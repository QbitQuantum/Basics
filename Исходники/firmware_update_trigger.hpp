 /*
  * Methods of INodeInfoListener
  */
 virtual void handleNodeInfoUnavailable(NodeID node_id)
 {
     UAVCAN_TRACE("FirmwareUpdateTrigger", "Node ID %d could not provide GetNodeInfo response", int(node_id.get()));
     pending_nodes_.remove(node_id); // For extra paranoia
 }