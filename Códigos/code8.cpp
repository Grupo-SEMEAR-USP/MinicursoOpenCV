/*
WorkshpS - Minicurso de Visão Computacional : Uma introdução a OpenCV com C++
- utilização de algoritmo de captura de cores para rastreamento de objetos
*/
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

 int main( int argc, char** argv )
 {
    //VideoCapture cap(0); //captura video da webcam
    VideoCapture cap("video.mp4");
    if ( !cap.isOpened() )  
    {
         cout << "Não foi possível abrir webcam ou video ..." << endl;
         return -1;
    }

 namedWindow("Control", CV_WINDOW_NORMAL);//criarei a janela "Control" para receber os ranges
//Crio minhas variáveis que realizaram o controle de reconhecimento das cores
 int iLowH = 37;
 int iHighH = 132;

 int iLowS = 109; 
 int iHighS = 255;

 int iLowV = 45;
 int iHighV = 255;

 //Crio trackbars na janela "Control" para as variaveis anterios 
 createTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
 createTrackbar("HighH", "Control", &iHighH, 179);

 createTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
 createTrackbar("HighS", "Control", &iHighS, 255);

 createTrackbar("LowV", "Control", &iLowV, 255);//Value (0 - 255)
 createTrackbar("HighV", "Control", &iHighV, 255);

 int iLastX = -1; 
 int iLastY = -1;

 //Captura temporariamente a imagem da camera
 Mat imgTmp;
 cap.read(imgTmp); 

 //crio uma imagem em preto do mesmo tamanho da imagem da camera
 //Mat imgLines = Mat::zeros( imgTmp.size(), CV_8UC3 );
 

 while (true){
     Mat imgOriginal;

     bool bSuccess = cap.read(imgOriginal); // irá ler um frame do video
     if (!bSuccess) //se não obtive sucesso
     {
        cout << "Impossivel de ler video" << endl;
        break;
     }

    Mat imgHSV;

    cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV);
    /*
    Função utilizada para converter uma cor de um espaço de cores para outro. Recebe como parâmetros
    a imagem de entrada, a imagem de saída e o tipo de tranformação, no caso do espaço RGB 2 para HSV
    */ 
 
    Mat imgThresholded;

    inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image (limita a imagem)
    /*
    Função responsável por reconhecer padrões por cores,e ela toma quatro argumentos: a imagem a ser analisada,
    o tom mínimo da cor e o tom máximo da cor no formato HSV e a imagem de saída com os limites encontrados
    */  
    
    //filtros morfológicos (remove pequenos objetos do primeiro plano)
    erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
    dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
    /*
    recebe como parâmetros imagem de entrada, imagem de saída, o kernel utilizado para aplicação do filtro
    podendo ser no formato MORPH_RECT (quadrado) , MORPH_CROSS (cruz), MORPH_ELLIPSE (cruz)
    */ 


    
    Moments oMoments = moments(imgThresholded);
    /*
    Calcula os momentos da imagem Thresholded atráves da função moments 
    (ele calcula os contornos/areas encontradas) e guarda na variavel oMoments na estrutura (class)
    Moments da biblioteca
    */
   // Pego os momentos espaciais 
    double dM01 = oMoments.m01; //pega tamanho em y
    double dM10 = oMoments.m10; //pega tamanho em x
    double dArea = oMoments.m00;//area do momento

    // Se a area <= 10000, Eu considero que não existe objeto na imagem e isso ocorre por causa do
    //ruído, a area não é zero
    if (dArea > 10000){
        //calcula a posição da bola
        int posX = dM10 / dArea;
        int posY = dM01 / dArea;        
        if (iLastX >= 0 && iLastY >= 0 && posX >= 0 && posY >= 0){
            //Desenha um circulo vermelho do ponto anterior para o ponto atual
            circle(imgOriginal,Point(posX,posY),50,Scalar(0,0,255),3);
            //line(imgLines,Point(posX,posY),Scalar(0,0,255));
        }
        iLastX = posX;
        iLastY = posY;
    }
    namedWindow("Thresholded Image",WINDOW_NORMAL);
    namedWindow("Original",WINDOW_NORMAL);
    imshow("Thresholded Image", imgThresholded); //show the thresholded image

    //imgOriginal = imgOriginal + imgLines;
    imshow("Original", imgOriginal); //show the original image

    if (waitKey(30) == 27) //espera pela tecla 'esc' ser pressionada, se for o loop é quebrado
    {
        cout << "tecla ESC foi pressionado pelo usuario" << endl;
        break; 
    }
    
}

   return 0;
}
