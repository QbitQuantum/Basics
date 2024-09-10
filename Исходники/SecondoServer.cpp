void
SecondoServer::WriteResponse( const int errorCode, const int errorPos,
                              const string& errorMessage, ListExpr resultList )
{
  ListExpr msg = nl->TextAtom();
  nl->AppendText( msg, errorMessage );
  
  ListExpr list = nl->FourElemList(
                    nl->IntAtom( errorCode ),
                    nl->IntAtom( errorPos ),
                    msg,
                    resultList );

  iostream& iosock = client->GetSocketStream();
 
  csp->IgnoreMsg(true); 
  iosock << "<SecondoResponse>" << endl;
  csp::sendList(iosock, NList(list));  
  iosock << "</SecondoResponse>" << endl;
  
}