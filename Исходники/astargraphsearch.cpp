Node* AStarGraphSearch::runSearch()
{
    // Declare Variables
    bool  goalFound;
    Node* current;
    Node* start = feeder->getNode(initNodeID);

    g_score[initNodeID] = 0;
    h_score[initNodeID] = heuristic->evaluateHeuristic(start);
    f_score[initNodeID] = g_score[initNodeID] + h_score[initNodeID];

    addNodeToFrontier(start);

    while (numberOfNodesInFrontier > 0)
    {
        current = popFrontier(); /*---- GUI UPDATE ----*/ notifyObservers(current->getNodeID(),NODE_UPDATE);

        goalFound = goalTest(current);
        if (goalFound)
            break;

        addNodeToExploredSet(current);

        int currentID = current->getNodeID();
        std::vector <Edge*> edgeSuccessors;
        feeder->getSuccessors(current,&edgeSuccessors);
        int numberOfSuccessors = edgeSuccessors.size();
        for (int i=0; i<numberOfSuccessors; i++)
        {
            Node* neighbour = edgeSuccessors[i]->getTarget(); /*---- GUI UPDATE ----*/ notifyObservers(edgeSuccessors[i]->getEdgeID(),EDGE_UPDATE);
            if (isNodeInExploredSet(neighbour))
                continue;

            int neighbourID = neighbour->getNodeID();

            int posInOpenSet = isNodeInFrontier(neighbour);
            if (posInOpenSet == -1)
            {
                double g_neighbour   = g_score[currentID] + edgeSuccessors[i]->getCost();
                g_score[neighbourID] = g_neighbour;
                h_score[neighbourID] = heuristic->evaluateHeuristic(neighbour);
                f_score[neighbourID] = g_neighbour + h_score[neighbourID];
                neighbour->setParent(current);
                addNodeToFrontier(neighbour);
            }
            else
            {
                double newPath_g_score = g_score[currentID] + edgeSuccessors[i]->getCost();
                if (newPath_g_score < g_score[neighbourID])
                {
                    //update g,f scores and parent, h score stays the same
                    g_score[neighbourID] = newPath_g_score;
                    f_score[neighbourID] = newPath_g_score + h_score[neighbourID];
                    neighbour->setParent(current);
                    openSet.erase(openSet.begin() + posInOpenSet);
                    numberOfNodesInFrontier--;
                    addNodeToFrontier(neighbour);
                }
            }
        }
    }

    if (goalFound)
        return current;
    else
        return NULL;
}