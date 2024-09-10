void SG_EntryForm::SaveTxt(
                           OFormatter& txtfile,
                           Grammar &gram,
                           const SG_Entry &entry
                          ) const
{
 const GramClass &c = gram.classes()[ entry.GetClass() ];
 txtfile.printf( "  " );

 for( Container::size_type i=0; i<coords().size(); i++ )
  {
   const GramCoordPair cp = coords()[i];

   if( find( c.attrs(), cp.GetCoord() )!=UNKNOWN )
    continue;

   const GramCoord& c = gram.coords()[cp.GetCoord().GetIndex()];
   const UCString& dim_name = c.GetName()[cp.GetCoord().GetVar()];

   if( !c.states().empty() )
    {
     const UCString &state_name = c.GetStateName(cp.GetState());

     if( c.IsDefState(cp.GetState()) && c.IsHeadState(cp.GetState() ) )
      txtfile.printf(
                     "%us%us%us%us%us ",
                     dim_name.c_str(),
                     sol_get_token(B_COLON).c_str(),
                     sol_get_token(B_OROUNDPAREN).c_str(),
                     state_name.c_str(),
                     sol_get_token(B_CROUNDPAREN).c_str()
                    );
     else
      txtfile.printf(
                     "%us%us%us ",
                     dim_name.c_str(),
                     sol_get_token(B_COLON).c_str(),
                     state_name.c_str()
                    );
    }
   else
    {
     UCString prefix;

     if(!cp.GetState())
      prefix=sol_get_token(B_NEGATIVE);

     txtfile.printf( "%us%us ", prefix.c_str(), dim_name.c_str() );
    }
  }

 txtfile.printf(
                " %us %us %us\n",
                sol_get_token(B_OFIGPAREN).c_str(),
                content->c_str(),
                sol_get_token(B_CFIGPAREN).c_str()
               );
 return;
}