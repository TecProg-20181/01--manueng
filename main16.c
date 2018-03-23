#include <stdio.h>

typedef struct _pixel {
    unsigned short int r;
    unsigned short int g;
    unsigned short int b;
} Pixel;

typedef struct _image {
    // [width][height][rgb]
    // 0 -> r
    // 1 -> g
    // 2 -> b
    Pixel pixel[512][512];
    unsigned int width;
    unsigned int height;
} Image;
  short int menor(  int n1,   int n2){
     int result;
    if(n1>n2){
        result=n2;
    }else{
        result=n1;
    }
    return result;
}


int pixel_igual(Pixel p1, Pixel p2) {
    int result;
    if (p1.r == p2.r &&
        p1.g == p2.g &&
        p1.b == p2.b){
           result=1;
        }else{
         result=0;
        }
    return result;
}
Image inverter_cores(Image imagework) {
    unsigned int i,j;

    
    for (i = 0; i < imagework.height; ++i) {
        for (j = 0; j <imagework.width; ++j) {
           imagework.pixel[i][j].r= 255 - imagework.pixel[i][j].r;
           imagework.pixel[i][j].g= 255 - imagework.pixel[i][j].g;
           imagework.pixel[i][j].b= 255 - imagework.pixel[i][j].b;
        }
    }
   return imagework;
}

Image escala_de_cinza(Image imagemwork) {
   unsigned int i,j;
    for (i = 0; i < imagemwork.height; ++i) {
        for (j = 0; j < imagemwork.width; ++j) {
            unsigned int media =imagemwork.pixel[i][j].r +
                       imagemwork.pixel[i][j].g +
                        imagemwork.pixel[i][j].b;
            media /= 3;
            imagemwork.pixel[i][j].r = media;
            imagemwork.pixel[i][j].g = media;
           imagemwork.pixel[i][j].b= media;
        }
    }

    return imagemwork;
}


Image blur(Image imagework,int tamanho) {
    unsigned i,j;

    for ( i = 0; i <imagework.height; ++i) {
        for (j = 0; j < imagework.width; ++j) {
            Pixel media = {0, 0, 0};
            int x,y;
            int menor_h = menor(imagework.height- 1 , i + tamanho/2);
            int min_w = menor(imagework.width - 1 ,j + tamanho/2) ;
            for( x = menor(0 ,i - tamanho/2 ); x <= menor_h; ++x) {
                for( y = menor  (0 , j - tamanho/2); y <= min_w; ++y) {
                    media.r +=imagework.pixel[x][y].r;
                    media.g += imagework.pixel[x][y].g;
                    media.b += imagework.pixel[x][y].b;
                }
            }

            // printf("%u", media.r)
            media.r /= tamanho * tamanho;
            media.g /= tamanho * tamanho;
            media.b /= tamanho* tamanho;

           imagework.pixel[i][j].r = media.r;
           imagework.pixel[i][j].g= media.g;
          imagework.pixel[i][j].b= media.b;
        }
    }
    return imagework;
}


Image rotacionar90direita(Image imagework) {

     int i,j,x,y;
    for (i = 0, y = 0; i < imagework.width; ++i, ++y) {
        for (j = imagework.height - 1, x = 0; j >= 0; --j, ++x) {
            imagework.pixel[i][j].r= imagework.pixel[x][y].r;
            imagework.pixel[i][j].g = imagework.pixel[x][y].g;
            imagework.pixel[i][j].b=  imagework.pixel[i][j].b;
        }
    }
  return imagework;
}

Image cortar_imagem(Image imagework, int x, int y, int w, int h) {

    int i,j;
    imagework.width=w;
    imagework.height=h;
    for( i = 0; i < h; ++i) {
        for(j = 0; j <w; ++j) {
            imagework.pixel[i][j].r=imagework.pixel[i + y][j + x].r;
            imagework.pixel[i][j].g=imagework.pixel[i + y][j + x].g;
            imagework.pixel[i][j].b=imagework.pixel[i + y][j + x].b;
        }
    }

    return imagework;
}
int filtrosepiap(double c1,double c2,double c3,Pixel  pixel){
    int c;
    c= pixel.r*c1+ pixel.g*c2+pixel.b*c3;
    return menor(c,255);
}
 Image filtro_sepia (Image img){
    unsigned int  x,j;
                for (x = 0; x < img.height; ++x) {
                    for (j = 0; j < img.width; ++j) {


                        img.pixel[x][j].r = filtrosepiap(0.393,0.769,0.189,img.pixel[x][j]);

                        img.pixel[x][j].g = filtrosepiap(0.349,0.686,0.168,img.pixel[x][j]);

                        img.pixel[x][j].b= filtrosepiap(0.272,0.534,0.131,img.pixel[x][j]);}
        }
            return img;
}



 Image  espelhamento(Image img){ 
                int horizontal = 0;
                scanf("%d", &horizontal);

                int w = img.width, h = img.height;

                if (horizontal == 1) w /= 2;
                else h /= 2;

                for (int i2 = 0; i2 < h; ++i2) {
                    for (int j = 0; j < w; ++j) {
                        int x = i2, y = j;

                        if (horizontal == 1) y = img.width - 1 - j;
                        else x = img.height - 1 - i2;

                        Pixel auxpixel;
                        auxpixel.r = img.pixel[i2][j].r;
                        auxpixel.g = img.pixel[i2][j].g;
                        auxpixel.b = img.pixel[i2][j].b;

                        img.pixel[i2][j].r = img.pixel[x][y].r;
                        img.pixel[i2][j].g = img.pixel[x][y].g;
                        img.pixel[i2][j].b = img.pixel[x][y].b;

                        img.pixel[x][y].r = auxpixel.r;
                        img.pixel[x][y].g = auxpixel.g;
                        img.pixel[x][y].b = auxpixel.b;
                    }
                }
return img;
}
  Image operacao (int opcao, Image imagework){

     switch(opcao) {
            case 1: { // Escala de Cinza
                imagework= escala_de_cinza(imagework);
                break;
            }
            case 2: { // Filtro Sepia
                imagework= filtro_sepia(imagework);
                break;
            }
            case 3: { // Blur
                int tamanho = 0;
                 scanf("%d", &tamanho);
                imagework=blur(imagework,tamanho);
                break;
            }
            case 4: { // Rotacao
                int quantas_vezes = 0;
                scanf("%d", &quantas_vezes);
                quantas_vezes %= 4;
                unsigned int j;
                for ( j = 0; j < quantas_vezes; ++j) {
                  imagework = rotacionar90direita(imagework);
                }
                break;
            }
            case 5: { // Espelhamento
                imagework=espelhamento(imagework);
                break;
            }
            case 6: { // Inversao de Cores
               imagework=inverter_cores(imagework);
                break;
            }
            case 7: { // Cortar Imagem
                int x, y;
                scanf("%d %d", &x, &y);
                int w, h;
                scanf("%d %d", &w, &h);

                imagework = cortar_imagem(imagework, x, y,w,h);
                break;
            }
          }
       return imagework;

}
void print_pixel(Image imagework){
    unsigned int i,j;
    for (i= 0; i < imagework.height; i++) {
        for ( j= 0; j < imagework.width; j++) {
            printf("%hu %hu %hu ", imagework.pixel[i][j].r,
                                   imagework.pixel[i][j].g,
                                   imagework.pixel[i][j].b);

        }
        printf("\n");
    }
}
int main() {
    Image imagework;
    Image imagework3;
    // read type of image
    char p3[4];
    scanf("%s", p3);

    // read width height and color of image
    int max_color;
    scanf("%u %u %d", &imagework.width, &imagework.height, &max_color);


    // read all pixels of image
    unsigned int i,j;
    for ( i = 0; i < imagework.height; ++i) {
        for (j = 0; j < imagework.width; ++j) {
            scanf("%hu %hu %hu", &imagework.pixel[i][j].r,
                                 &imagework.pixel[i][j].g,
                                 &imagework.pixel[i][j].b);

        }
    }
   imagework3=imagework;
    int n_opcoes;
    scanf("%d", &n_opcoes);

    for( i = 0; i < n_opcoes; ++i) {
        int opcao;
        scanf("%d", &opcao);
       imagework3=operacao(opcao,imagework);


    }


    // print type of image
    printf("P3\n");
    // print width height and color of image
    printf("%u %u\n255\n", imagework.width, imagework.height);

    // print pixels of image

    print_pixel(imagework3);
    return 0;
}
