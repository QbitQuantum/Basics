void showError(mu::Parser::exception_type &e)
{
    cout << "Error occurred in parser.\n" 
         << "Message:  " << e.GetMsg() << "\n"
         << "Formula:  " << e.GetExpr() << "\n"
         << "Token:    " << e.GetToken() << "\n"
         << "Position: " << e.GetPos() << "\n"
         << "Error code:     " << e.GetCode() << endl;
}