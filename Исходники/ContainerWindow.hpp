 void bring_child_to_top(Window &child) {
   children.remove(&child);
   children.insert(children.begin(), &child);
   invalidate();
 }