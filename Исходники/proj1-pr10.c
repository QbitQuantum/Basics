int main()
{
    time_t hora;
    struct tm *timeinfo;
    int Nvoos;
    int Ndecolagens;
    int Npousos;
    
    char codigo_voo[7];
    char tipo_voo;
    int combustivel_voo;
    int aviso_voo;
    int pista_voo = 1;
    
    char codigos[64][7] = {"VG3001", "JJ4404", "LN7001", "TG1501",
    "GL7602", "TT1010", "AZ1009", "AZ1008", "AZ1010", "TG1506", "VG3002", "JJ4402", "GL7603",
    "RL7880", "AL0012", "TT4544", "TG1505", "VG3003", "JJ4403", "JJ4401", "LN7002", "AZ1002",
    "AZ1007", "GL7604", "AZ1006", "TG1503", "AZ1003", "JJ4403", "AZ1001", "LN7003", "AZ1004",
    "TG1504", "AZ1005", "TG1502", "GL7601", "TT4500", "RL7801", "JJ4410", "GL7607", "AL0029",
    "VV3390", "VV3392", "GF4681", "GF4690", "AZ1020", "JJ4435", "VG3010", "LF0920", "AZ1065",
    "LF0978", "RL7867", "TT4502", "GL7645", "LF0932", "JJ4434", "TG1510", "TT1020", "AZ1098",
    "BA2312", "VG3030", "BA2304", "KL5609", "KL5610", "KL5611"};
    
    srand(time(NULL));
    
    //Gerador de número de vôos, pousos e decolagens
    Nvoos = geraRand (0, 64);
    Ndecolagens = geraRand (0, Nvoos);
    Npousos = Nvoos - Ndecolagens;
    int voos = 0;
    int dec = Ndecolagens;
    int pouso = Npousos;
     
    FILA fila = cria_fila();
    
    for(voos = 1; voos <= Nvoos; voos++){
             strcpy(codigo_voo, codigos[voos]);
             
             if(pouso > 0 && dec >0){
                      if(geraRand(0,1)){
                                  tipo_voo = 'D';
                                  dec--;
                                  combustivel_voo = geraRand (24, 48);
                                  pista_voo = ((voos-1)%3)+1;
                                  }
                      else{
                           tipo_voo = 'P';
                           pouso--;
                           combustivel_voo = geraRand (0, 12);
                           
                           if (combustivel_voo == 0)
                                                   aviso_voo = 1;
                           
                           else
                                aviso_voo = 0;
                                
                           
                           pista_voo = ((voos - 1)%3) + 1;
                           if(pista_voo == 3 && tipo_voo == 'P' && aviso_voo == 0){
                                        pista_voo = ((voos)%3) + 1;
                                        }
                           }
                      }
                      
             else if (pouso == 0 && dec !=0){
                  tipo_voo = 'D';
                  dec--;
                  combustivel_voo = geraRand (24, 48);
                  pista_voo = ((voos-1)%3) + 1;
                  }
                  
             else if (pouso != 0 && dec == 0){
                  tipo_voo = 'P';
                  pouso--;
                  combustivel_voo = geraRand (0, 12);
                  
                  if (combustivel_voo == 0){
                                          aviso_voo = 1;
                                          }
                  else{
                       aviso_voo = 0;
                       }
                  
                  pista_voo = ((voos - 1)%3) + 1;
                  if(pista_voo == 3 && tipo_voo == 'P' && aviso_voo == 0){
                               pista_voo = ((voos)%3) + 1;
                               }
                  }
                  
             insere_fila(fila, codigo_voo, tipo_voo, combustivel_voo, aviso_voo, pista_voo);
             }
    
    printf ("\n              Aeroporto Internacional de Brasilia\n");
    hora = time(NULL);
    timeinfo = localtime(&hora);
    printf("                   Hora atual: %02d:%02d:%02d\n", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
    printf("                       Fila de pedidos:\n");
    printf("                          Nvoos: %d\n", Nvoos);
    printf("                       Ndecolagens: %d\n", Ndecolagens);
    printf("                         Npousos: %d\n\n", Npousos);
    printf("             Fila designada (na ordem) por pistas:\n\n");
    printf("                     ******Pista 1:******\n                           Pousos:\n\n");
    ver_fila(fila, 'P', 1);
    printf("\n                         Decolagens:\n\n");
    ver_fila(fila, 'D', 1);
    printf("\n                     ******Pista 2:******\n                           Pousos:\n\n");
    ver_fila(fila, 'P', 2);
    printf("\n                         Decolagens:\n\n");
    ver_fila(fila, 'D', 2);
    printf("\n                     ******Pista 3:******\n                           Pousos:\n\n");
    ver_fila(fila, 'P', 3);
    printf("\n                         Decolagens:\n\n");
    ver_fila(fila, 'D', 3);
    printf("\n");
     
    libera_fila (fila);
    return 0;   
}