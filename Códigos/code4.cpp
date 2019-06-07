/*
WorkshpS - Minicurso de Visão Computacional : Uma introdução a OpenCV com C++ 
- apresentação de funções responsáveis por realizar desenhos de formas geométricas básicas
*/
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    Mat src = imread( "image_4.jpeg" );

    if( src.empty() ){
        printf( " Imagem não carregada ! \n " );
        return -1;
    }   

    Mat dst = src.clone();

    /*
    comando ellipse desenha uma elipse 
    Parâmetros: imagem , coordenada centro, tamanho (eixo_horizontal,eixo_vertical),
    ângulo que ela estará virado , ângulo de começo, ângulo final que vai preenchendo,
    grossura, tipo de linha
    */ 

    ellipse( src, Point(src.cols/2,src.rows/2), Size(src.cols/4,src.rows/16), 
    -45, 0, 360, Scalar(0,0,0), 3, LINE_4);

    ellipse( src, Point(src.cols/2,src.rows/2), Size(src.cols/4,src.rows/16), 
    0, 0, 360, Scalar(0,0,0), 3, LINE_4 );

    ellipse( src, Point(src.cols/2,src.rows/2), Size(src.cols/4,src.rows/16), 
    45, 0, 360, Scalar(0,0,0), 3, LINE_4 );

    ellipse( src, Point(src.cols/2,src.rows/2), Size(src.cols/4,src.rows/16), 
    90, 0, 360, Scalar(0,0,0), 3, LINE_4 );

    /*
    Desenha um circulo na imagem
    Parâmetros: imagem, centro, raio do circulo, canais(cor), grossura, tipo  
    */

    circle( src, Point(src.cols/2,src.rows/2), src.cols/32, Scalar(255,255,255,0.1), FILLED, LINE_8);

    /*
    Função que define uma linha entre as coordenadas linha na imagem guardada na variavel mat 
    de entrada
    Parametros: mat de entrada, coordenada 1, coordenada 2, cor , grossura(1 até 4), 
    tipo de linha (pontilhada...) 
    */

    line ( src, Point(120,270), Point(355,270), Scalar(255,255,255), 3, LINE_4);
    line ( src, Point(120,270), Point(120,515), Scalar(255,255,255), 3, LINE_4);
    line ( src, Point(120,515), Point(355,515), Scalar(255,255,255), 3, LINE_4);
    line ( src, Point(355,515), Point(355,270), Scalar(255,255,255), 3, LINE_4);

    Point rook_points[1][4];
    rook_points[0][0]  = Point( (3*src.cols)/4, (3*src.rows)/4);
    rook_points[0][1]  = Point( src.cols, src.rows);
    rook_points[0][2]  = Point( (3*src.cols)/4, (src.rows));
    rook_points[0][3]  = Point( src.cols, (3*src.rows)/4);

    const Point* ppt[1] = { rook_points[0] };
    int npt[] = { 4 };

    /*
    Função que produz um polígono 
    parâmetros: imagem, ponteiro de coordenadas, numero de pontos, cor , tipo de linhas
    */
   
    fillPoly( src,ppt,npt,1,Scalar( 0, 0, 255),LINE_MAX );

    rook_points[0][0]  = Point( 0, 0);
    rook_points[0][1]  = Point( src.cols/4, 0);
    rook_points[0][2]  = Point( 0, src.rows/4);
    rook_points[0][3]  = Point( src.cols/4, src.rows/4);

    const Point* ppt1[1] = { rook_points[0] };
    fillPoly( src,ppt1,npt,1,Scalar( 255, 0, 0),LINE_MAX );

    /* 
    Função que desenha um retângulo
    Parametros: imagem, coordenada 1, coordenada diagonalmente oposta,cor,
    preenchido//grossura(se -1 ele é FILLED), tipo de linha
    */
   
    rectangle(src,Point(3*src.cols/4, 0),Point(src.cols, src.rows/4),Scalar(0,0,255),-1,LINE_8);
    rectangle(src,Point(0, 3*src.rows/4),Point(src.cols/4, src.rows),Scalar(255,0,0),-1,LINE_8);

    namedWindow( "Result Image", WINDOW_NORMAL );
    resizeWindow("Result Image",Size(500,800));

    imshow("Result Image", src );

    waitKey(0);
    destroyWindow("Result Image");
    src.release();
    return 0;
}

/*
Observações :  
Point é uma estrutura de coordenada no R2 :

Point pt;
pt.x = 10;
pt.y = 8;

Point pt = Point(10, 8);

Scalar:
Represents a 4-element vector. The type Scalar is widely used in OpenCV for passing pixel values.
In this tutorial, we will use it extensively to represent BGR color values (3 parameters). 
It is not necessary to define the last argument if it is not going to be used.//parametro de visibilidade
Let's see an example, if we are asked for a color argument and we give:
Scalar( a, b, c )
We would be defining a BGR color such as: Blue = a, Green = b and Red = c 

imagem.cols -> pega o numero total de colunas da matriz da imagem -> utilizo para variar meu x
imagem.rows -> pega o numero total de linhas da matriz da imagem -> utilizo para variar meu y

Size(width, heigth) é uma classe relacionado com o tamanho
*/
