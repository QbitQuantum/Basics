void CallstackTree::remove( uint callstackId )
{
   // check if the callstack was recorded
   bool wasRecorded = false;
   for ( long i = m_callstackIdsCount - 1; i >= 0; --i )
   {
      if ( m_callstackIds[i] == callstackId )
      {
         wasRecorded = true;
         RawArrayUtil::remove( m_allocator, m_callstackIds, m_callstackIdsCount, i );
         break;
      }
   }

   if ( !wasRecorded )
   {
      return;
   }

   // remove callstack from the tree
   Node* nextNode = m_root;
   while( nextNode != NULL )
   {
      Node* analyzedNode = nextNode;
      nextNode = NULL;

      // find a child that corresponds to this callstack id
      uint count = analyzedNode->m_childrenCount;
      for ( uint i = 0; i < count; ++i )
      {
         Node* child = analyzedNode->m_children[i];
         if ( child->isPartOfCallstack( callstackId ) )
         {
            // remove the callstack 
            bool wasLastCallstack = child->remove( callstackId );

            if ( wasLastCallstack )
            {
               // and if it was the last one - remove the node altogether, thus removing the whole branch
               child->~Node();
               m_allocator->dealloc( child );
               RawArrayUtil::remove( m_allocator, analyzedNode->m_children, analyzedNode->m_childrenCount, i );
               nextNode = NULL;
            }
            else
            {
               // go to the next node
               nextNode = child;
            }
            break;
         }
      }
   }

}