/*
WorkshpS - Minicurso de Visão Computacional : Uma introdução a OpenCV com C++ - 
algoritmo desenvolvido para capturas de tamplate a partir de um parâmetro em uma imagem
*/
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

// Variaveis globais que armazenam a imagem original e as alteradas pelo metodo
Mat img, templ, result;

// Nome atribuido as janelas utilizadas
char* image_window = "Imagem Original";
char* result_window = "Resultado";

// Variaveis para escolher o metodo de matching
int match_method;
int max_Trackbar = 5;

// Header da funcao callback do MatchingMethod
void MatchingMethod(int, void*);

int main( int argc, char** argv )
{
    // Leitura das duas imagens: a original e o templete tirado dela
    img = imread( argv[1], 1 );
    templ = imread( argv[2], 1 );

    namedWindow( image_window, CV_WINDOW_NORMAL );
    namedWindow( result_window, CV_WINDOW_NORMAL );

    // A trackbar varia de 0 a 5, sendo cada número um método diferente de matching
    char* trackbar_label = "Metodo: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
    createTrackbar( trackbar_label, image_window, &match_method, max_Trackbar, MatchingMethod );

    // Chamada da funcao Matching (callback da trackbar)
    MatchingMethod(0,0);

    waitKey(0);

    return 0;
}


void MatchingMethod(int, void*)
{
    // Uma copia da imagem original e criada
    Mat img_display;
    img.copyTo( img_display );

    // Duas variaveis armazenam o tamanho da imagem resultado baseado no tamanho da orgininal e do templete a ser procurado
    int result_cols =  img.cols - templ.cols + 1;
    int result_rows = img.rows - templ.rows + 1;

    // A imagem resultante e criada
    result.create( result_rows, result_cols, CV_32FC1 );

    /* A funcao match e aplicada e seus parâmetros sao:
            - imagem original
            - templete a ser procurado
            - imagem a receber o resultado da aplicacao do metodo
            - o metodo escolhido (varia com a trackbar)
    */
    matchTemplate( img, templ, result, match_method );
    // Funcao para normalizar os resultados entre 0 e 1
    normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );

    // Variaveis que armazenem as informacaoes da matriz resultante
    double minVal; double maxVal; Point minLoc; Point maxLoc;
    Point matchLoc;

    // Funcao que localiza o minimo e o maximo valor
    minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );

    // Para os dois primeiros metodos, usa-se a deteccao do ponto minimo, enquanto que para o restante se usa o maximo
    if( match_method  == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED )
        matchLoc = minLoc;
    else
        matchLoc = maxLoc;

    // Desenho de um retangulo na regiao detectada
    rectangle( img_display, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar(0,0,255), 2, 8, 0 );
    rectangle( result, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar(0,0,255), 2, 8, 0 );

    imshow( image_window, img_display );
    imshow( result_window, result );
}
