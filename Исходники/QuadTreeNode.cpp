std::vector<MapObject*> QuadTreeNode::Retrieve(const sf::FloatRect& bounds, sf::Uint16& searchDepth)
{	
	searchDepth = m_level;
	std::vector<MapObject*> foundObjects;
	sf::Int16 index = m_GetIndex(bounds);

	//recursively add objects of child node if bounds is fully contained
	if(!m_children.empty() && index != -1) 
	{
		foundObjects = m_children[index]->Retrieve(bounds, searchDepth);
	}
	else
	{
		//add all objects of child nodes which intersect test area
		for(auto& child : m_children)
		{
			if(bounds.intersects(child->m_bounds))
			{
				std::vector<MapObject*> childObjects = child->Retrieve(bounds, searchDepth);
				foundObjects.insert(foundObjects.end(), childObjects.begin(), childObjects.end());
			}
		}

	}
	//and append objects in this node
	foundObjects.insert(foundObjects.end(), m_objects.begin(), m_objects.end());
	m_debugShape.setOutlineColor(sf::Color::Red);
	return foundObjects;
}