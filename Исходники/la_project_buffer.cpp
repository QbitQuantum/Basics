void LA_WordProjBuffer::PrintMap(
                                 OFormatter &txtfile,
                                 SynGram &gram
                                ) const
{
 Report(txtfile,gram.GetDict().GetLexAuto());

 txtfile.printf(
                "There are %d item(s) in word projection cache:\n",
                list.size()
               );

 for( Container::size_type i=0; i<list.size(); i++ )
  {
   list[i].PrintInfo(txtfile,gram);
  }

 txtfile.printf( "The end of word projection cache map.\n" );

 return;
}