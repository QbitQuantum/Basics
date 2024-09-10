std::vector<xy::Entity> DynamicTreeSystem::query(sf::FloatRect area, std::uint64_t filter) const
{
    Detail::FixedStack<std::int32_t, 256> stack;
    stack.push(m_root);

    std::vector<xy::Entity> retVal;
    retVal.reserve(256);

    while (stack.size() > 0)
    {
        auto treeID = stack.pop();
        if (treeID == TreeNode::Null)
        {
            continue;
        }

        const auto& node = m_nodes[treeID];
        if (area.intersects(node.fatBounds))
        {
            //TODO it would be nice to precache the filter fetch, but it would miss changes at the component level
            if (node.isLeaf() && node.entity.isValid()
                && (node.entity.getComponent<BroadphaseComponent>().m_filterFlags & filter)) 
            {
                //we have a candidate, stash
                retVal.push_back(node.entity);
            }
            else
            {
                stack.push(node.childA);
                stack.push(node.childB);
            }
        }
    }
    return retVal;
}