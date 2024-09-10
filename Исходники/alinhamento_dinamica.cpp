int main() {
    
    elemento **mat;
    int ntestes;
    char sequencia1[100];
    char sequencia2[100];
    char novaseq1[200]= "";
    char novaseq2[200]= "";
    //tamanho = quantidade de elementos iguais
    int tamanho;
    //n = tamanho sequencia 1
    int n;
    //m = tamanho sequencia 2
    int m;
    
    //ntestes é a quantidade de testes que terei no meu programa
    
    scanf("%d", &ntestes);
    
    // esse for pega as 2 proximas sequencias e resolve o problema pra elas, e assim para todo o par de sequencias
    for(int i=0;i<ntestes;i++) {
            scanf("%s", sequencia1);
            scanf("%s", sequencia2);
            n = strlen(sequencia1);
            m = strlen(sequencia2);
            //funcao que cria a matriz
            alinhamento(sequencia1,sequencia2,&mat);
            //funcao recursiva que pega o resultado e coloca
            tamanho = resposta(mat,sequencia1,sequencia2,novaseq1,novaseq2,m,n,0);
            printf("Tamanho: %d",tamanho);
            printf("\nAlinhamento:  \n");
            printf("%s \n",novaseq1);
            printf("%s \n",novaseq2);
            strset(novaseq1,0);
            strset(novaseq2,0);
            free(&mat);
            printf("\n");
    }
    return 0;
}