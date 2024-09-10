int main()
{
	criarTabuleiro();
	mostrarTabuleiro();

	Player jogo = NULL;

	int turno = 1;
	int fim = 0;
	int x0, y0, xf, yf, jAtual = 0;
	char jogador1[10], jogador2[10], jogadorAtual[10];


	puts(" ");
	do
	{
		if (turno == 1) {
			printf("=== JOGADOR 1 insira o nome ===\n");
			scanf("%s", jogador1);
			printf("=== JOGADOR 2 insira o nome ===\n");
			scanf("%s", jogador2);
			
			system("cls");
			fflush(stdin);
		}

		strcpy(jogadorAtual, jogador1);

		if (jAtual > 2) {
			strcpy(jogadorAtual, jogador1);
			jAtual = 0;
		}
		if (jAtual == 1)
			strcpy(jogadorAtual, jogador2);

		printf("======================================================\n");
		printf("TURNO: %d\nJOGADOR: %s", turno, jogadorAtual);
		puts(" ");
		mostrarTabuleiro();

		printf("==== Insira um movimento ===\n");
		printf("\t ESCOLHA A CORDENADA DA PEÇA A MOVIMENTAR [x0, y0]\n");
		printf("\t x0 = \n");
		scanf("%d", &x0);
		printf("\t y0 = \n");
		scanf("%d", &y0);
		printf("\t ESCOLHA A CORDENADA O DESTINO DA PEÇA [xf, yf]");

		scanf("%d %d", &xf, &yf);
		fflush(stdin);

		//fazerMovimento(x0)
		turno++;

		mostrarTabuleiro();
		printf("FIM DE JOGADA ? [1-sim, 0-não]\n");
		scanf("%d", &fim);

		fflush(stdin);
		jAtual++;

		if (vencerPartida() == 1)
		{
			system("cls");
			printf("PARABéNS O JOGADOR 1 VENCEU A PARTIDA!!!");
			break;
		}
		if (vencerPartida() == 2)
		{
			system("cls");
			printf("PARABéNS O JOGADOR 2 VENCEU A PARTIDA!!!");
			break;
		}

	} while (vencerPartida() == 0);


	getchar();
	return 0;
}