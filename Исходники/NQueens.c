# include <stdio.h>
# include <stdlib.h>
# include <time.h>
int N;  //For N * N ChessBoard
int flag;
void printArray(int a[]);        /* Just to Print the Final Solution */
void getPositions(int a[], int n1, int n2);  /* The Recursive Function */
int main_NQueens()
{
	int *a;
	int ctr = 0;
	printf("\nTHE N QUEENS PROBLEM ");
	printf("\nNumber Of Rows(N) For NxN Chessboard.");
	scanf_s("%d", &N);
	a = (int *)(malloc(sizeof(int)*N));
	printf("\nAll possible Solutions ..  \n");
	printf("\nIn Each of the solutions the Coordinates of the N-Queens are given (Row,Col) .");
	printf("\nNote that the Rows and Colums are numbered between 1 - N :\n");
	for (ctr = 0; ctr<N; ctr++)
		getPositions(a, 0, ctr);
	getchar();
	getchar();
}