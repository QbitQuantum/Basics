AIMove AIPlayer::findBestMove(Grid& grid)
{
	AIMove bestMove;
	TreeHelper helper;

	std::vector<Point> availablePositions;
	std::vector<Point> adjacent;

	grid.getAllAvailablePositions(availablePositions);

	//Run the minmax for all of them.
	for (unsigned int i = 0; i < availablePositions.size(); ++i)
	{
		Minimax minimax;

		Point p = availablePositions[i];
		grid.getAdjacentPositions(p, adjacent);

		int win = checkForWin(grid, p.x, p.y); 

		//Create root node for the minimax.
		Node root;

		//The number of children for this node is equal to the number of adjacent nodes.
		root.addChild(adjacent.size());
		root.setValue(win);
		root.setParent(nullptr);

		//For each adjacent node.
		std::vector<Node*>& nodes = root.getChild();
		for (unsigned int n = 0; n < nodes.size() ; ++n)
		{
			//Set value to -1, assuming the other player will play in that position.
			nodes[n]->setValue(-1); //first level we assume is bad because the player will block our game.

			//Check for 2nd level adjacency.
			//Not for each first level adjacent node, get the adjacent nodes to that and build the second level.
			//So we can try to predict if its going to be good or not.
			Point pa2nd = adjacent[n];
			std::vector<Point> adjacent2nd;
			grid.getAdjacentPositions(pa2nd, adjacent2nd);

			//Add the number of children equal to the number of adjacent nodes.
			nodes[n]->addChild(adjacent2nd.size());
			std::vector<Node*>& secondLevel = nodes[n]->getChild();
			for (unsigned int l2 = 0; l2 < secondLevel.size() ; ++l2)
			{
				//int winWin = checkForWin(grid, adjacent2nd[l2].x, adjacent2nd[l2].y);
				//give it the weight of victory
				secondLevel[l2]->setValue(1); 
			}

			//Run the minimax.
			minimax.minmax(&root, true);

			int value = root.getValue();
			if (bestMove.value < value)
			{
				bestMove.value = value;
				bestMove.position = p;
			}
		}
		adjacent.clear();
	}

	return bestMove;
}