extern Table *LAY_InitTable()
{  Table *LAY_table = CreateTable( "LAY", LAY_NSTRUCTS, LAY_NUNIONS );

   AddElement( LAY_LPAIR,
               "Lpair",
               Sort1( LAY_LAYOUT),
               Sort2( LAY_LAYOUT, LAY_LAYOUT),
               Sort2( "a", "b"),
               LAY_table );

   AddElement( LAY_LBRACKET,
               "Lbracket",
               Sort1( LAY_LAYOUT),
               Sort3( LAY_LAYOUT, LAY_LAYOUT, LAY_LAYOUT),
               Sort3( "open", "body", "close"),
               LAY_table );

   AddElement( LAY_HLIST,
               "Hlist",
               Sort1( LAY_LAYOUT),
               Sort1( LAY_VECLAYOUT),
               Sort1( "list"),
               LAY_table );

   AddElement( LAY_VLIST,
               "Vlist",
               Sort1( LAY_LAYOUT),
               Sort1( LAY_VECLAYOUT),
               Sort1( "list"),
               LAY_table );

   AddSort( LAY_LAYOUT, "Layout", LAY_table);

   return( LAY_table);
}