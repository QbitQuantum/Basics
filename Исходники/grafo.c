void InitWithAdjMatrix(AdjMatrixGraph *graph, EdgeList *edge_list, FreeList *free_list, Table *table){
    int i, j;
    
    CreateEdgeList(edge_list, graph->m);
    for (i = 0; i < graph->n; i++){
        for (j = 0; j < i; j++){ 
        /* Adiciona arestas apenas uma vez. 
        Para adicionar duas basta colocar j < graph->n */
            if (graph->matrix[i][j] == 1){
                AddEdge(i, j, NULO, edge_list); /* Adciona aresta descolorida ao EdgeList */
            }
        }
    }
    CreateTable(table, graph->n, graph->delta);
    for (i = 0; i < table->sizeX; i++){
        for (j = 0; j < table->sizeY; j++){
            table->matrix[i][j].status = FALSE;
            table->matrix[i][j].adj = NULO;
            table->matrix[i][j].cPointer = NULL;
        }
    }
    CreateFreeList(free_list, graph->n, graph->delta, table);
}