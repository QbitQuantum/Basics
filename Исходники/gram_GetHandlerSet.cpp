 void getHandlerSet (basl::Nonterm & nonterm, smtc::HandlerPtrVector & handler_set)
 {
   nonterm.accept (GetHandlerSet (handler_set));
 }