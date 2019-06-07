/*
WorkshpS - Minicurso de Visão Computacional : Uma introdução a OpenCV com C++ - 
- desenvolvimento de trackbars e filtros utilizados na eliminação de ruídos
*/
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp" 
#include <iostream>

using namespace cv;
using namespace std;

int val_blur, val_gau, val_med, val_bil;
Mat dst, img;

void Blur(int, void*){
	int i = 2*val_blur+1;
	blur(img,dst,Size(i,i),Point(-1,-1),BORDER_DEFAULT);
	/*
	A função blur é uma das funções que esfumaçam(tiram o foco) da imagem 
    Parâmetros: imagem de entrada, imagem de saída, o tamanho do kernel, a coordenada da âncora
    do kernel se (-1,-1) representa o centro, o tipo de borda
        
    O que ele faz é o kernel = 1/(ksize.width*ksize.heigth) * [matriz de 1 do tamanho de size]
	*/
	imshow("Result Image",dst);
}

void Gaussian_Blur(int, void*){
	int i = 2*val_gau+1;
	GaussianBlur(img,dst,Size(i,i),0,0);
	imshow("Result Image",dst);
	/*
	Função que aplica o filtro GaussianBlur
    Parâmetros: imagem de entrada, imagem de saida, tamanho do kernel, 
    derivada de x (dx = 0 max intensidade), derivada de y 
	*/
}

void Median_Blur(int, void*){
	int i = 2*val_med+1;
	medianBlur(img,dst,i);
	/*
	Aplica o filtro median blur também utilizado como efeito de esfumaçar para tratamento de ruido
	Recebe a imagem de entrada, imagem de saída e tamanho do kernel que precisa só de uma coordenada
	por ser um quadrado.
	*/

	imshow("Result Image",dst);
}

void Bilateral_Filter(int, void*){
	int i = 2*val_bil+1;
	bilateralFilter(img,dst,i,i*2,i/2);
	/*
    Parâmetros: imagem entrada, imagem saída, diametro que estou pegando de cada pixel vizinho,
    sigmaColor, sigmaSpace

    sigmaColor : Filtro sigma no espaço de cores. 
    Um valor maior do parâmetro significa que cores mais distantes dentro da vizinhança 
    do pixel (ver sigmaSpace) serão misturadas, resultando em áreas maiores de cor semi-igual.

    sigmaSpace: Filtro sigma no espaço de coordenadas. Um valor maior do parâmetro significa 
    que pixels mais distantes influenciarão um ao outro, desde que suas cores estejam próximas 
    o suficiente (veja sigmaColor). Quando d> 0, especifica o tamanho da vizinhança, 
    independentemente do sigmaSpace. Caso contrário, d é proporcional ao sigmaSpace
    */
	imshow("Result Image",dst);
}

int main( int argc, char* argv[] )
{
	char* imageName = argv[1];

   	img = imread(imageName, IMREAD_COLOR);

	namedWindow("Original Image",WINDOW_NORMAL);
	namedWindow("Result Image",WINDOW_NORMAL);
	resizeWindow("Result Image",Size(700,700));
	moveWindow("Original Image",100,0);
	moveWindow("Result Image",500,0);
	/*
	Função para mover uma janela, tomo como ponto (0,0) o canto superior esquerdo da tela,
	recebe como parâmetros o nome da janela a ser movida, quantidades de pixes no eixo x,
	quantidade de pixels no eixo y
	*/
	imshow("Original Image",img);
	createTrackbar("Blur: ","Result Image",&val_blur,15,Blur);
	createTrackbar("Gaussian Blur: ","Result Image",&val_gau,15,Gaussian_Blur);
	createTrackbar("Median Blur : ","Result Image",&val_med,15,Median_Blur);
	createTrackbar("Bilateral Filter : ","Result Image",&val_bil,15,Bilateral_Filter);
	/*
	Cria um trackbar e o anexa à janela especificada.
    A função createTrackbar cria uma barra de controle (um controle deslizante ou range) 
    com o nome e faixa especificados, atribui um valor variável para ser uma posição 
    sincronizada com o trackbar e especifica a função de retorno de chamada onChange 
    a ser chamada na mudança de posição do trackbar. A barra de controle criada é exibida 
    no nome da janela especificado.
    
    Parâmetros: nome da trackbar, nome da janale utilizada, ponteiro opcional , 
    máxima posição do slider, onChange, userdata
    
    ponteiro opcional: Ponteiro opcional para uma variável inteira cujo valor reflete a 
    posição do controle deslizante. Na criação, a posição do controle deslizante é definida por 
    essa variável


    onChange : Ponteiro para a função a ser chamada toda vez que o controle deslizante mudar de posição.
    Esta função deve ser prototipada como void Foo (int, void *); , onde o primeiro parâmetro é a posição
    da barra de controle e o segundo parâmetro são os dados do usuário (veja o próximo parâmetro). 
    Se o retorno de chamada for o ponteiro NULL, nenhum retorno de chamada será chamado, mas somente o 
    valor será atualizado.
    database: 
      
    database: Dados do usuário que são passados como estão para o retorno de chamada. Pode ser usado
    para manipular eventos de trackbar sem usar variáveis globais
	*/
	Blur(0,0);
	Gaussian_Blur(0,0);
	Median_Blur(0,0);
	Bilateral_Filter(0,0);
	waitKey(0);
	destroyAllWindows();
	img.release();
	dst.release();
	return 0;
}
