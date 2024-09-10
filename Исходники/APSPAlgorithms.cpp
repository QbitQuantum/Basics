void APSPAlgorithms::GraphicalFloydWarshall()
{
    clock_t startTime = clock();
    relaxNum = 0;

    // GraphicalFloydWarshall initialization
    vector<map<int, Arc> > fromList, toList;
    fromList.resize(nodeNum + 1);
    toList.resize(nodeNum + 1);
    for (auto arc: arcs) {
        fromList[arc.from][arc.to] = arc;
        toList[arc.to][arc.from] = arc;
    }

    Arc startArc, endArc;
    for (int mid = 1; mid < nodeNum + 1; mid++)
        for (auto startArcEntry: toList[mid])
            for (auto endArcEntry: fromList[mid]) {
                startArc = startArcEntry.second;
                endArc = endArcEntry.second;

                relaxNum++;
                int temp = startArc.arcLength + endArc.arcLength;
                if (dis[startArc.from][endArc.to] > temp) {
                    fromList[startArc.from][endArc.to] = Arc(startArc.from, endArc.to, temp);
                    toList[endArc.to][startArc.from] = Arc(startArc.from, endArc.to, temp);

                    dis[startArc.from][endArc.to] = temp;
                    pre[startArc.from][endArc.to] = mid;
                }
            }

    processTime = clock() -startTime;
}