/*
 * Function: aStar
 * --------------------
 * This function implements aStar search (variation of dijkstras with a heuristic)
 *
 * Preconditions:
 *
 *  @param: graph: The graph to be searched
 *          start: The start vertex
 *          end:The end vertex
 *  @return: returns a vector of vertexes containing the path (empty if no path)
 */
Vector<Vertex*> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {

    graph.resetData(); // reset
    Vector<Vertex*> path; // the return path
    Set<Vertex*> inQueue; // A vector holding the values that we have already put into the queue

    // INitialize every vertex to have infinite cost
    for(Vertex* s:graph.getVertexSet()){
        s->cost = POSITIVE_INFINITY;
    }

    PriorityQueue<Vertex*> pq; // A pq to see where to search next (cost+heuristic = priority)
    // Set start's cost to 0 + heuristicFxn val
    start->cost = 0 + heuristicFunction(start,end);
    // Enqueue start vertex
    pq.enqueue(start,0);
    start->setColor(YELLOW);
    inQueue.add(start);

    // While there are still elements in the pq to try
    while(!pq.isEmpty()){
        Vertex* v = pq.dequeue();
        inQueue.remove(v);

        v->visited = true;
        v->setColor(GREEN);

        // We can stop (reached end)
        if(v == end){
            // We have reached the end, deconstruct
            path.clear();

            Vertex* temp = v;
            path.insert(0,temp);

            while(temp->previous!=NULL){ // deconstruct
                temp = temp->previous;
                path.insert(0,temp);
            }
            break;
        }
        // For each unvisited neighbor of v vertex
        for (Vertex* n: graph.getNeighbors(v)){
            // And it's unvisited
            if(n->visited == false){
                // v's cost plus weight of edge
                Edge* e = graph.getEdge(v,n);
                double edgeCost = e->cost;
                double costToVertexN = v->cost + edgeCost;
                // If the costToVertexN < n->cost, we know this is a better way to get to
                // vertex n
                if(costToVertexN < n->cost){
                    n->cost = costToVertexN;
                    n->previous = v;
                    n->setColor(YELLOW);

                    // Check to see if pq already contains n
                    if(inQueue.contains(n)){ // Priority now includes heuristic
                        pq.changePriority(n,costToVertexN + heuristicFunction(n,end));
                    } else {
                        pq.enqueue(n,costToVertexN + heuristicFunction(n,end));
                    }
                }

            }
        }

    }
    return path;
}