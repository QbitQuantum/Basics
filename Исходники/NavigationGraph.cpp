int NavigationGraph::getClosestNodeIndexToPoint(const Vec3& p) const
{
    if (nodes_.empty())
        return -1;

    auto index = 0;
    auto closestDistance = p.distance(nodes_[0]->getPosition());

    for (auto i = 1U; i < nodes_.size(); i++)
    {
        auto d = p.distance(nodes_[i]->getPosition());
        if (d < closestDistance)
        {
            closestDistance = d;
            index = i;
        }
    }

    return index;
}