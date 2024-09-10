void BNK_MAKRO_SECIMI::FILL_TABLE()
{
    QTableWidget * table_widget = GET_TABLE_WIDGET();

    SQL_QUERY query ( DB );

    query.PREPARE_SELECT ( "bnk_makrolar","makro_id,makro_adi" );

    if ( query.SELECT() EQ 0 ) {
        return;
    }

    int current_row = 0;

    while ( query.NEXT () ) {
        current_row = ADD_NEW_ROW();

        table_widget->item ( current_row,0 )->setText ( query.VALUE ( "makro_id" ).toString() );
        table_widget->item ( current_row,1 )->setText ( query.VALUE ( "makro_adi" ).toString() );
    }
}