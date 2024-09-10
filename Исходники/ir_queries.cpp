 bool check(Stmt stmt) {
   isFlattened = true;
   indexExprFound = false;
   stmt.accept(this);
   return isFlattened;
 }