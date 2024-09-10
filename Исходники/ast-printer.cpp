 void visitArrayLiteral(ArrayLiteral *node) override {
   prefix();
   fprintf(fp_, "[ ArrayLiteral\n");
   indent();
   for (size_t i = 0; i < node->expressions()->length(); i++) {
     Expression *expr = node->expressions()->at(i);
     indent();
     expr->accept(this);
     unindent();
   }
   if (node->repeatLastElement()) {
     indent();
     prefix();
     fprintf(fp_, "...\n");
     unindent();
   }
 }