 virtual void accept(FieldVisitor& v)
 {
   v.enter(*this);
   getOperand().accept(v);
   v.exit(*this);
 }