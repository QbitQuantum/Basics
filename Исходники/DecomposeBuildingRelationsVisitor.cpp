void DecomposeBuildingRelationsVisitor::_decomposeBuilding(const shared_ptr<Relation>& r)
{
  Tags baseTags = r->getTags();

  const vector<RelationData::Entry> members = r->getMembers();

  for (size_t i = 0; i < members.size(); ++i)
  {
    ElementId eid = members[i].getElementId();
    r->removeElement(eid);
    if (eid.getType() == ElementType::Node)
    {
      LOG_WARN("Unexpected node encountered in building relation. " << r->getElementId());
      continue;
    }
    // we're dropping the outline. We only care about the parts.
    else if (members[i].getRole() == "outline")
    {
      continue;
    }
    else if (members[i].getRole() != "part")
    {
      LOG_WARN("Encountered an unexpected role in a building relation. " << r->getElementId());
    }

    // ok, we've got a building part. Recompose it as a building.
    shared_ptr<Element> e = _map->getElement(members[i].getElementId());

    Tags t = baseTags;
    t.addTags(e->getTags());
    // don't need the building:part tag anymore.
    t.remove("building:part");

    if (!t.contains("building"))
    {
      t["building"] = "yes";
    }

    e->setTags(t);
  }

  // remove the building relation
  RecursiveElementRemover(r->getElementId()).apply(_map->shared_from_this());
}