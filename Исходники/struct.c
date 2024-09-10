 void visit(TypeTuple *t)
 {
     if (t->arguments)
     {
         for (size_t i = 0; i < t->arguments->dim; i++)
         {
             Type *tprm = (*t->arguments)[i]->type;
             if (tprm)
                 tprm->accept(this);
         }
     }
 }