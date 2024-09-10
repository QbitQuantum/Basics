 void printMuException(mu::Parser::exception_type &e)
 {
   using std::cout;
   cout << "Content of muParser exception" << "\n";
   cout << "Message:  " << e.GetMsg() << "\n";
   cout << "Formula:  " << e.GetExpr() << "\n";
   cout << "Token:    " << e.GetToken() << "\n";
   cout << "Position: " << e.GetPos() << "\n";
   cout << "Errc:     " << e.GetCode() << "\n";
 }