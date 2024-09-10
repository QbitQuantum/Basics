 /**
  * Standard assignment operator.
  */
 self& operator=(self rhs) {
   swap(*this,rhs);
   return *this;
 };