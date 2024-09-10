void
RibEntry::removeChild(shared_ptr<RibEntry> child)
{
  BOOST_ASSERT(child->getParent().get() == this);
  child->setParent(shared_ptr<RibEntry>());
  m_children.remove(child);
}