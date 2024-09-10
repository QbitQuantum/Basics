int MUH_CHECK_MUHASEBE_ALARMLARI ( QString tam_hesap_kodu,double eklenecek_borc,double eklenecek_alacak )
{
    if ( K9_MUHASEBE_ALARMLARI_KAPALIMI() EQ true ) {
        return ADAK_OK;
    }

    if ( tam_hesap_kodu.isEmpty() EQ true ) {
        return ADAK_FAIL;
    }

    SQL_QUERY query (DB);

    query.PREPARE_SELECT("muh_hesaplar" , "tali_hesap , hesap_ismi , hesap_id, toplam_borc_array , toplam_alacak_array, "
                         "ent_borc_array , ent_alacak_array , ent_olmayan_borc_array,"
                         "ent_olmayan_alacak_array" , "tam_hesap_kodu = :tam_hesap_kodu");

    query.SET_VALUE(":tam_hesap_kodu" , tam_hesap_kodu );

    if ( query.SELECT() EQ 0 ) {
        return ADAK_FAIL;
    }
    query.NEXT();

    int tali_hesap_mi = query.VALUE(0).toInt();

    if ( tali_hesap_mi EQ 0 ) {
        return ADAK_FAIL;
    }

    double * HESABIN_BORC_BAKIYESI   = new double [ K9_ARRAY_SIZE ];
    double * HESABIN_ALACAK_BAKIYESI = new double [ K9_ARRAY_SIZE ];

    if ( K9_KULLANICININ_CALISTIGI_SIRKET() EQ 1 ) {
        UNPACK_DOUBLE_ARRAY ( query.VALUE("ent_borc_array").toString()  ,HESABIN_BORC_BAKIYESI     ,K9_ARRAY_SIZE );
        UNPACK_DOUBLE_ARRAY ( query.VALUE("ent_alacak_array").toString(),HESABIN_ALACAK_BAKIYESI   ,K9_ARRAY_SIZE );
    }
    else {
        UNPACK_DOUBLE_ARRAY ( query.VALUE("toplam_borc_array").toString()  ,HESABIN_BORC_BAKIYESI     ,K9_ARRAY_SIZE );
        UNPACK_DOUBLE_ARRAY ( query.VALUE("toplam_alacak_array").toString(),HESABIN_ALACAK_BAKIYESI   ,K9_ARRAY_SIZE );
    }

    double hesap_toplam_borc   = HESABIN_BORC_BAKIYESI   [ K9_SON_BAKIYE ];
    double hesap_toplam_alacak = HESABIN_ALACAK_BAKIYESI [ K9_SON_BAKIYE ];

    delete [] HESABIN_BORC_BAKIYESI;
    delete [] HESABIN_ALACAK_BAKIYESI;

    if ( tam_hesap_kodu.at(0) EQ '1' OR tam_hesap_kodu.at(0) EQ '2') {

        if ( hesap_toplam_alacak >= hesap_toplam_borc ) {
            return ADAK_OK;
        }

        if ( hesap_toplam_alacak + eklenecek_alacak > hesap_toplam_borc + eklenecek_borc ) {
            ADAK_MSG_ENUM msg_enum = ADAK_YES_NO(QString("%1 %2 alacak bakiye veriyor. Yine de devam etmek istermisiniz ?")
                                                 .arg(tam_hesap_kodu)
                                                 .arg(query.VALUE(1).toString()),NULL,NULL);
            if ( msg_enum NE ADAK_YES ) {
                return ADAK_FAIL;
            }
        }
    }
    else if ( tam_hesap_kodu.at(0) EQ '3' OR tam_hesap_kodu.at(0) EQ '4' OR tam_hesap_kodu.at(0) EQ '5') {

        if ( hesap_toplam_alacak < hesap_toplam_borc ) {
            return ADAK_OK;
        }

        if ( hesap_toplam_alacak + eklenecek_alacak < hesap_toplam_borc + eklenecek_borc ) {
            ADAK_MSG_ENUM msg_enum = ADAK_YES_NO(QString("%1 %2 borc bakiye veriyor. Yine de devam etmek istermisiniz ?")
                                                 .arg(tam_hesap_kodu)
                                                 .arg(query.VALUE(1).toString()),NULL,NULL);
            if ( msg_enum NE ADAK_YES ) {
                return ADAK_FAIL;
            }
        }
    }

    return ADAK_OK;
}