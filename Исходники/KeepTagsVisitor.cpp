void KeepTagsVisitor::visit(const shared_ptr<Element>& e)
{
  //get a copy of the tags for modifying
  Tags tags;
  tags.addTags(e->getTags());
  for (Tags::const_iterator it = e->getTags().begin(); it != e->getTags().end(); ++it)
  {
    if (!_keys.contains(it.key()))
    {
      tags.remove(it.key());
    }
  }
  e->setTags(tags);
}