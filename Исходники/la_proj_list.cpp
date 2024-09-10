void LA_ProjList::PrintInfo(
                            OFormatter &txtfile,
                            SynGram &gram
                           ) const
{
 if( empty() )
  // Чтобы не засорять листинг, пропускаем пустые списки...
  return;

 txtfile.printf(
                "\nList of cached projections beginning with symbol [%uc]:\n"
                , Char
               );

 for( Container::size_type i=0; i<size(); i++ )
  get(CastSizeToInt(i)).PrintInfo(txtfile,gram);

 return;
}