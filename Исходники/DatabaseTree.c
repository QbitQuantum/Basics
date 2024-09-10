int main()
{
	int key,age;
	char name[MAXSTR],operacao;
	FILE *fIndex,*fTerminal;
	Register reg,*cons;
	float start,end,timeElapsed;

	fIndex = checkFileIndex();
	fTerminal = checkFileTerminal();
	do
	{
		fseek(fIndex,0,SEEK_SET);
		fseek(fTerminal,0,SEEK_SET);
		scanf("%c%*c",&operacao);
		operacao = tolower(operacao);
		switch(operacao)
		{
			//Sair do Programa
			case 'e':
			{
				fclose(fIndex);
				fclose(fTerminal);
				exit(1);
				break;
			}

			//Insere Registro
			case 'i':
			{
				scanf("%d%*c",&key);
				getstr(name,MAXSTR);
				scanf("%d%*c",&age);
				if(fIndex && fTerminal)
				{
					reg.key = key;
					strcpy(reg.name,name);
					reg.age = age;
					if(!insereRegistro(fIndex,fTerminal,&reg))
					{
						printf("chave ja existente: %d\n",key);
					}
				}
				break;
			}

			//Consulta Regisro
			case 'c':
			{
				scanf("%d%*c",&key);
				start = (float)clock()/CLOCKS_PER_SEC;
				cons = consultaRegistro(fIndex,fTerminal,key);
				end = (float)clock()/CLOCKS_PER_SEC;
				timeElapsed = end - start;
				if(cons) printf("chave: %d\n%s\n%d\n",key,cons->name,cons->age);
				else printf("chave nao encontrada\n");

				printf("query rapida: %f segundos\n",timeElapsed);
				start = (float)clock()/CLOCKS_PER_SEC;
				cons = slowQuery(fTerminal,key);
				end = (float)clock()/CLOCKS_PER_SEC;
				timeElapsed = end - start;
				printf("query lenta: %f segundos\n",timeElapsed);
				break;
			}

			//Remove Registro
			case 'r':
			{
				scanf("%d%*c",&key);
				if(!removeRegistro(fIndex,fTerminal,key))
				{
					 printf("chave nao encontrada\n");
				}
				break;
			}

			//Imprime Árvore
			case 'p':
			{
				imprimeArvore(fIndex,fTerminal);
				break;
			}

			//Imprime nós Terminais
			case 'f':
			{
				imprimeNosTerminais(fTerminal);
				break;
			}
		}

	}while(operacao != 'e');

	return 0;
}