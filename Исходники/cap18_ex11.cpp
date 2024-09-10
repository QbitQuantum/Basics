Vector<DiogoArc *> dijkstraFindShortestPath(DiogoNode *start, DiogoNode* finish)
{
    Vector<DiogoArc *> path;
    SimplePiorityQueue<Vector<DiogoArc *>> queue;
    Map<string, int> fixed;

    while (start != finish)
    {
        if (!fixed.containsKey(start->getName())) //If hasnt reached this node, meaning is the shortest/first path to this
        {
            fixed.add(start->getName(), getPathCost(path)); //Cached the visited node, with the current path cost because its the lowest (first one to arrive)

            for (DiogoArc *arc: *(start->getArcs())) //Queue up the next nodes to continue the checking, having the cost as the priority so the next path dequeued is the closest one
            {
                path.add(arc);
                queue.enqueue(path, getPathCost(path));
                path.remove(path.size() - 1);
            }
        }
        if(queue.isEmpty()) //went through all the arcs and paths and didnt reach the finish node
        {
            path.clear();
            return path; //return empty path;
        }

        path = queue.dequeue();
        start = path[path.size() - 1]->getFinish(); //change the start to the last node reached and continue the search for the finish node
    }
    return path;
}