//
// Get all the paths corresponding to the linear components of the graph
// Precondition: all vertices have in/out degree at most 1 (no branching)
//
PathVector Bigraph::getLinearComponents()
{
    PathVector outPaths;
    setColors(GC_WHITE);
    VertexPtrMapIter iter = m_vertices.begin(); 
    for(; iter != m_vertices.end(); ++iter)
    {
        // Output the linear path containing this vertex if it hasnt been visited already
        if(iter->second->getColor() != GC_BLACK)
        {
            outPaths.push_back(constructLinearPath(iter->second->getID()));
        }
    }
    assert(checkColors(GC_BLACK));
    return outPaths;
}