void SQL_INDEX_BATCH::READ_INDEXES()
{
    SQL_QUERY query (DB);

    query.PREPARE_SELECT("sql_tablolar","indexler_array","tablo_id=:tablo_id");
    query.SET_VALUE     (":tablo_id",p_tablo_id);

    if ( query.SELECT() EQ 0 ) {
        return;
    }

    query.NEXT();

    UNPACK_INT_ARRAY(query.VALUE(0).toString(),INDEXLER_ARRAY,INDEXLER_ARRAY_SIZE);

    int line_number = 1;
    for ( int i = 4; i < INDEXLER_ARRAY_SIZE; i++ ) {
        if ( INDEXLER_ARRAY[i] EQ 0 ) {
            if ( i+1 MOD 4 EQ 0 ) {
                line_number++;
            }
            continue;
        }
        COMBOBOX_ARRAY[line_number-1][i-(4*line_number)]->setCurrentIndex
                (COMBOBOX_ARRAY[line_number][i-(4*line_number)]->findText(GET_ALAN_ADI(p_tablo_id,INDEXLER_ARRAY[i])));

        if ( i+1 MOD 4 EQ 0 ) {
            line_number++;
        }
    }
}