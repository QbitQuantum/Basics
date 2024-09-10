 void unsubscribe()
 {
   if (use_indices_) {
     sub_input_.unsubscribe();
     sub_indices_.unsubscribe();
   }
   else {
     sub_.shutdown();
   }
 }