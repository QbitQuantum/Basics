/*
 * Traverse the graph and draw all the elements. The order of edges vs nodes
 * doesn't matter here since the groups are already in the correct order.
 */
void SVG_Image::drawGraph(const Graph& g, unsigned int layoutGridSize)
{
    gridSize = layoutGridSize;
    hexWidth = getHexagonWidth(gridSize);
    std::cout << "Drawing a graph, gridsize = " << gridSize << std::endl;
    // Try to come up with good size for nodes and edges.
    nodeRadius = 0.2*hexWidth;
    nodeThickness = 0*nodeRadius;
    edgeThickness = 0.1*nodeRadius;
    init_xml();
    for(auto node : g.nodes) {
        drawNode(node.first);
        for(auto to : node.second) {
            drawEdge(node.first, to);
        }
    }
}