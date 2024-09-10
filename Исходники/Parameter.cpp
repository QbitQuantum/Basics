Connection* Parameter::connect(Node* node)
{
    // Sanity check
    if (!isInputParameter()) {
        throw ConnectionError(m_node->getName() + "." + m_name + ": can only connect input nodes");        
    }
    if (node == m_node) {
        throw ConnectionError(m_node->getName() + "." + m_name + ": cannot connect to myself");
    }
    if (!canConnectTo(node)) {
        throw ConnectionError(m_node->getName() + "." + m_name + ": cannot connect to " + node->getName());
    }
    disconnect();
    m_connection = new Connection(node->getOutputParameter(), this);
    node->addDownstream(m_connection);
    m_node->markDirty();
    // TODO: notify
    return m_connection;
}