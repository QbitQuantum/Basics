void driverProgram(char *inputFile, char *outputFile)
{
	FILE *fin = fopen(inputFile, "r");
	FILE *fout = fopen(outputFile, "w");
	int source;
	graph *G = loadGraph(fin);
	int **cost = alocateMemoryForCost(G->noOfVertices);
	int *predecesors = allocateMemoryForPredecesors(G->noOfVertices);

	


	printf_s("Give the source vertex:");
	scanf_s("%d", &source);
	BellmanFord(G, source, cost, predecesors);
	for (int i = 0; i < G->noOfVertices; i++)
	{
		fprintf_s(fout, "%d\n", cost[1][i]);
	}

	while (true)
	{
		int destination;
		printf_s("Give the vertex to which you want to reconstruct the path:");
		scanf_s("%d", &destination);
		if (cost[1][destination] == infinite)
		{
			printf_s("there is no path to %d from %d\n", destination, source);
		}
		else if (cost[1][destination] == minfinite)
		{
			printf_s("it is a negative cycle cannot display path\n");
		}
		else
		{
			reconstructPath(source, destination, G, predecesors);
		}

		printf_s("Continue? \n1.Yes\n0.No\n");
		int dummy;
		scanf_s("%d",&dummy);
		if (dummy == 0)
		{
			break;
		}
	}
	fclose(fin);
	fclose(fout);
}