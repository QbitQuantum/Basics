 bool remove(const T key) {
   if(key == value) return false; // cannot remove parent from self
   if(key < value) {
     if(left == NULL) return false;
     if(left->getValue() == key) {
       BinarySearchTree<T> *ls = left->leftNode();
       BinarySearchTree<T> *rs = left->rightNode();
       if(ls == NULL && rs == NULL) {
         left = NULL;
       } else if(ls == NULL) {
         left = rs;
       } else if(rs == NULL) {
         left = ls;
       } else {
         BinarySearchTree<T> *pred = predecessor(left);
         left->setValue(pred->getValue());
         return left->rightNode()->remove(pred->getValue());
       }
       return true;
     } else {
       return left->remove(key);
     }
   } else {
     if(right == NULL) return false;
     if(right->getValue() == key) {
       BinarySearchTree<T> *ls = right->leftNode();
       BinarySearchTree<T> *rs = right->rightNode();
       if(ls == NULL && rs == NULL) {
         right = NULL;
       } else if(ls == NULL) {
         right = rs;
       } else if(rs == NULL) {
         right = ls;
       } else {
         BinarySearchTree<T> *pred = predecessor(right);
         right->setValue(pred->getValue());
         return right->rightNode()->remove(pred->getValue());
       }
       return true;
     } else {
       return right->remove(key);
     }
   }
 }