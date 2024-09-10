 void visit(TypeSArray *t)
 {
     if (!substitute(t))
     store(t);
     if (t->isImmutable() || t->isShared())
     {
         visit((Type *)t);
     }
     if (t->isConst())
         buf.writeByte('K');
     buf.printf("A%llu_", t->dim ? t->dim->toInteger() : 0);
     t->next->accept(this);
     
 }