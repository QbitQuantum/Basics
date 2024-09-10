void EntityDrawLayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Node<Entity*>* node = drawList_.getFirst();
	Node<Entity*>* next = nullptr;

	while (node != nullptr)
	{
		next = node->getNext();
		node->remove();
		target.draw(*node->data, states);
		delete node;
		node = next;
	}
}