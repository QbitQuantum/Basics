SocketDescriptor AnimeshAsset::GetSocketTransform(const char* socketName)
{
  SocketDescriptor desc;

  uint sockf = animeshsprite->FindSocket(socketName);
  if (sockf == (uint)~0) return desc;
  CS::Mesh::iAnimatedMeshSocket* sock = animeshstate->GetSocket(sockf);
  if (!sock) return desc;

  csString str;

  desc["Name"] = TypeValue("String", sock->GetName());
  desc["Bone"] = TypeValue("String", str.Format("%zu", sock->GetBone()).GetData());

  //csVector3 offset = sock->GetFactory()->GetTransform().GetOrigin();
  csVector3 offset = sock->GetTransform().GetOrigin();
  desc["Offset"] = TypeValue("Vector3", str.Format("%.2f, %.2f, %.2f", offset.x, offset.y, offset.z).GetData());

  //csVector3 rot = Decompose(sock->GetFactory()->GetTransform().GetO2T());
  csVector3 rot = Decompose(sock->GetTransform().GetO2T());
  desc["Rotation"] = TypeValue("Vector3", str.Format("%.2f, %.2f, %.2f", rot.x, rot.y, rot.z).GetData());

  return desc;
}