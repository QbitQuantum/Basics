int main(){	
	int chave = 0;	
	FILE *arq, *arqo, *arqw;
	
	arq = fopen("entrada-transposicao.txt", "r");
	arqo = fopen("texto-original.txt", "r");
	arqw = fopen("saida-transposicao.txt", "w");
	
	if(arq == NULL) printf("Não abriu");
	
	char dados[10000], dados1[10000];
	fgets(dados, 10000, arq);
	fgets(dados1, 10000, arqo);
	
	int i=0, t, j, ic; 
	
	for(i=0; i<strlen(dados1); i++){
		if(dados1[i]==10) dados1[i] = '\0';
	}
	
	if(dados == NULL) printf("Não leu fgets");
	
	
	for(t=1; t<256; t++){
		char *chavx = (char *)malloc(sizeof(char)*strlen(dados));
		int tamanho_codificado = strlen(dados);
		int ldecod = trunc(tamanho_codificado / t); //quantidade de linhas
		int cdecod = trunc(tamanho_codificado / ldecod);
			
		int mdecod[cdecod][ldecod];
		ic = 0;
		int cc=0, cl=0;
		int max_linha = strlen(dados) / t; //t vai ser a chave agora
		int inc = 0;
		for(i=0; i<cdecod; i++){
			for(j=0; j<ldecod; j++){
				if(dados[inc]!=10){
					mdecod[i][j] = dados[inc++];
				}
			}
		}	
		
		inc = 0;
		for(i=0; i<ldecod; i++){
			for(j=0; j<cdecod; j++){
				chavx[inc++] = mdecod[j][i];
			}
		}
		int ehc = 0;
		for(i=strlen(chavx)-1; i>0; i--){
			if(chavx[i]!=' ') break;
			if(chavx[i]==' ') chavx[i] = '\0';
		}
		if(strcmp(chavx, dados1)==0){
			printf("---------------\nChave descoberta: %d\n--------------------\n", t);
			break;
		}else{
			//printf("chavx =>> [%s]==[%s]\n", chavx, dados1);
		}
	}
	
	
	/*int i = 0, j = 0, tamanho_linhas = 0, icol = 0, ilinha = 0;
	tamanho_linhas = trunc(strlen(dados) / chave) + 1;
	int matrix[tamanho_linhas][chave];
	for(i=0; i<tamanho_linhas; i++){
		for(j=0; j<chave; j++){
			matrix[i][j] = ' '; //"Limpar" a matriz
		}
	}	
	for(i=0; i<strlen(dados); i++){
		int k = (int)dados[i];
		if(k!=10) matrix[ilinha][icol] = k; //ignorar a quebra de linha
		//int gerado = codificar(k, chave);
		//int decodificado = decodificar(gerado, chave);
		//printf(">%c - %c\n", gerado, decodificado);
		icol++;
		if(icol >= chave){
			icol = 0;
			ilinha++;
		}
	}
	
	printf("--------------%dx%d----------------\n", tamanho_linhas, chave);
	for(i=0; i<tamanho_linhas; i++){
		for(j=0; j<chave; j++){
			printf("%c", matrix[i][j]);
		}
		printf("\n");
	}
	printf("------------------------------\n");
	
	printf("Texto codificado: \n");
	char codificado[tamanho_linhas*chave];
	int ic = 0;
	for(i=0; i<chave; i++){
		for(j=0; j<tamanho_linhas; j++){
			printf("%c", matrix[j][i]);
			codificado[ic++] = matrix[j][i];
		}
	}
	printf("\n");
	printf("=================================\nTexto decodificado:\n");
	int tamanho_codificado = strlen(codificado);
	int ldecod = tamanho_codificado / chave; //quantidade de linhas
	int cdecod = tamanho_codificado / ldecod;
	int mdecod[cdecod][ldecod];
	ic = 0;
	int cc=0, cl=0;
	for(i=0; i<strlen(codificado); i++){
		mdecod[cc][cl] = codificado[i];
		cc++;
		if(cc>=chave){
			cc=0;
			cl++;
		}
	}
	for(i=0; i<ldecod; i++){
		for(j=0; j<cdecod; j++){
			printf("%c", matrix[i][j]);
		}
	}
	printf("\n========================================\n"); */
	return 0; 
}