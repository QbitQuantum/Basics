    void randomize()
    {
	Timer t;
	for(int i = 1;i < 20;i++)
	{
	   cout << "\nFor operation : " << i;
	   nodes = i;

	   //general initializations
	   visited = new int [nodes];
	   *edges = new int [nodes];
	   for(int i = 0;i < nodes;i++) edges[i] = new int [nodes];
	   for(int row = 0;row < nodes;row++)
	       for(int col = 0;col < nodes;col++)
	       {   visited[row] = 0;
		   edges[row][col] = -1;
	       }
	   //-----------------------

	   for(int k = 0;k < nodes;k++)
	      for(int l = 0;l < nodes;l++)
	      {
		  if(edges[k][l] != -1) continue;
		  edges[k][l] = rand() % 2;
		  edges[l][k] = 0;
	      }

	  t.start();topo_sort();t.stop();stck.clear();
	  cout << " time taken is : " << t.time() << " seconds";
	}
    }