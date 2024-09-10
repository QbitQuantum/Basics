 // Pass an IRVisitor through to all Exprs referenced in the ReductionDomainContents
 void accept(IRVisitor *visitor) {
     for (const ReductionVariable &rvar : domain) {
         if (rvar.min.defined()) {
             rvar.min.accept(visitor);
         }
         if (rvar.extent.defined()) {
             rvar.extent.accept(visitor);
         }
     }
     if (predicate.defined()) {
         predicate.accept(visitor);
     }
 }