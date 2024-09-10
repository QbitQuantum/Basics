Cor Visao::gravaCor(){        
    Cor cor = Cor();

    while (true){ 
        clock_t start=tempo();  

        cam >> imagem;

        cvtColor(imagem, imagemHSV, COLOR_BGR2HSV); 

        imshow("Imagem Normal", imagem); 
        moveWindow("Imagem Normal", 0, 0);  

        inRange(imagemHSV, Scalar(pontos[0]-variacaoH, pontos[1]*(1-variacao), pontos[2]*(1-variacao)),
         Scalar(pontos[0]+variacaoH, pontos[1]*(1+variacao), pontos[2]*(1+variacao)), imagemTratada); 
        
        //medianBlur(imagemTratada, imagemTratada, 3);     

        imshow("Calibragem", imagemTratada); 
        moveWindow("Calibragem", 640, 0);

        setMouseCallback("Imagem Normal", corPixel, 0);

        char key =  waitKey(1);    
        if (key == 27){
            for (int i=0; i<10; i++){
                destroyAllWindows();
                waitKey(1);  
            }
            break; 
        }
        if (clique == true){
            cor.corH = pontos[0];
            cor.corS = pontos[1];
            cor.corV = pontos[2];

            if (key == 32){ 
                for (int i=0; i<10; i++){
                    destroyAllWindows();
                    waitKey(1);  
                }
                cout << "Cor Calibrada" << endl;
                clique = false;
                pontos[0] = 0; pontos[1] = 0; pontos[2] = 0;  
                break; 
            }            
        }        
    }
    return cor;
}