int PRS_PERSONEL_ODENEK_EKLEME_FISI::GET_FIS_RECORD ( int record_id )
{
    SQL_QUERY   sql_query(DB);
    SQL_QUERY   query    (DB);

    sql_query.PREPARE_SELECT( "prs_personeller ",
                              "sicil_no, cari_hesap_id",
                              "personel_id = :personel_id" );
    sql_query.SET_VALUE( ":personel_id", record_id );

    if ( sql_query.SELECT() EQ 0 ) {
        return ADAK_FAIL;
    }

    sql_query.NEXT();

    line_edit_personel_sicil_no->setText ( sql_query.VALUE(0).toString() );

    int cari_hesap_id   = sql_query.VALUE( 1 ).toInt();

    CARI_HESAP_STRUCT hesap_bilgileri;
    CARI_SET_HESAP_STRUCT_DEFAULTS(&hesap_bilgileri);

    CARI_KART_BILGILERINI_OKU( cari_hesap_id, &hesap_bilgileri  );

    line_edit_personel_adi_soyadi->setText( hesap_bilgileri.cari_hesap_ismi );


    query.PREPARE_SELECT ( "prs_ek_kesintiler_odenekler",
                           "kesinti_odenek_id, personel_id, order_number,  "
                           "odenek_kesinti_adi, bordro_donemi_ay, bordro_donemi_yil, ssk_kesintisi_iceriyor_mu, "
                           "gelir_vergisi_iceriyor_mu, damga_vergisi_iceriyor_mu, "
                           "yuzde_mi, yuzde_orani, tutar, aciklama, bordro_id ",
                           "personel_id = :personel_id "
                           "AND kesinti_odenek_turu = :kesinti_odenek_turu ");


    query.SET_VALUE      ( ":personel_id",          record_id );
    query.SET_VALUE      ( ":kesinti_odenek_turu"  , ENUM_PRS_ODENEK);

    query.SELECT("order_number ASC" );

    while ( query.NEXT() EQ true ) {

        int p_current_row;

        p_current_row = ADD_NEW_LINE ();

        QWidget     *  cell_widget = table_widget_odenek_satirlari->cellWidget( p_current_row, BORDRO_DONEMI_AY_COLUMN );
        QLineEdit   *   line_edit_odenek_adi                        = ( QLineEdit  * ) table_widget_odenek_satirlari->cellWidget( p_current_row, ODENEK_ADI_COLUMN );
        QComboBox   *   combo_box_bordro_donemi_ay                  = ( QComboBox  * ) table_widget_odenek_satirlari->cellWidget( p_current_row, BORDRO_DONEMI_AY_COLUMN );
        QComboBox   *   combo_box_bordro_donemi_yil                 = ( QComboBox  * ) table_widget_odenek_satirlari->cellWidget( p_current_row, BORDRO_DONEMI_YIL_COLUMN );
        QCheckBox   *   check_box_odenek_ssk_kesintisi_iceriyor_mu  = ( QCheckBox  * ) table_widget_odenek_satirlari->cellWidget( p_current_row, ODENEK_SSK_KESINTISI_ICERIYOR_MU_COLUMN );
        QCheckBox   *   check_box_odenek_gelir_vergisi_iceriyor_mu  = ( QCheckBox  * ) table_widget_odenek_satirlari->cellWidget( p_current_row, ODENEK_GELIR_VERGISI_ICERIYOR_MU_COLUMN );
        QCheckBox   *   check_box_odenek_damga_vergisi_iceriyor_mu  = ( QCheckBox  * ) table_widget_odenek_satirlari->cellWidget( p_current_row, ODENEK_DAMGA_VERGISI_ICERIYOR_MU_COLUMN );
        QComboBox   *   combo_box_odenek_yuzde_mi                   = ( QComboBox  * ) table_widget_odenek_satirlari->cellWidget( p_current_row, ODENEK_YUZDE_MI_COLUMN );
        QCommaEdit  *   comma_edit_yuzde_orani                      = ( QCommaEdit * ) table_widget_odenek_satirlari->cellWidget( p_current_row, YUZDE_COLUMN );
        QCommaEdit  *   comma_edit_tutar                            = ( QCommaEdit * ) table_widget_odenek_satirlari->cellWidget( p_current_row, TUTAR_COLUMN );

        line_edit_odenek_adi->setText( query.VALUE("odenek_kesinti_adi").toString() );
        combo_box_bordro_donemi_ay->setCurrentIndex( query.VALUE("bordro_donemi_ay").toInt() );
        combo_box_bordro_donemi_yil->setCurrentIndex( combo_box_bordro_donemi_yil->findText( query.VALUE("bordro_donemi_yil").toString()) );
        check_box_odenek_ssk_kesintisi_iceriyor_mu->setChecked( query.VALUE("ssk_kesintisi_iceriyor_mu").toInt() );
        check_box_odenek_gelir_vergisi_iceriyor_mu->setChecked( query.VALUE("gelir_vergisi_iceriyor_mu").toInt() );
        check_box_odenek_damga_vergisi_iceriyor_mu->setChecked( query.VALUE("damga_vergisi_iceriyor_mu").toInt() );
        combo_box_odenek_yuzde_mi->setCurrentIndex( query.VALUE("yuzde_mi").toInt() );
        comma_edit_yuzde_orani->SET_DOUBLE ( query.VALUE("yuzde_orani").toDouble() );
        comma_edit_tutar->SET_DOUBLE ( query.VALUE("tutar").toDouble() );

        if ( combo_box_odenek_yuzde_mi->currentText() EQ tr("TUTAR") ) {
            comma_edit_tutar->setEnabled( true );
        }
        else {
            comma_edit_yuzde_orani->setEnabled( true );
        }

        cell_widget = table_widget_odenek_satirlari->cellWidget( p_current_row, ACIKLAMA_COLUMN );
        QLineEdit  *   line_edit_aciklama    = static_cast < QLineEdit * > ( cell_widget );
        line_edit_aciklama->setText( query.VALUE("aciklama").toString() );


        QString id                                  = query.VALUE("kesinti_odenek_id").toString();
        QString personel_id                         = query.VALUE("personel_id").toString();
        QString order_number                        = query.VALUE("order_number").toString();

        QTableWidgetItem * new_item;

        new_item = new QTableWidgetItem(tr("%1").arg(id));
        table_widget_odenek_satirlari->setItem(p_current_row, ROW_ID_COLUMN, new_item);

        new_item = new QTableWidgetItem(tr("%1").arg(personel_id));
        table_widget_odenek_satirlari->setItem(p_current_row, RECORD_ID_COLUMN, new_item);

        new_item = new QTableWidgetItem(tr("%1").arg(order_number));
        table_widget_odenek_satirlari->setItem(p_current_row, ORDER_COLUMN, new_item);

    }
    return ADAK_OK;
}