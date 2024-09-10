int SMM_SIRADAKI_MAKBUZ_NO_AL(QString p_makbuz_tarihi, ADAK_SQL *P_DB)
{
    ADAK_SQL * USE_DB;

    if ( P_DB EQ NULL ) {
        USE_DB = DB;
    }
    else {
        USE_DB = P_DB;
    }

    SQL_QUERY query ( USE_DB );

    query.PREPARE_SELECT ( "smm_makbuzlar",
                           "makbuz_no",
                           "makbuz_tarihi = :makbuz_tarihi" );
    query.SET_VALUE    ( ":makbuz_tarihi", p_makbuz_tarihi );

    if ( query.SELECT( "makbuz_no DESC", 0, 1 ) EQ 0 ) {
        return 1;
    }

    query.NEXT();

    return query.VALUE(0).toInt() + 1;
}