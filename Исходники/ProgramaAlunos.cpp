/*start function*/
int gravacao ()
{
    system("title grava e le arquivo");
    FILE *p;
    char nome[20],tele[10], opcao;
    
    
    p = fopen("dados.001","rt");
    
    if (p==NULL){
                 
                 printf("\n ....:Programa Dados Alunos:.....\n\n");
                 printf("\n arquivo nao existe...novo criado\n");
                 p= fopen("dados.001","wt");
                 if (p == NULL) return (-1);
                 }else{
                       printf("\t ....:Programa Dados Alunos:.....\n\n");
                       printf("\nlogado\n");
                       fclose(p);
                       p = fopen("dados.001", "at");
                       }
                while (1){
                      printf("\n<C A D A S T R O>\n\n\n\n");                      
                      printf("\nNome :");
                      scanf("%s", nome);
                      printf("\nTelefone :");
                      scanf("%s", tele); 
                
                 printf("\nconfirma gravar este registro? [s/n]:");
                 do{
                      opcao = getchar();
                      }while (tolower(opcao) != 's' && tolower(opcao) != 'n');
                      
                      if (tolower(opcao) == ' '){
                           fprintf(p, "%s %s\n", nome, tele);
                           printf("\n registro gravado");
                         }
                         
                         else{printf("\n registro nao gravado");
                              }
                              
                 printf("\ndeseja continuar gravando este registro? [s/n]:");
                   do{
                      opcao = getchar();
                      }while (tolower(opcao) != 's' && tolower(opcao) != 'n');
                      if (tolower(opcao) == 'n'){
                           printf("fim da gravacao");
                           break;}
                            
                            }                                                             
                                                                                                
                 fprintf(p,"%s %s \n",nome, tele);
                 
                                
                                                  
                 fclose(p);
                                    
                 main();
        
    

}