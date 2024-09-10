// ----------------------------------------------------------------------------
void ArenaGraph::buildGraph()
{
    const unsigned int n_nodes = getNumNodes();

    m_distance_matrix = std::vector<std::vector<float>>
        (n_nodes, std::vector<float>(n_nodes, 9999.9f));
    for (unsigned int i = 0; i < n_nodes; i++)
    {
        ArenaNode* cur_node = getNode(i);
        for (const int& adjacent : cur_node->getAdjacentNodes())
        {
            Vec3 diff = getNode(adjacent)->getCenter() - cur_node->getCenter();
            float distance = diff.length();
            m_distance_matrix[i][adjacent] = distance;
        }
        m_distance_matrix[i][i] = 0.0f;
    }

    // Allocate and initialise the previous node data structure:
    m_parent_node = std::vector<std::vector<int16_t>>
        (n_nodes, std::vector<int16_t>(n_nodes, Graph::UNKNOWN_SECTOR));
    for (unsigned int i = 0; i < n_nodes; i++)
    {
        for (unsigned int j = 0; j < n_nodes; j++)
        {
            if (i == j || m_distance_matrix[i][j] >= 9899.9f)
                m_parent_node[i][j] = -1;
            else
                m_parent_node[i][j] = i;
        }   // for j
    }   // for i

}   // buildGraph