void pintaRegiao(CelPixel *cab, Imagem *R, Imagem *G, Imagem *B, 
		 float cor[3])
	/*	A função recebe uma lista encadeada de pixels que fazem parte
		de uma subregião, três imagens (canais) e um vetor com as cores-
		padrão. Para cada posição do pixel, colore cada cor corresponden-
		te nas imagens R, G e B. */
{
	int i, j;
	CelPixel *pixel_atual;
	pixel_atual = cab->prox;
	/*printf("cor 1 = %f", cor[0]);*/
		
	while(pixel_atual != NULL)
	{
		i = pixel_atual->x; j = pixel_atual->y;
		/*printf("%d ", i);*/
		
		setPixel(R, i, j, cor[0]);
		setPixel(G, i, j, cor[1]);
		setPixel(B, i, j, cor[2]);
		pixel_atual = pixel_atual->prox;
	}
}