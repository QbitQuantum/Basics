int PRS_PUANTAJLARI_GOR_VE_DUZELT_FISI::GET_FIS_RECORD ( int record_id )
{

    SQL_QUERY  query    ( DB );
    SQL_QUERY  s_query  ( DB );

    QString bordro_bas_donemi = PRS_GET_BORDRO_DONEMI_BAS_STRING( m_bordro_yili, m_bordro_ayi );
    QString bordro_bts_donemi = PRS_GET_BORDRO_DONEMI_BTS_STRING( m_bordro_yili, m_bordro_ayi );

    // isten ayrilanlar

    query.PREPARE_SELECT("prs_personel_nufus_blgler, prs_personeller, prs_personel_kisisel_blgler " ,
                         "prs_personel_nufus_blgler.personel_id, "
                         "ucret_sekli,                  "
                         "net_ucret,                    "
                         "brut_ucret ,                  "
                         "ise_giris_tarihi,             "
                         "cari_hesap_id,                "
                         "ise_giris_tarihi,             "
                         "calisma_sekli,                "
                         "haftalik_calisilan_gun_sayisi,"
                         "isten_cikis_tarihi",

                         "prs_personel_nufus_blgler.personel_id         = prs_personeller.personel_id               "
                         "AND prs_personel_kisisel_blgler.personel_id   = prs_personeller.personel_id               "
                         "AND sube_id = :sube_id                              "
                         "AND ise_giris_tarihi   <= :ise_giris_tarihi         "
                         "AND isten_cikis_tarihi >= :isten_cikis_tarihi       " );
    query.SET_VALUE(":sube_id"            , m_sube_id);
    query.SET_VALUE(":ise_giris_tarihi"   , bordro_bts_donemi );
    query.SET_VALUE(":isten_cikis_tarihi" , bordro_bas_donemi );

    if ( query.SELECT() EQ 0) {
        return ADAK_OK;
    }

    int current_row     = -1;
    int prs_doviz_id    =  0;

    while ( query.NEXT() NE 0 ) {

        int personel_id = query.VALUE("personel_id").toInt();


        int cari_hesap_id           = query.VALUE( "cari_hesap_id").toInt();
        QDate ise_giris_tarihi      = QDate::fromString( query.VALUE( "ise_giris_tarihi" ).toString(), "yyyy.MM.dd" );
        QString isten_cikis_tarihi  = query.VALUE( "isten_cikis_tarihi" ).toString();

        CARI_HESAP_STRUCT hesap_bilgileri;
        CARI_SET_HESAP_STRUCT_DEFAULTS(&hesap_bilgileri);

        CARI_KART_BILGILERINI_OKU( cari_hesap_id, &hesap_bilgileri  );

        current_row = ADD_NEW_LINE();

        QLineEdit * line_edit_adi_soyad       = ( QLineEdit * ) m_ui->table_widget_gun_satirlari->cellWidget(current_row ,ADI_COLUMN);

        line_edit_adi_soyad->setText( hesap_bilgileri.cari_hesap_ismi );

        int calisma_sekli                       = query.VALUE("calisma_sekli").toInt();

        prs_doviz_id                            = CARI_GET_PARA_BIRIM_ID( cari_hesap_id );

        int ucret_sekli_enum                    = query.VALUE( "ucret_sekli" ).toInt();
        double net_ucret                        = query.VALUE( "net_ucret"   ).toDouble();
        double brut_ucret                       = query.VALUE( "brut_ucret"  ).toDouble();
        double haftalik_calisilan_gun_sayisi    = query.VALUE( "haftalik_calisilan_gun_sayisi" ).toDouble();

        double prs_personel_ucret = net_ucret;
        if ( ucret_sekli_enum EQ PRS_BRUT ) {
            prs_personel_ucret    = brut_ucret;
        }

        QTableWidgetItem * new_item;

        new_item = new QTableWidgetItem(tr("%1").arg(personel_id));
        m_ui->table_widget_gun_satirlari->setItem(current_row ,ROW_ID_COLUMN ,new_item);

        new_item=new QTableWidgetItem(tr("%1").arg(record_id));
        m_ui->table_widget_gun_satirlari->setItem(current_row ,RECORD_ID_COLUMN ,new_item);

        QLineEdit * line_edit_calisma_sekli  = ( QLineEdit * ) m_ui->table_widget_gun_satirlari->cellWidget(current_row, CALISMA_SEKLI);
        line_edit_calisma_sekli->setText( QVariant ( calisma_sekli ).toString() );

        s_query.PREPARE_SELECT ("prs_puantaj","gun_sayisi ",
                                "personel_id = :personel_id  "
                                "AND bordro_donemi_yil    = :bordro_donemi_yil  "
                                "AND bordro_donemi_ay     = :bordro_donemi_ay   ");
        s_query.SET_VALUE (":personel_id"       ,  personel_id   );
        s_query.SET_VALUE (":bordro_donemi_yil" ,  m_bordro_yili );
        s_query.SET_VALUE (":bordro_donemi_ay"  ,  m_bordro_ayi );

        QCommaEdit * comma_edit_doviz_kuru              = ( QCommaEdit * ) m_ui->table_widget_gun_satirlari->cellWidget( current_row, KUR_COLUMN );
        QCommaEdit * comma_edit_aldigi_ucret            = ( QCommaEdit * ) m_ui->table_widget_gun_satirlari->cellWidget( current_row, ALDIGI_UCRET );
        QCommaEdit * comma_edit_ucret_tutari            = ( QCommaEdit * ) m_ui->table_widget_gun_satirlari->cellWidget( current_row, TEMEL_PARABIRIMI_UCRET );
        QCommaEdit * comma_edit_gun                     = ( QCommaEdit * ) m_ui->table_widget_gun_satirlari->cellWidget(current_row,CALISTIGI_GUN_COLUMN);
        QCommaEdit * comma_edit_ek_odenek               = ( QCommaEdit * ) m_ui->table_widget_gun_satirlari->cellWidget(current_row,EK_ODENEK_TUTARI);
        QCommaEdit * comma_edit_ek_kesinti              = ( QCommaEdit * ) m_ui->table_widget_gun_satirlari->cellWidget(current_row,EK_KESINTI_TUTARI);
        QCommaEdit * comma_edit_gunluk_ucret            = ( QCommaEdit * ) m_ui->table_widget_gun_satirlari->cellWidget(current_row,GUNLUK_UCRET   );
        QCommaEdit * comma_edit_yemek_verilen_gun_sayisi= ( QCommaEdit * ) m_ui->table_widget_gun_satirlari->cellWidget(current_row,YEMEK_VERILEN_GUN_SAYISI   );

        comma_edit_yemek_verilen_gun_sayisi->SET_DOUBLE( haftalik_calisilan_gun_sayisi * 4 );

        double eksik_gun_sayisi = PRS_GET_EKSIK_GUN_SAYISI( personel_id, m_bordro_ayi, m_bordro_yili );

        if ( eksik_gun_sayisi > 0.00 ) {

            if ( isten_cikis_tarihi NE "9999.99.99" ) {
                comma_edit_gun->SET_DOUBLE( QDate::fromString( isten_cikis_tarihi, "yyyy.MM.dd").daysInMonth() -  eksik_gun_sayisi );
            }
            else {
                comma_edit_gun->SET_DOUBLE( QDate::fromString( bordro_bts_donemi, "yyyy.MM.dd").daysInMonth() -  eksik_gun_sayisi );
            }
        }
        else {
            if ( isten_cikis_tarihi NE "9999.99.99" ) {
                QDate isten_cikis_date = QDate::fromString( isten_cikis_tarihi, "yyyy.MM.dd");
                comma_edit_gun->SET_DOUBLE( isten_cikis_date.day() );
            }
            else {
                comma_edit_gun->SET_DOUBLE( 30 );
            }
        }

        int gun_sayisi = comma_edit_gun->GET_DOUBLE();
        if ( ise_giris_tarihi.year() EQ m_bordro_yili )  {

            QDate bordro_tarihi;
            if ( ise_giris_tarihi.month() EQ m_bordro_ayi ) {
                int ise_giris_gunu = ise_giris_tarihi.day();

                bordro_tarihi = QDate::fromString( bordro_bts_donemi, "yyyy.MM.dd" );

                if ( isten_cikis_tarihi NE "9999.99.99" ) {
                    bordro_tarihi = QDate::fromString( isten_cikis_tarihi, "yyyy.MM.dd" );
                    gun_sayisi = bordro_tarihi.day();
                }
                else {
                    gun_sayisi = bordro_tarihi.daysInMonth();
                }

                gun_sayisi = gun_sayisi - ise_giris_gunu + 1 ;

                comma_edit_gun->SET_INTEGER( gun_sayisi );
            }

            comma_edit_yemek_verilen_gun_sayisi->SET_DOUBLE( haftalik_calisilan_gun_sayisi * floor( comma_edit_gun->GET_DOUBLE() / 7.0 ) );
        }

        // GUNLUK UCRET PUANTAJ'DA GUN DEGISTIRILIRSE OTOMATIK CARPILACAK
        comma_edit_gunluk_ucret->SET_DOUBLE( ROUND( prs_personel_ucret / 30 ));
        if ( calisma_sekli EQ ENUM_GUNLUK ) {
            comma_edit_gunluk_ucret->SET_DOUBLE( prs_personel_ucret );
        }
        if ( calisma_sekli EQ ENUM_AYLIK and gun_sayisi > 30 ) {
            comma_edit_gun->SET_DOUBLE( 30 );
        }

        if ( calisma_sekli EQ ENUM_GUNLUK ) {
            prs_personel_ucret = ROUND( comma_edit_gun->GET_DOUBLE() * comma_edit_gunluk_ucret->GET_DOUBLE() );
        }

        if ( prs_doviz_id NE DVZ_GET_TEMEL_PARA_BIRIMI_ID() ) {
            comma_edit_doviz_kuru->setEnabled( true );
        }

        // personel ek odenek bilgileri sorgulaniyor.

        double toplam_ek_odenek  = 0.00;
        double toplam_ek_kesinti = 0.00;

        SQL_QUERY t_query( DB );

        t_query.PREPARE_SELECT( "prs_ek_kesintiler_odenekler",
                                "yuzde_mi, yuzde_orani, tutar, kesinti_odenek_turu ",
                                "personel_id         = :personel_id       AND "
                                "bordro_donemi_yil   = :bordro_donemi_yil AND "
                                "bordro_donemi_ay    = :bordro_donemi_ay      ");

        t_query.SET_VALUE( ":personel_id"           , personel_id       );
        t_query.SET_VALUE( ":bordro_donemi_yil"     , m_bordro_yili     );
        t_query.SET_VALUE( ":bordro_donemi_ay "     , m_bordro_ayi      );

        if ( t_query.SELECT() NE 0 ) {
            while ( t_query.NEXT() EQ true ) {
                int     yuzde_mi            = t_query.VALUE( "yuzde_mi" ).toInt();
                int     kesinti_odenek_turu = t_query.VALUE( "kesinti_odenek_turu" ).toInt();
                double  yuzde_orani         = t_query.VALUE( "yuzde_orani" ).toDouble();
                double  tutar               = t_query.VALUE( "tutar" ).toDouble();

                if ( yuzde_mi EQ 1 ) {
                    if ( kesinti_odenek_turu EQ ENUM_PRS_ODENEK ) {
                        toplam_ek_odenek    += ROUND( prs_personel_ucret * yuzde_orani );
                    }
                    if ( kesinti_odenek_turu EQ ENUM_PRS_KESINTI ) {
                        toplam_ek_kesinti  += ROUND( prs_personel_ucret * yuzde_orani );
                    }
                }
                else {
                    if ( kesinti_odenek_turu EQ ENUM_PRS_ODENEK ) {
                        toplam_ek_odenek    += tutar;
                    }
                    if ( kesinti_odenek_turu EQ ENUM_PRS_KESINTI ) {
                        toplam_ek_kesinti  += tutar;
                    }
                }
            }
        }

        comma_edit_aldigi_ucret->SET_DOUBLE ( prs_personel_ucret );
        comma_edit_ek_odenek->SET_DOUBLE    ( toplam_ek_odenek   );
        comma_edit_ek_kesinti->SET_DOUBLE   ( toplam_ek_kesinti  );
        comma_edit_doviz_kuru->SET_DOUBLE   ( DVZ_DOVIZ_KURUNU_AL( prs_doviz_id, QDate::currentDate(), ENUM_SATIS ) );
        comma_edit_ucret_tutari->SET_DOUBLE ( ROUND( comma_edit_doviz_kuru->GET_DOUBLE() * prs_personel_ucret ) );

        if ( s_query.SELECT() EQ 0 ) {
            DB->START_TRANSACTION();
            QCommaEdit * comma_edit_kur   =  ( QCommaEdit * ) m_ui->table_widget_gun_satirlari->cellWidget(current_row ,KUR_COLUMN);
            SQL_QUERY insert_query(DB);
            insert_query.PREPARE_INSERT("prs_puantaj", "puantaj_id" ,
                                        "personel_id , gun_sayisi ,doviz_kuru,  "
                                        "temel_para_birim_tutari , bordro_donemi_yil, bordro_donemi_ay, yemek_verilen_gun_sayisi ");

            insert_query.SET_VALUE(":personel_id"               , personel_id);
            insert_query.SET_VALUE(":gun_sayisi"                , comma_edit_gun->GET_DOUBLE());
            insert_query.SET_VALUE(":doviz_kuru"                , comma_edit_kur->GET_DOUBLE());
            insert_query.SET_VALUE(":temel_para_birim_tutari"   , comma_edit_ucret_tutari->GET_DOUBLE() );
            insert_query.SET_VALUE(":bordro_donemi_yil"         , m_bordro_yili );
            insert_query.SET_VALUE(":bordro_donemi_ay"          , m_bordro_ayi );
            insert_query.SET_VALUE(":yemek_verilen_gun_sayisi"  , comma_edit_yemek_verilen_gun_sayisi->GET_DOUBLE() );

            insert_query.INSERT();
            DB->COMMIT_TRANSACTION();
        }

    }
    return ADAK_OK;
}