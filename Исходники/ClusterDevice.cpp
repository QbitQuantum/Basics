void ClusterDevice::FreeMem(CLMem* mem, void* dev_specific) {
  ClusterSendMessage request;
  request.WriteInt(CLUSTER_REQUEST_FREE_MEM);
  request.WriteULong(mem->id());
  request.Send(node_id_, CLUSTER_TAG_COMMAND);
}