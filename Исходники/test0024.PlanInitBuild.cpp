 void make_cycle()
  {
   Node *start;
   
   do
     {
      start=nodes+random.select(Len);
     }
   while( start->req_list.len==0 );
   
   Node *node=start;
   
   while( random.select(4) )
     {
      ulen j=random.select(node->req_list.len);
      
      Node *next=node->req_list[j];
      
      if( next->req_list.len )
        {
         node=next;
        }
      else
        {
         node->req_list[j]=start;
         
         return;
        }
     }
     
   {
    ulen j=random.select(node->req_list.len);
    
    node->req_list[j]=start;
   }  
  }