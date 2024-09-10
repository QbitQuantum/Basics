bool nglZipPath::Decompose(const nglPath& rPath, std::list<nglPath>& rList)
{
  nglPath parent(rPath.GetParent());
  nglString tmp = rPath.GetNodeName();
  nglPath node(tmp.IsNull()? nglString::Empty : tmp);

  if (parent == rPath)
    return true;

  rList.push_front(node);
  return Decompose(parent, rList);

  return true;
}