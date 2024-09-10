 virtual void accept(FieldVisitor& v)
 {
   v.enter(*this);
   getLeft().accept(v);
   getRight().accept(v);
   v.exit(*this);
 }