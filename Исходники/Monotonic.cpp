 void visit_eq(Expr a, Expr b) {
     a.accept(this);
     Monotonic ra = result;
     b.accept(this);
     Monotonic rb = result;
     if (ra == Monotonic::Constant && rb == Monotonic::Constant) {
         result = Monotonic::Constant;
     } else {
         result = Monotonic::Unknown;
     }
 }