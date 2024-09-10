int main(){
	
	clrscr();
	
	//Registros
		struct FILIA {
			char PAI[40];
			char MAE[40];
		
		};
		
		struct DATANASC {
			int DIA;
			int MES;
			int ANO;
			
		};

		struct ENDER{
			char RUA[30];
			char NUMERO[10];
			char COMPLEMENTO[30];
			char BAIRRO[30];
			char CIDADE[30];

		};

		struct FUNCIONARIO {
			char NOME[40];
			struct FILIA FILIACAO;
			struct DATANASC DTNASC;
			struct ENDER ENDERECO;
			int QTDAT;

		};

	//Constantes
		const int MAX = 1;
		const int COR1 = 10;
		const int COR2 = 12;

	//Variaveis
		struct FUNCIONARIO FUNC[30];
		int I,Cor,C,ANOATUAL;

	//Inicializacao Variaveis
		Cor = 0;
		C = 0;
		ANOATUAL = 0;
	//Leitura
		for(I = 0; I < MAX; I++){
			//NOME
			do{
				printf("Entre com o Nome do %i° Funcionário: ",(I+1));
				scanf("%s",&FUNC[I].NOME);
			}while(FUNC[I].NOME == "");
			//PAI
			do{
				printf("\n");
				printf("Entre com o Nome do Pai do %i° Funcionário: ",(I+1));
				scanf("%s",&FUNC[I].FILIACAO.PAI);
			}while(FUNC[I].FILIACAO.PAI == "");
			//MAE
			do{
				printf("\n");
				printf("Entre com o Nome da Mae do %i° Funcionário: ",(I+1));
				scanf("%s",&FUNC[I].FILIACAO.MAE);
			}while(FUNC[I].FILIACAO.MAE == "");
			//DIA
			do{
				printf("\n");
				printf("Entre com o Dia de Nascimento do %i° Funcionário: ",(I+1));
				scanf("%i",&FUNC[I].DTNASC.DIA);
			}while(FUNC[I].DTNASC.DIA < 0 && FUNC[I].DTNASC.DIA > 31);
			//MES
			do{
				printf("\n");
				printf("Entre com o Mes de Nascimento do %i° Funcionário: ",(I+1));
				scanf("%i",&FUNC[I].DTNASC.MES);
			}while(FUNC[I].DTNASC.MES < 0 && FUNC[I].DTNASC.MES > 12);
			//ANO
			do{
				printf("\n");
				printf("Entre com o Ano de Nascimento do %i° Funcionário: ",(I+1));
				scanf("%i",&FUNC[I].DTNASC.ANO);
			}while(FUNC[I].DTNASC.ANO < 0);
			//RUA
			do{
				printf("\n");
				printf("Entre com a Rua do %i° Funcionário: ",(I+1));
				scanf("%s",&FUNC[I].ENDERECO.RUA);
			}while(FUNC[I].ENDERECO.RUA == "");
			//NUMERO
			do{
				printf("\n");
				printf("Entre com o Numero do %i° Funcionário: ",(I+1));
				scanf("%s",&FUNC[I].ENDERECO.NUMERO);
			}while(FUNC[I].ENDERECO.NUMERO == "");
			//COMPLEMENTO
			do{
				printf("\n");
				printf("Entre com o Complemento do %i° Funcionário: ",(I+1));
				scanf("%s",&FUNC[I].ENDERECO.COMPLEMENTO);
			}while(FUNC[I].ENDERECO.COMPLEMENTO == "");
			//BAIRRO
			do{
				printf("\n");
				printf("Entre com o Bairro do %i° Funcionário: ",(I+1));
				scanf("%s",&FUNC[I].ENDERECO.BAIRRO);
			}while(FUNC[I].ENDERECO.BAIRRO == "");
			//CIDADE
			do{
				printf("\n");
				printf("Entre com a Cidade do %i° Funcionário: ",(I+1));
				scanf("%s",&FUNC[I].ENDERECO.CIDADE);
			}while(FUNC[I].ENDERECO.CIDADE == "");
			//QTDAT
			do{
				printf("\n");
				printf("Entre com a Quantidade de Anos Trabalhados do %i° Funcionário: ",(I+1));
				scanf("%i",&FUNC[I].QTDAT);
			}while(FUNC[I].QTDAT < 0);
			//Ano Atual
			do{
				printf("\n");
				printf("Entre com o Ano Atual: ");
				scanf("%i",&ANOATUAL);
			}while(ANOATUAL < 0);


		}

	//Processamento
		printf("\n\nFuncionários com mais de 30 Anos de Idade e 10 Trabalhados\n\n");
		printf("--\t Funcionario");
		printf("\n");
		for(I = 0; I < MAX; I++){
			//Cor
				if(Cor%2 == 0){
					textcolor(COR1);
				}else{
					textcolor(COR2);
				}

			//Resultado
				if(((ANOATUAL - FUNC[I].DTNASC.ANO) > 30) && (FUNC[I].QTDAT > 10)){
					if(C<10 && C>=0){ // até 9
						cprintf("00%i",(C+1));
						printf("\t");
						cprintf("%s",FUNC[I].NOME);
						printf("\n");
						Cor +=1;
						C+=1;
					}else if(C>=10 && C<100){ //10 até 99
						cprintf("0%i",(C+1));
						printf("\t");
						cprintf("%s",FUNC[I].NOME);
						printf("\n");
						Cor +=1;
						C+=1;
					}else if(C>=100){ // acima de 100
						cprintf("%i",(C+1));
						printf("\t");
						cprintf("%s",FUNC[I].NOME);
						printf("\n");
						Cor +=1;
						C+=1;
					}
				}
		}
	
		if(C == 0){
			printf("\t");
			cprintf("Nenhum Funcionario =>%i - %i = %i",ANOATUAL,FUNC[0].DTNASC.ANO,(ANOATUAL-FUNC[0].DTNASC.ANO));
		}
	
	//Impressao Valores Lidos
		//Muito Extenso Oo
		
	getch();
	return 0;
}