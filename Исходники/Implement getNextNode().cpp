Node* GetNextNode(Node *node) {
   assert(node != NULL);

   Node* next = node->GetFirstChild();
   if(next) return next;

   next = node->GetSlibing();

   if(next) return next;

   next = node->GetParent();

   while (next) {

      next = next->GetSlibing();
      if(next) return next;
      next = next->GetParent();
   }

   return NULL;
}