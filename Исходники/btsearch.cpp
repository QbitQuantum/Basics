 Node* remove( int val, Node* parent ) {
     if ( this->value > val ) {
         if ( left == NULL ) {
             return NULL;
         } else {
             return left->remove( val, this );
         }
     } else if ( this->value < val ) {
         if ( right == NULL ) {
             return NULL;
         } else {
             return right->remove( val, this );
         }
     } else {
        if (left != NULL && right != NULL) {
              this->value = right->min();
              return right->remove( this->value, this );
        } else if (parent->left == this) {
              parent->left = (left != NULL) ? left : right;
              return this;
        } else if (parent->right == this) {
              parent->right = (left != NULL) ? left : right;
              return this;
        }
     }
     return NULL;
 }