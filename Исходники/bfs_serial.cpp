void bfs1 (Graph* graph) {

    queue<Vertex*> Q;

    map<int, Vertex*>* ord_adj_list = new map<int, Vertex*>();
    for (auto vertex : *graph->get_adj_list()) {
        ord_adj_list->insert( pair<int, Vertex*> (vertex.first->getID(), vertex.first) );
    }

    for (auto vertex : *ord_adj_list) {

        if (vertex.second->getColor() != 0)
            continue;

        vertex.second->setColor(1);
        Q.push(vertex.second);

        //while queue not empty
        while (!Q.empty()) {
            //take the first element
            Vertex* v = Q.front();
            Q.pop();

            for (Vertex* to : *graph->getEdges(v)) {
                Vertex* u = graph->getVertex(to);

                if (u->getColor() == 0) {
                    u->setColor(1);
                    u->setParent(v);
                    Q.push(u);
                }
            }
        }
    }

    ord_adj_list->clear();
}