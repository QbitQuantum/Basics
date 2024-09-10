DWORD WINAPI waiting_for(LPVOID p)
{            
      int ret,first = 1;
      int i=0;
      unsigned char c;
      int flag;
      unsigned short crc;
      int u;
      
      struct Frame *f;
      
      f = (struct Frame*) p;
   
      f->length =0; 
      f->type = 0; 
      
      if(side == 0)//LADO IZQUIERDO (EMISOR)
      {
          while(1)
          {                    
              flag = 0;
              
              while(flag ==0)
              {
                 if(first == 1)//es el primer caracter, por tanto esperamos hasta que exista uno en el buffer que poder leer
                  {
                    f_esperar_leer(INFINITE);
                    clearFrame(f);//aprovechamos para limpiar la trama
                    i=0;    
                  }
                  else
                  {
                    f_esperar_leer(800);//este ya no es el primer caracter
                  }
                  
                  ret=f_leer(&c);                
                  first= 0;
                  		
                  switch (ret)
                  {               
                     case 0://sin problemas al leer                   
                        fI->body[i] = c;
                        fI->length++;
            				i++;          				 
                     break;
           				
            			case -1://sobreescritura
            				if(mode == 1){fprintf(stderr,"Error de sobrescritura al leer\n");}		
           				break;
           				
            			case -2://no queda nada que leer
                                          
            			   //evaluamos la trama
                        fI->type = evaluateFrame(fI);  
                                 
            			   if(mode == 1)
                        { 
               			   printf("\n-------------------------------RECEIVED------------------------------------\n");                                                                        			   
               			   if(fI->type != -1)
               			   {
                           	SetConsoleTextAttribute(hstdoutI, FOREGROUND_GREEN); //Letra verde para trama correcta
                           }
                           else
                           {
                              SetConsoleTextAttribute(hstdoutI, FOREGROUND_RED); //Letra roja para trama incorrecta
                           }
               			   for(u=0;u<fI->length;u++)
                           {
                              printData(fI->body[u]);
                              printf(" ");
                           }
                           
                           printf("\n");
                           SetConsoleTextAttribute(hstdoutI, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE); //Letra blanca
                        }
                        
            			   //indicamos que hay una trama lista
                        ReleaseSemaphore(side_I_data_ready,1,NULL);
                        
                        //reiniciamos los valores de control
                        first=1;
                        flag = 1;
           				break;
           				
            			case -3:
                        fprintf(stderr,"\nComunication off\n");
                        conexionOK = 0;
                        ExitThread(1);
           				break;
           			} 
               } 
          } 
       }
       else//LADO DERECHO (RECEPTOR)
       { 
          while(1)
          {       
            flag = 0;
             
              while(flag ==0)
              {
                  if(first == 1)//es el primer caracter, por tanto esperamos hasta que exista uno en el buffer que poder leer
                  {
                     f_esperar_leer(INFINITE);
                     clearFrame(f);//aprovechamos para limpiar la trama
                     i=0;   
                  }
                  else
                  {
                      f_esperar_leer(800);//no es el primera caracter
                  }
                  
                  ret=f_leer(&c);                
                  first = 0;
                
                  switch (ret)
                  {
                	    case 0://sin problemas al leer
                           fD->body[i] = c;
                           fD->length++;
                				i++;
                		break;
               				
                		case -1://sobreescritura
                			if(mode == 1){fprintf(stderr,"Read overrrun error\n");}		
               		break;
               				
                		case -2://no queda nada que leer
                        
                        //evaluamos la trama
                        fD->type = evaluateFrame(fD);
                        
                        if(mode == 1)
                        {
                           printf("\n-------------------------------RECEIVED------------------------------------\n");
                                                 			                   			                 			    
                   			if(fD->type != -1)
               			   {                         
                           	SetConsoleTextAttribute(hstdoutD, FOREGROUND_GREEN); //Letra verde para trama correcta         
                           }
                           else
                           {
                              SetConsoleTextAttribute(hstdoutD, FOREGROUND_RED); //Letra roja para trama incorrecta
       
                           }
                   			for(u=0;u<fD->length;u++)
                           {
                              printData(fD->body[u]);
                              printf(" ");
                           }                                            
                           printf("\n");
                           SetConsoleTextAttribute(hstdoutD, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE); //Letra blanca
                        }
                        else
                        {
                           //para que cuando no este en modo debug muestre los datos que recibe
                           if(fD->type == dataFrame)
                           {
                              catchData(fD);
                              printf("\nReceived: %s",fD->data);
                           }
                           
                        }
                        
                        //indicamos que hay una trama lista
                			ReleaseSemaphore(side_D_data_ready,1,NULL);
                			
                			//reiniciamos los valores de control
                			first=1;
                		   flag = 1;                                     
               		 break;
               				
                		case -3://la comunicacion se ha cortado
                			fprintf(stderr,"\nComunication offn\n");
                			conexionOK = 0;
                			fD->type = -5;
                			ExitThread(1);
               		break;
               	} 
               }  
            } 
      }       
}