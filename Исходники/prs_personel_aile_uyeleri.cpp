int PRS_PERSONEL_AILE_FISI::GET_FIS_RECORD ( int record_id )
{
    SQL_QUERY   sql_query_personel (DB);
    SQL_QUERY   query              (DB);


    int cari_hesap_id =  0 ;
    sql_query_personel.PREPARE_SELECT( "prs_personeller ","sicil_no, cari_hesap_id","personel_id = :personel_id" );

    sql_query_personel.SET_VALUE(":personel_id", record_id);

    if ( sql_query_personel.SELECT() NE 0 ) {

        sql_query_personel.NEXT();

        line_edit_personel_sicil_no->setText ( sql_query_personel.VALUE(0).toString() );
        cari_hesap_id     =   sql_query_personel.VALUE( 1 ).toInt();
    }

    CARI_HESAP_STRUCT hesap_bilgileri;
    CARI_SET_HESAP_STRUCT_DEFAULTS(&hesap_bilgileri);

    CARI_KART_BILGILERINI_OKU( cari_hesap_id, &hesap_bilgileri  );

    line_edit_personel_adi->setText         ( hesap_bilgileri.cari_hesap_ismi);

    query.PREPARE_SELECT ( "prs_personel_aile_uyeleri ",
                           "aile_bilgi_id , personel_id, order_number, aciklama, "
                           "adi_soyadi,  tc_kimlik_no,akrabalik_derecesi,dogum_tarihi, "
                           "ogrenim_durumu, calisma_durumu,"
                           "cinsiyet, asgari_gecim_ind_durumu ",
                           "personel_id = :personel_id ");

    query.SET_VALUE      ( ":personel_id",  record_id );

    if ( query.SELECT("order_number ASC" ) NE 0 ) {

        while ( query.NEXT() EQ true ) {

            int p_current_row;

            p_current_row = ADD_NEW_LINE ();

            QWidget    *   cell_widget = table_widget_aile_satirlari->cellWidget( p_current_row, AD_SOYAD_COLUMN );
            QLineEdit  *   line_edit_ad_soyad    = static_cast < QLineEdit * > ( cell_widget );
            line_edit_ad_soyad->setText( query.VALUE("adi_soyadi").toString() );

            cell_widget = table_widget_aile_satirlari->cellWidget( p_current_row, TC_KIMLIK_NO_COLUMN );
            QLineEdit  *   line_edit_tc_kimlik_no    = static_cast < QLineEdit * > ( cell_widget );
            line_edit_tc_kimlik_no->setText( query.VALUE("tc_kimlik_no").toString() );

            cell_widget = table_widget_aile_satirlari->cellWidget( p_current_row, AKRABALIK_DERECESI_COLUMN );
            QComboBox  *   combo_box_akrabalik_derecesi    = static_cast < QComboBox * > ( cell_widget );

            FIND_AND_SET_COMBOBOX_TEXT(combo_box_akrabalik_derecesi ,
                                       PRS_GET_AKRABALIK_DERECESI_STRING(query.VALUE("akrabalik_derecesi").toInt()));

            cell_widget = table_widget_aile_satirlari->cellWidget( p_current_row, CALISMA_DURUMU_COLUMN );
            QComboBox  *   combo_box_calisma_durumu    = static_cast < QComboBox * > ( cell_widget );

            FIND_AND_SET_COMBOBOX_TEXT(combo_box_calisma_durumu , PRS_GET_CALISMA_DURUMU_STRING(query.VALUE("calisma_durumu").toInt()));

            cell_widget = table_widget_aile_satirlari->cellWidget( p_current_row, DOGUM_TARIHI_COLUMN);
            QAdakDate * adakDate_dogum_tarihi = static_cast<QAdakDate*> (cell_widget);
            adakDate_dogum_tarihi->SET_DATE( query.VALUE("dogum_tarihi").toString());

            cell_widget = table_widget_aile_satirlari->cellWidget( p_current_row, EGITIM_DURUMU_COLUMN );
            QComboBox  *   combo_box_egitim_durumu    = static_cast < QComboBox * > ( cell_widget );

            FIND_AND_SET_COMBOBOX_TEXT(combo_box_egitim_durumu , query.VALUE("ogrenim_durumu").toString());

            cell_widget = table_widget_aile_satirlari->cellWidget( p_current_row, CINSIYET_COLUMN );
            QComboBox  *   combo_box_cinsiyet    = static_cast < QComboBox * > ( cell_widget );

            FIND_AND_SET_COMBOBOX_TEXT(combo_box_cinsiyet , query.VALUE("cinsiyet").toString());

            cell_widget = table_widget_aile_satirlari->cellWidget( p_current_row, ACIKLAMA_COLUMN );
            QLineEdit  *   line_edit_aciklama    = static_cast < QLineEdit * > ( cell_widget );
            line_edit_aciklama->setText( query.VALUE("aciklama").toString() );

            cell_widget = table_widget_aile_satirlari->cellWidget( p_current_row, ASGARI_GECIM_IND_DURUMU_COLUMN );
            QComboBox  *   combo_box_asagari_gecim_ind_durumu  = static_cast < QComboBox * > ( cell_widget );

            int asgari_gecim_ind_durumu = query.VALUE( "asgari_gecim_ind_durumu" ).toInt();

            FIND_AND_SET_COMBOBOX_TEXT( combo_box_asagari_gecim_ind_durumu , PRS_GET_EVET_HAYIR_DURUMU_STRING(asgari_gecim_ind_durumu));


            QString id                      = query.VALUE("aile_bilgi_id").toString();
            QString personel_id             = query.VALUE("personel_id").toString();
            QString order_number            = query.VALUE("order_number").toString();


            QTableWidgetItem * new_item;

            table_widget_aile_satirlari->setHorizontalHeaderLabels(QStringList()<<"id"<<"record_id"<<"satir_order"
                                                                    <<tr("Ad Soyad")<<tr("TC Kimlik No")<<tr("Akrabalık Derecesi")<<("Çalışma Durumu")
                                                                    <<tr("Doğum Tarihi")<<tr("Eğitim Düzeyi")
                                                                    <<tr("Cinsiyet")<< tr("Asgari Geçim \n İndirimi") << tr("Açıklama")<<tr("")<<tr("") );

            new_item = new QTableWidgetItem(tr("%1").arg(id));
            table_widget_aile_satirlari->setItem(p_current_row, ROW_ID_COLUMN, new_item);

            new_item = new QTableWidgetItem(tr("%1").arg(personel_id));
            table_widget_aile_satirlari->setItem(p_current_row, RECORD_ID_COLUMN, new_item);

            new_item = new QTableWidgetItem(tr("%1").arg(order_number));
            table_widget_aile_satirlari->setItem(p_current_row, ORDER_COLUMN, new_item);

        }
    }
    return ADAK_OK;
}