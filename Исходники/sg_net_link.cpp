void SG_NetLink::SaveTagsTxt( OFormatter &txtfile, SynGram &gram ) const
{
 if( tags!=0 )
  {
   txtfile.printf( " tags { " );

   SG_TagsList tags_ptr = gram.Get_Net().tag_sets->operator [](tags);

   for( lem::Container::size_type i=0; i<tags_ptr->size(); ++i )
    {
     const int itag = (*tags_ptr)[i].first;
     const int ival = (*tags_ptr)[i].second;

     const ThesaurusTag &tag = gram.Get_Net().GetTagDefs()[itag];

     txtfile.printf( " \"%us\"", tag.GetName().c_str() );

     if( ival!=UNKNOWN )
      {
       const lem::UCString &val = tag[ival];
       txtfile.printf( "=\"%us\"", val.c_str() );        
      }

     txtfile.printf( " }" );     
    }
  }

 return;
}