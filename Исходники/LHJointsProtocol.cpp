void LHJointsProtocol::findConnectedNodes()
{
    if(_nodeAUUID.length() == 0 || _nodeBUUID.length() == 0)
        return;
    
    
    Node* node = dynamic_cast<Node*>(this);
    if(!node)return;
    
    LHScene* scene = (LHScene*)node->getScene();
    
    LHNodeProtocol* parentProtocol = dynamic_cast<LHNodeProtocol*>(node->getParent());
    if(parentProtocol)
    {
        _nodeA = parentProtocol->getChildNodeWithUUID(_nodeAUUID);
        _nodeB = parentProtocol->getChildNodeWithUUID(_nodeBUUID);
    }
    if(!_nodeA){
        _nodeA = scene->getChildNodeWithUUID(_nodeAUUID);
        
    }
    if(!_nodeB){
        _nodeB = scene->getChildNodeWithUUID(_nodeBUUID);
    }
}