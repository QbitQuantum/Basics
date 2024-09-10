		void PathSearch::update(long timeslice)
		{

			startTime = clock();

			while (1)
			{

				currentTime = clock();
				float _elapsedTime = currentTime - startTime;

				if (_elapsedTime < timeslice)
				{
					SearchNode* _currentNode = searchQueue->front();
					searchQueue->pop();

					if (_currentNode != goalNode)
					{

						for (int i = 0; i < _currentNode->edges.size(); i++)
							if (!nodeState[_currentNode->edges[i]])
							{

								PlannerNode* _newPlanner = new PlannerNode;
								_newPlanner->parent = _currentNode->myPlanner;
								_newPlanner->Vertex = _currentNode->edges[i];
								_currentNode->edges[i]->myPlanner = _newPlanner;
								_currentNode->edges[i]->heuristicCost = distance(_currentNode->edges[i]->data, goalNode->data);
								_currentNode->edges[i]->givenCost = _currentNode->givenCost + distance(_currentNode->edges[i]->data, _currentNode->myPlanner->Vertex->data);
								cleanMe.push_back(_newPlanner);

								searchQueue->push(_currentNode->edges[i]);
								nodeState[_currentNode->edges[i]] = true;

							}

					}
					else
					{

						PlannerNode* _cPlanner = goalNode->myPlanner;

						while (1)
						{

							solution.push_back(_cPlanner);

							if (_cPlanner->Vertex == startNode)
								break;

							if (_cPlanner->Vertex != startNode && _cPlanner->Vertex != goalNode)
								_cPlanner->Vertex->data->setFill(0xFF0000FF);

							_cPlanner = _cPlanner->parent;

						}

						reachedGoal = true;
						return;

					}

				}
				else return;

			}

		}