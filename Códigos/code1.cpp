/*
WorkshpS - Minicurso de Visão Computacional : Uma introdução a OpenCV com C++ - 
código para explicar conceitos básicos relacionados a classe Mat
*/
#include <stdio.h> // biblioteca com as funções básicas de C
#include <iostream> // biblioteca com as funções básicas de C++
#include "opencv2/highgui.hpp" // uma das bibliotecas da OpenCV

using namespace std; // usada para facilitar o uso das funções de C (printf, scanf,...)
using namespace cv; // usada para facilitar o uso das funções da OpenCV (sem ela, cada função da opencv teria de ser escrita com um "cv::" antes)

char *window_2 = "Window 2";

int main()
{
    /* A varíavel Mat é a classe básica da OpenCV que armazena uma imagem. Ela contém tanto as informações dos pixeis
	(matrix multidimensional) quanto as informações sobre o formato da imagem (tamanho, tipo dos canais de cor...) 
	Existem vários métodos para criar uma imagem do zero, dois deles são abordados nesta prática */

	///////////////////////////////////////////////////////////////////////

	namedWindow("Window 1", WINDOW_NORMAL); // janela a ser usada
	waitKey(0);

	/* Os parâmetros são:
			10,10: o tamanho da imagem
			CV_8UC3: formato dos pixeis
			Scalar(255,0,0): a cor atribuida a eles
	*/
	Mat M1 (10, 10, CV_8UC3, Scalar(255,0,0));

	// print numérico da matriz de pixeis RGB
    cout << "M1 = " << endl << " " << M1 << endl << endl; 
	// a imagem gerada pela matriz
    imshow("Window 1", M1); 
    waitKey(0); 

	destroyWindow("Window 1");


	///////////////////////////////////////////////////////////////////////

	namedWindow(window_2, WINDOW_AUTOSIZE);
    waitKey(0);

    Mat M2;
    M2.create(20,20, CV_8UC3);
    cout << "M2 = " << endl << " " << M2 << endl << endl;
    imshow(window_2, M2);
    waitKey(0);
	destroyWindow(window_2);

	//////////////////////////////////////////////////////////////////////

	namedWindow("New Window 1", WINDOW_NORMAL); // janela a ser usada
	namedWindow("New Window 2", WINDOW_NORMAL); // janela a ser usada

    /* Formas de atribuição - é importante ressaltar que de ambos os modos, apesar de cada variável
    possuir um header diferente, todas possuiram o mesmo ponteiro, portanto a alteração em uma delas
    afeta todas */
    Mat M3(M1);
    Mat M4 = M2;

	imshow("New Window 1", M3); 
	imshow("New Window 2", M4); 
	waitKey(0);


    // Copiando uma Mat para que possam ser trabalhadas separademente: 

	/* O comando release "libera" a imagem da memória. O nome da imagem deve ser escrito antes do .release. 
	Apesar de uma boa prática, o compilador do C tem formas de liberar espaço de memória periodicamente, 
	fazendo com que o comando release seja pouco usado */
	//M1.release(); 

    Mat M5 = M1.clone();
    Mat M6;
    M1.copyTo(M6);


	imshow("New Window 1", M5); 
	imshow("New Window 2", M6);
	waitKey(0); 

	////////////////////////////////////////////////////////////////////
	

	return 0;
}
