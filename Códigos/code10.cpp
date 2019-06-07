/*
WorkshpS - Minicurso de Visão Computacional : Uma introdução a OpenCV com C++ 
- introdução ao algoritmo de captura de contornos e de comparação de contornos
*/
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"

#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	// variáveis para o Canny
	int thresholdImg = 110;
	int thresholdCam = 95;

	Mat compareImg;
	Mat cannyImg;
	Mat frame;
	Mat cannyFrame;

	RNG rng(12345); //Random Number Generator -> retorna numeros aleatorios - no caso numeros compostos por 12345 

	// variáveis utilizadas para o findContours
	vector<vector<Point> > contours;//vetor que guardará os contornos
	vector<Vec4i> hierarchy;//vetor que guarda as hieraquias de vetor
	vector<Point> ImgContour;

	// primeiro acha o contorno que utilizará como comparação
	compareImg = imread(argv[1], IMREAD_GRAYSCALE);

	if( compareImg.empty() ){
		cout << "Imagem nao carregada !" ;
		return -1;
	}
	
	Canny(compareImg, cannyImg, thresholdImg, thresholdImg * 2);
	/*
  	A função encontra arestas na imagem da imagem de entrada e as marca nas arestas do mapa de 
  	saída usando o algoritmo de Canny. O menor valor entre o limite 1 e o limite 2 é usado para vinculação
  	de borda. O maior valor é usado para encontrar segmentos iniciais de arestas fortes
  	Canny(imagem de entrada, imagem de saida com os contornos, primeiro limite, segundo limite,
  	tamanho de abertura para o operador de Sobel)
  	*/
	
	findContours(cannyImg, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	/*
  	Função que retorna os contornos em uma imagem binária 
  	findContours(imagem de entrada no qual pixels não 0 são tratados como 1 e 0 como 0/
  	Contornos detectados. Cada contorno é armazenado como um vetor de pontos./ 
  	Vetor de saída opcional, contendo informações sobre a topologia da imagem. 
  	Tem tantos elementos quanto o número de contornos. Para cada contorno de contorno i [i], os 
  	elementos hierarquia [i] [0], hiearchy [i] [1], hiearchy [i] [2] e hiearchy [i] [3] são definidos 
  	como 0- índices baseados nos contornos dos contornos seguinte e anterior no mesmo nível hierárquico, 
  	o primeiro contorno filho e o contorno pai, respectivamente. Se para o contorno i não houver nenhum 
  	contorno seguinte, anterior, pai ou aninhado, os elementos correspondentes da hierarquia [i] serão 
  	negativos. )/Modo de recuperação de contorno,/Método de aproximação de contorno/Deslocamento 
  	opcional pelo qual cada ponto de contorno é deslocado. Isso é útil se os contornos 
  	forem extraídos do ROI da imagem e, em seguida, devem ser analisados em todo o contexto da imagem. 
  	*/
	namedWindow("Canny ImgCompare", CV_WINDOW_NORMAL);
	imshow("Canny ImgCompare", cannyImg);	

	ImgContour = contours[0]; //Guardarei o contorno primário que quero utilizar como parâmetro de comparação
	
	for (int i = 0; i < contours.size(); i++) {

		Mat temp = Mat::zeros(cannyImg.size(),CV_8UC3);
		/*
		Tomo uma imagem do tamanho da cannyImg inicializada com todos os elementos
  		zero (atribuindo a cor preta)
  		*/
		drawContours(temp,contours,i,Scalar(0,0,255),2,8);
		/*
       Função responsável por printar na tela os contornos 
       (imagem de entrada /Todos os contornos de entrada. Cada contorno é armazenado como um vetor de pontos/
       Parâmetro que indica um contorno para desenhar. Se for negativo, todos os contornos são desenhados./
       Cor dos contornos/ Espessura das linhas com as quais os contornos são desenhados. Se for negativo (por exemplo, espessura = CV_FILLED)
        os interiores do contorno são desenhados.)/Conectividade de linha/Informações opcionais sobre hierarquia. Só é necessário 
        se você quiser desenhar apenas alguns dos contornos (veja maxLevel)./
        Nível máximo para contornos desenhados. Se for 0, somente o contorno especificado é 
        desenhado. Se for 1, a função desenha o (s) contorno (s) e todos os contornos aninhados. 
        Se for 2, a função desenha os contornos, todos os contornos aninhados, todos os contornos 
        aninhados para aninhados e assim por diante. Esse parâmetro só é levado em conta quando 
        há hierarquia disponível./
        Optional contour shift parameter. Shift all the drawn contours by the specified valor derivada
        x e y
        */
		namedWindow("Contours ImgCompare", WINDOW_NORMAL);
		imshow("Contours ImgCompare", temp);
	}

	//VideoCapture cap(0);
	VideoCapture cap("figuras.mp4");

	if ( !cap.isOpened() )
    {
         cout << "Erro ao abrir o video ou camera" << endl;
         return -1;
    }


	while (waitKey(1) != 27) 
	{

		cap.read(frame);

		// aplica o blur para reduzir os ruídos
		blur(frame, frame, Size(3, 3));

		Canny(frame, cannyFrame, thresholdCam, thresholdCam * 2);
		findContours(cannyFrame, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

		// passa por todos contornos, procurando aquele com o menor valor (maior chance de ser o certo)
		double valor;
		double menor = 100;//Não posso começar por zero, pois é o que quero chegar
		vector<Point> melhor;//guardará o melhor contorno
		for (int i = 0; i < contours.size(); i++) 
		{
			 valor = matchShapes(ImgContour, contours[i], CV_CONTOURS_MATCH_I1,0);
			 /*
			 Função responsável por comparar dois formatos (shapes). Recebe como parâmetro uma imagem em
			 gray_scale ou vetor de contornos de entrada, segunda imagem em gray_scale ou vetor de 
			 contornos que será usado para comparar, método de comparação,Parâmetro específico do método 
			 Ele retorna um valor em que mais próximo de 0 menor é a distância entre o determinado contorno
			 e o objeto que está encontrando 
			 */

			if (valor < menor) // && valor > 0 && arcLength(contours[i], false) > 80A função calcula um comprimento de curva ou um perímetro de contorno fechado. 
			{
				menor = valor;
				melhor = contours[i];
			}
			//dentro do for estou passando por todos os contornos de um frame e calculando o menor valor
			//possivel achado pela minha matchShape
		}

		if (menor<=0.2){
			Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
       		/*
       		gerando uma variavel do tipo Scalar que guardará os canais das cores do contorno de forma 
       		aleátoria utilizando o rng.uniform que gerará cores indo de 0 até 255
       		*/
			polylines(frame, melhor, true, color, 3);
			/*
			Função utilizada para desenhar polígonos e outras figuras, principalmente quando se quer
			desenhar somente um contorno. Recebe de parâmetros a imagem de entrada aonde será desenhado,
			o vetor de pontos(contorno), variável booleana se indica ou não se o contorno(figura) é fechada,
			cor, grossura
			*/
		}

		namedWindow("Camera", WINDOW_NORMAL);
		imshow("Camera", frame);

		namedWindow("Canny Camera", WINDOW_NORMAL);
		imshow("Canny Camera", cannyFrame);

	}

	return 0;
}
