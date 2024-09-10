 void LetBindingChecker::Do(const Expression& Exp)
 {
     LetBindingChecker Checker;
     Exp->Accept(&Checker);
     return;
 }