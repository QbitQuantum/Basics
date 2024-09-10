/* Inicializacao do programa */
int main(){
  int n_contatos = 0; // Conta o numero de contatos ja inseridos
  int resp, telefone_lido, i;
  contato agenda[70];
  char parametro, inicial;
  char nome_lido[TAM];
  bool ordenado = False; /* Inicialmente a agenda não esta ordenada */
        
  do{
    parametro = getchar();
    switch(parametro){
    case('i'): /* Insere um novo contato na agenda */
      getchar();
      scanf("%d", &(agenda[n_contatos].tel));
      getchar();
      scanf("%[^\n]", agenda[n_contatos].nome);
      getchar();
      //for(i = 0; i <= n_contatos; i++)
      //  printf("%d****%-40s %d\n", n_contatos, agenda[i].nome, agenda[i].tel); 
           
      n_contatos++;
      ordenado = False;
      break;
            
    case('r'): /* Faz a remocao de um contato da agenda */
      if(n_contatos > 0){
	getchar();
	scanf("%d", &telefone_lido);
	getchar();
               
	resp = buscaTelefone(agenda, telefone_lido, n_contatos);
	if(resp == -1)
	  printf("Nao foi possivel remover: Contato inexistente!\n\n");
	else{
	  printf("Contato: %-40s %d\nFoi removido com sucesso!\n\n", agenda[resp].nome, agenda[resp].tel);
	  remover(agenda, resp, n_contatos);
                 
	  n_contatos--;
	}
      }
      else
	printf("Nao foi possivel remover: Contato inexistente!\n\n");
               
      break;
         
    case('n'): /* Busca um nome na agenda */
      if(ordenado == False){
	// separa(agenda, 0, n_contatos);
	ordenaNome(agenda, 0, n_contatos-1);            
	ordenado = True;
      }
      getchar();
      scanf("%[^\n]", nome_lido);
      getchar();
      resp = buscaNome(agenda, nome_lido, 0, n_contatos);
                
      if(resp == -1)
	printf("Contato nao encontrado!\n\n");
      else
	printf("%-40s %d\n\n", agenda[resp].nome, agenda[resp].tel);
                
      break;
                
    case('t'): /* Busca um telefone na agenda */
      getchar();
      scanf("%d", &telefone_lido);
      getchar();
      resp = buscaTelefone(agenda, telefone_lido, n_contatos);
                
      if(resp == -1)
	printf("Contato nao encontrado!\n\n");
      else
	printf("%-40s %d\n\n", agenda[resp].nome, agenda[resp].tel);
                
      break;
                
    case('p'): /* Faz a impressao de todos os contatos em ordem alfabetica */
      if(ordenado == False){
	ordenaNome(agenda, 0, n_contatos-1);
	ordenado = True;
      }
      if(n_contatos > 0){ /* Se nao existem contatos na agenda entao nao e necessario imprimir */
	inicial = agenda[0].nome[0];
	printf("----%c----\n", inicial);
	     
	for(i = 0; i < n_contatos; i++){
	  if(agenda[i].nome[0] == inicial)
	    printf("%-40s %d\n", agenda[i].nome, agenda[i].tel);
	  else{
	    printf("----%c----\n", agenda[i].nome[0]);
	    inicial = agenda[i].nome[0];
	    printf("%-40s %d\n", agenda[i].nome, agenda[i].tel);
	  }
	}
	putchar('\n');
      }
      else
	printf("\n");
      break;
    }
  } while(parametro != 'f');
    
  // system("pause");
    
  return 0;
}