// return {false: this entry is not empty, true: this entry is empty and erased}
bool
NameTree::eraseEntryIfEmpty(shared_ptr<name_tree::Entry> entry)
{
  BOOST_ASSERT(static_cast<bool>(entry));

  NFD_LOG_TRACE("eraseEntryIfEmpty " << entry->getPrefix());

  // first check if this Entry can be erased
  if (entry->isEmpty())
    {
      // update child-related info in the parent
      shared_ptr<name_tree::Entry> parent = entry->getParent();

      if (static_cast<bool>(parent))
        {
          std::vector<shared_ptr<name_tree::Entry> >& parentChildrenList =
            parent->getChildren();

          bool isFound = false;
          size_t size = parentChildrenList.size();
          for (size_t i = 0; i < size; i++)
            {
              if (parentChildrenList[i] == entry)
                {
                  parentChildrenList[i] = parentChildrenList[size - 1];
                  parentChildrenList.pop_back();
                  isFound = true;
                  break;
                }
            }

          BOOST_VERIFY(isFound == true);
        }

      // remove this Entry and its Name Tree Node
      name_tree::Node* node = entry->m_node;
      name_tree::Node* nodePrev = node->m_prev;

      // configure the previous node
      if (nodePrev != 0)
        {
          // link the previous node to the next node
          nodePrev->m_next = node->m_next;
        }
      else
        {
          m_buckets[entry->getHash() % m_nBuckets] = node->m_next;
        }

      // link the previous node with the next node (skip the erased one)
      if (node->m_next != 0)
        {
          node->m_next->m_prev = nodePrev;
          node->m_next = 0;
        }

      BOOST_ASSERT(node->m_next == 0);

      m_nItems--;
      delete node;

      if (static_cast<bool>(parent))
        eraseEntryIfEmpty(parent);

      size_t newNBuckets = static_cast<size_t>(m_shrinkFactor *
                                     static_cast<double>(m_nBuckets));

      if (newNBuckets >= m_minNBuckets && m_nItems < m_shrinkThreshold)
        {
          resize(newNBuckets);
        }

      return true;

    } // if this entry is empty

  return false; // if this entry is not empty
}