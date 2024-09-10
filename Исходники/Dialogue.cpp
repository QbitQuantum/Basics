void Dialogue::setNextNode(int choice) {
	if (m_currentNode == nullptr) return;
	int nextNode;
	if (choice == -1) {
		nextNode = m_currentNode->nextTag;
	}
	else {
		nextNode = m_currentNode->choices[choice].second;
	}

	if (nextNode == -1) {
		m_currentNode = nullptr;
		return;
	}
	else if (nextNode == -2) {
		reload(m_id, m_screen, m_window);
		updateWindow();
		return;
	}

	m_currentNode = &m_nodes[nextNode];
}