void SG_CoordContext::SaveTxt( OFormatter &txt, SynGram &sg ) const
{
 const UCString &class_name = sg.classes()[iclass].GetName();

 txt.printf(
            " %us:\"???\" { "
            , class_name.c_str()
           );

 for( Container::size_type k=0; k<coords.size(); k++ )
  {
   const int icoord = coords[k].GetCoord().GetIndex();
   const int istate = coords[k].GetState();

   const UCString &coord_name = sg.coords()[ icoord ].GetName().front();

   if( !sg.coords()[icoord].states().size() )
    {
     if( istate!=0 )
      txt.printf( " %us", coord_name.c_str() );
     else
      txt.printf( " ~%us", coord_name.c_str() );
    }
   else
    {
     const UCString &state_name = sg.coords()[ icoord ].GetStateName( istate );
     txt.printf( " %us:%us", coord_name.c_str(), state_name.c_str() );
    }
  }

 txt.printf( " }" );

 return;
}