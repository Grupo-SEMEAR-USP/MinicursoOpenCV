/*
WorkshpS - Minicurso de Visão Computacional : Uma introdução a OpenCV com C++ 
- introdução a filtros 
*/
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

char* window_1 = "Source Image";
char* window_2 = "Result Image";

int main(int argc, char** argv)
{
    char* imageName = argv[1];

    Mat src, dst;
    
    src = imread(imageName, IMREAD_COLOR);
    if(argc != 2 || !src.data)
    {
        printf( " No image data \n " );
        return -1;
    }


    Mat kernel = (Mat_<char>(3,3) <<    1.0,    0.0,    -1.0,
                                        2.0,    0.0,    -2.0,
                                        1.0,    0.0,    -1.0);

    /*Mat kernel = (Mat_<char>(3,3) <<    0.2,    4.0,    2.0,
                                        0.4,    1.0,    4.0,
                                        0.2,    0.4,    0.2);
    */
    
    /*
    Mat kernel = (Mat_<char>(3,3) <<    0.2,    1.0,    0.2,
                                        1.0,    1.0,    1.0,
                                        0.2,    1.0,    0.2);
    */


    /* filter2D é a função que aplica um filtro em uma imagem
        PARAMETROS 
            src: imagem original
            dst: imagem com o filtro
            src.depth(): profundidade (intensidade dos pixeis) a ser usada
            kernel: o filtro a ser aplicado
    */                        
    filter2D(src,dst,src.depth(),kernel);

    namedWindow(window_1, WINDOW_NORMAL);
    namedWindow(window_2, WINDOW_NORMAL);

    imshow(window_1, src);
    imshow(window_2, dst);

    waitKey(0);

    destroyWindow(window_1);
    destroyWindow(window_2);

    return 0;
}
