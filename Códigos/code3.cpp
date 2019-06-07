/*
WorkshpS - Minicurso de Visão Computacional : Uma introdução a OpenCV com C++ 
- código utilizado para explicar como realizar operações do tipo rotacionar, transladar, redimensionar e cortar uma imagem
*/
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void translada_imagem(Mat &dst, int x, int y){
	Mat deslocamento = (Mat_<double>(2,3) << 1, 0, x, 
	                                         0, 1, y);
	/*
	Estou declarando a matriz que recebe valores do tipo double,
	que possui 2 linhas e 3 colunas, que passarei como parâmetro
	para função warpAffine, só altero o x para transladar no eixo x
	(se x>0 -> direita/ x<0 -> esquerda) e o y para transladar no
	 eixo y	(se y>0 -> desce/ x<0 -> sobe)
	*/
    warpAffine(dst,dst,deslocamento,dst.size());
	/*
	Função que permite aplicar uma transformação do tipo afim (Affine)  - recebe como parâmetro
	imagem de origem, imagem de destino, uma Mat (matriz) com os valores 
	que serão aplicados na imagem de origem, as dimensões da imagem de saída
	*/
}

void rotaciona_imagem(Mat &dst, double angulo, double escala){
	Point centro = Point( dst.cols/2, dst.rows/2 );
	Mat rotacao = getRotationMatrix2D( centro, angulo, escala );
	/*
	Calcula uma matriz afim de rotação 2D
	*/
	warpAffine(dst,dst,rotacao,dst.size());
}

int main( int argc, char* argv[] )
{
	char* imageName = argv[1];

   	Mat img = imread(imageName, IMREAD_COLOR);
	
	namedWindow("Display Imagem",WINDOW_NORMAL);
	resizeWindow("Display Imagem",Size(700,500));
	/*
	Função responsável por redimensionar uma janela - recebe como parâmetros o nome da janela
	e o tamanho que quero redimensionar (pode-se colocar um valor em pixel só que receberá tanto 
	a largura como altura ou pode-se usar uma estrutura do tipo Size(largura,altura))
	*/
	imshow("Display Imagem",img);
	waitKey(0);
	destroyWindow("Display Imagem");
	Mat dst0, dst1, dst2, dst3;
	resize(img, dst0, Size(700,500));
	/*
	Função responsável por redimensionar uma imagem - recebe como parâmetros a
	imagem de entrada, a Mat que sera destino da imagem de saída, o tamanho re-
	dimensinado do tipo Size(largura,altura), 
	*/
	namedWindow("Imagem Redimensionada",WINDOW_NORMAL);
	resizeWindow("Imagem Redimensionada",Size(700,500));
	imshow("Imagem Redimensionada",dst0);
	waitKey(0);
	destroyWindow("Imagem Redimensionada");
	dst0.release();

	img.copyTo(dst1);
	translada_imagem(dst1,-80,-100);
	namedWindow("Imagem Transladada",WINDOW_NORMAL);
	resizeWindow("Imagem Transladada",Size(700,500));
	imshow("Imagem Transladada",dst1);
	waitKey(0);
	destroyWindow("Imagem Transladada");
	dst1.release();

	img.copyTo(dst2);
	rotaciona_imagem(dst2,90,0.5);
	namedWindow("Imagem Rotacionada",WINDOW_NORMAL);
	resizeWindow("Imagem Rotacionada",Size(700,500));
	imshow("Imagem Rotacionada",dst2);
	waitKey(0);
	destroyWindow("Imagem Rotacionada");
	dst2.release();

	img.copyTo(dst3);
	int Rows = dst3.rows;
    int Cols = dst3.cols;

	
    Mat mask (dst3.rows,dst3.cols, CV_8UC3, Scalar(0,0,0));
	//Declaro uma matriz do tamanho da imagem da dst3, do tipo de três canais e de cor preta

        
	//Declaro meus vetores de pontos que utilizarei para criar minha minha região de interesse (ROI)
    vector<Point> ROI_Poly, ROI_Output;
	//Tomo os pontos que irão gerar minha ROI guardando no meu vetor de pontos
    ROI_Poly.push_back(Point(0.25*Cols, 0.25*Rows)); //A
    ROI_Poly.push_back(Point(0.75*Cols, 0.25*Rows)); //B
    ROI_Poly.push_back(Point(0.75*Cols, 0.75*Rows)); //C
    ROI_Poly.push_back(Point(0.25*Cols, 0.75*Rows)); //E

	
    approxPolyDP(ROI_Poly,ROI_Output, 1.0, true);
	/*
	Função que aproxima uma curva ou polígono de entrada em outra curva / polígono com menos 
	vértices, de forma que a distância entre eles sejam menores ou igual à precisão especificada. 
	Ele usa o algoritmo Douglas-Peucker http://en.wikipedia.org/wiki/Ramer-Douglas-Peucker_algorithm
	Recebe como parâmetros vetor de Pontos 2D de entrada, vetor de Ponts 2D de saída,valor máximo
	de aproximação entre os vertices, parâmetro que caso seja true define que o polígono tem que ser
	fechado
	*/
        
    
    fillConvexPoly(mask, &ROI_Output[0], ROI_Output.size(), Scalar(255,255,255));
	/*
	Funçaõ que preenche uma imagem com um polígono fechado
	Recebe como parâmetros a imagem que será preenchida com o polígono
	o vetor de pontos do polígono, tamanho do polígono(vertices), a  cor
	que será preenchida o polígono*/                 
        
    // Crio uma nova imagem para guardar o resultado
    Mat imageDest;
        
    // Corto a região de interesse delimitada pela mask sobre a dst3 guardando o resultado na imageDest
    dst3.copyTo(imageDest, mask);  
	
	namedWindow("Imagem Original",WINDOW_NORMAL);
	namedWindow("Imagem Cortada",WINDOW_NORMAL);
	resizeWindow("Imagem Cortada",Size(700,500));
    imshow("Imagem Original", dst3);   
    imshow("Imagem Cortada", imageDest);
	waitKey(0);
	destroyAllWindows();
	dst3.release();
	mask.release();
	imageDest.release();

	return 0;
}
