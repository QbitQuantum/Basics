void TransformerVisitor::createMap(const Node& node)
{
	MapCreator * mapCreator = new MapCreator(templatesMap);
	node.accept(*mapCreator);
}