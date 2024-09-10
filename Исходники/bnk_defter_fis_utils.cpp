void BNK_DEFTER_FISI_SIL( BNK_DEFTER_FIS_STRUCT * P_FIS, int p_fis_id )
{
    SQL_QUERY query ( DB );
    query.PREPARE_SELECT ( "bnk_defter_fisler","modul_id, program_id,base_fis_id ",
                           "fis_id = :fis_id" );
    query.SET_VALUE      ( ":fis_id" , p_fis_id );

   if ( query.SELECT() EQ 0 ) {
        return;
    }
    query.NEXT();

    int         modul_id           =   query.VALUE ( 0 ).toInt();
    int         program_id         =   query.VALUE ( 1 ).toInt();
    int         base_fis_id        =   query.VALUE ( 2 ).toInt();

    if ( P_FIS->modul_id NE modul_id OR P_FIS->program_id NE program_id OR P_FIS->base_fis_id NE base_fis_id ) {
        return;
    }

    query.PREPARE_SELECT ( "bnk_defter_fis_satirlari","fis_satiri_id","fis_id = :fis_id" );
    query.SET_VALUE      ( ":fis_id", p_fis_id );

    // Fis'e ait satirlar siliniyor
    if ( query.SELECT() > 0 ) {
        while ( query.NEXT() EQ true ) {
            BNK_DEFTER_FIS_SATIRI_SIL ( P_FIS, query.VALUE ( 0 ).toInt() );
        }
    }

    query.PREPARE_DELETE ( "bnk_defter_fisler","fis_id = :fis_id" );
    query.SET_VALUE      ( ":fis_id", p_fis_id );
    query.DELETE();
}