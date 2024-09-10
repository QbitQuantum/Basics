//Método Main - Entry Point do Programa
int main91()
{
	//Título do Programa e autor
	printf(" << UEFS - PGCA 2014.1 - Programa estruct basico>>");
	printf("\n\n ## Autor: Leonardo Melo\n\n");

	tipoProduto produto;

	printf_s("\nDigite o NOME do produto: ");
	gets_s(produto.nome);
	fflush(stdin);

	printf_s("\nDigite o PRECO do produto: ");
	scanf_s("%f", &produto.preco);
	fflush(stdin);

	printf_s("\nDigite o FABRICANTE do produto: ");
	gets_s(produto.fabricante);
	fflush(stdin);

	printf_s("\n\nExibindo os dados do produto");

	printf_s("\n\n NOME do Produto: %s", produto.nome);
	printf_s("\n PRECO do Produto: %.2f", produto.preco);
	printf_s("\n FABRICANTE do Produto: %s", produto.fabricante);

	//Pula duas linhas e Pausa a Tela (Utilizando comandos DOS)
	printf("\n\n\n");
	system("pause");

	//Retorno do método main
	return(EXIT_SUCCESS);
}