SocketDescriptor GenmeshAsset::GetSocketTransform(const char* socketName)
{
  SocketDescriptor desc;

  iSkeletonSocket* sock = skeleton->FindSocket (socketName);
  if (!sock) return desc;

  csString str;

  desc["Name"] = TypeValue("String", sock->GetName());
  iSkeletonBone* bone = sock->GetBone();
  desc["Bone"] = TypeValue("String", bone->GetName());

  csVector3 offset = sock->GetTransform().GetOrigin();
  desc["Offset"] = TypeValue("Vector3", str.Format("%.2f, %.2f, %.2f", offset.x, offset.y, offset.z).GetData());

  csVector3 rot = Decompose(sock->GetTransform().GetO2T());
  desc["Rotation"] = TypeValue("Vector3", str.Format("%.2f, %.2f, %.2f", rot.x, rot.y, rot.z).GetData());

  return desc;
}