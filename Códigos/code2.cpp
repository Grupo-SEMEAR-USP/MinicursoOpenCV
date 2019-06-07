/*
WorkshpS - Minicurso de Visão Computacional : Uma introdução a OpenCV com C++
- apresentação de funções fundamentais a OpenCV
*/
#include <stdio.h>
#include <iostream>
#include <opencv2/highgui.hpp>

using namespace std; 
using namespace cv; 


int main()
{
	/*
	A função imread carrega a imagem e a salva na variável img. O primeiro parâmetro contêm o nome da imagem a ser usada 
	(neste caso a imagem deve estar armazenada na pasta do projeto) ou senão o endereço dela no disco. O segundo parâmetro
	deve conter as características da imagem:
	CV_LOAD_IMAGE_UNCHANGED: cor e resolução originais
	CV_LOAD_IMAGE_COLOR: permite configurar para escolher se quer em grayscale ou normal
	CV_LOAD_IMAGE_GRAYSCALE: converte a imagem para grayscale
	*/
	Mat img1 = imread("imagem_1.jpg",CV_LOAD_IMAGE_COLOR);
	Mat img2 = imread("imagem_1.jpg",CV_LOAD_IMAGE_GRAYSCALE);
	Mat img3 = imread("imagem_1.jpg",CV_LOAD_IMAGE_UNCHANGED);

	namedWindow("Display window 1", WINDOW_GUI_NORMAL);
	namedWindow("Display window 2", WINDOW_NORMAL);
	namedWindow("Display window 3", WINDOW_AUTOSIZE);
	/*
	Função que nomeia e cria uma janela de execução. O primeiro parâmetro deve conter o nome desejado e o segundo,
	a característica dessa janela:
	WINDOW_GUI_NORMAL: a imagem se aloca toda na janela, sendo possível redimensiona-la
	WINDOW_NORMAL: a imagem se aloca toda na janela, sendo possível redimensiona-la e permite ver coordenadas
	WINDOW_AUTOSIZE: a janela assume o tamanho padrão da tela, cortando a imagem original se essa ultrapassa esse tamanho
	*/


	imshow("Display window 1", img1);
	imshow("Display window 2", img2);
	imshow("Display window 3", img3);
	/*
	imshow é a função responsável por mostrar a imagem na janela criada. O primeiro parâmetro
	especifica que janela deve ser usada e o segundo, a imagem a ser exibida
	*/

	waitKey(0); 
	/* 
	Espera o usuário apertar qualquer tecla. O parâmetro é dado em milessegundos, mas, no caso de ser <= 0, o 
	programa espera infinitamente.
	*/

	destroyWindow("Display window 1"); 
	destroyWindow("Display window 2");
	destroyWindow("Display window 3"); 
	/* 
	Apaga a janela declarada como parâmetro, finalizando o programa
	*/


	//////////////////////////////////////////////////////////////////////////////////

	img2.release();
	img3.release();

	Mat img4 = img1.clone();

	namedWindow("Display Image", WINDOW_NORMAL);

	imshow("Display Image",img4);

	waitKey(0);

	img4.release();

	destroyAllWindows(); // Comando muito útil para apagar todas as janelas de uma só vez

	
	/////////////////////////////////////////////////////////////////////////////////

	Mat src;

	namedWindow("Source Video",WINDOW_NORMAL);
	
	VideoCapture cap("video_1.mp4");
	/*
	Função de captura de vídeo. O parâmetro deve conter o numero da câmera, 
	sendo 0 a câmera padrão. -1 acessa qualquer câmera disponível.
	O parâmetro também pode conter o endereço de um vídeo.
	*/

	if(cap.isOpened()) //Testamos se o video foi aberto com sucesso
		cout << "Video aberto com sucesso" << endl;
	else {
		cout << " Erro na abertura do video!" << endl;
		return 0; 
	}
	
	while(cap.isOpened()) { //Enquanto estiver o video aberto
		cap.read(src); //Captura as imagens (frames) da câmera e ou video e guarda na variável src
		imshow("Source Video",src);
		int k = waitKey(33); //Tempo esperado por cada frame
		if (k == 27) break; //Se apertar ESC saio do loop
	}

	src.release();

	destroyAllWindows();
	
}
