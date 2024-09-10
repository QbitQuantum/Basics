void TestCAO::removeFromScene(bool permanent)
{
	if(m_node == NULL)
		return;

	m_node->remove();
	m_node = NULL;
}