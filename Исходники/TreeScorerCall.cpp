void TreeScorerCall::PrintContext( Dictionary & dict, OFormatter & out ) const
{
 out.printf( "Edges count=%d:\n", edges.size() );
 for( int i=0; i<edges.size(); ++i )
  {
   edges[i].from->Print( out, & dict.GetSynGram(), true );
   const int lt = edges[i].link_type;
   out.printf( " --" );
   if( lt==UNKNOWN )
    out.printf( "<<UNKNOWN>>" );
   else
    out.printf( "%us", dict.GetSynGram().GetLink(lt).c_str() );

   out.printf( "--> " );

   edges[i].to->Print( out, & dict.GetSynGram(), true );
   out.eol();
  }

 out.eol();

 return;
}