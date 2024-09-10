/**
 * Compute the diversity of the tree at time t.
 *
 * \param[in]    t      time at which we want to know the diversity.
 *
 * \return The diversity (number of species in the reconstructed tree).
 */
int PiecewiseConstantSerialSampledBirthDeathProcess::survivors(double t) const
{

    const std::vector<TopologyNode*>& nodes = value->getNodes();

    int survivors = 0;
    for (std::vector<TopologyNode*>::const_iterator it = nodes.begin(); it != nodes.end(); ++it)
    {
        TopologyNode* n = *it;
        if ( n->getAge() < t )
        {
            if ( n->isRoot() || n->getParent().getAge() > t )
            {
                survivors++;
            }
        }
    }

    return survivors;
}