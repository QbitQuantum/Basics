void
pcl::recognition::ORROctree::deleteBranch (Node* node)
{
  node->deleteChildren ();
  node->deleteData ();

  Node *parent = node->getParent ();

  // Go up until you reach a node which has other non-empty children (i.e., children with other children or with data)
  while ( parent )
  {
    Node *children = parent->getChildren ();
    // Check the children
    int i;
    for ( i = 0 ; i < 8 ; ++i )
    {
      if ( children[i].hasData () || children[i].hasChildren () )
        break;
    }

    // There are no children with other children or with data -> delete them all!
    if ( i == 8 )
    {
      parent->deleteChildren ();
      parent->deleteData ();
      // Go one level up
      parent = parent->getParent ();
    }
    else
      // Terminate the deleting process
      break;
  }
}