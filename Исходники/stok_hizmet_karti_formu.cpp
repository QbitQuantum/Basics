int STOK_HIZMET_KARTI_FORMU::CHECK_UPDATE ( int record_id )
{
    SQL_QUERY query ( DB );

    query.PREPARE_SELECT ( "stk_urunler ","urun_id, urun_kodu, barkod_numarasi",
                           "urun_kodu         = :urun_kodu_1       "
                           "OR    urun_kodu         = :urun_kodu_2       "
                           "OR    barkod_numarasi   = :barkod_numarasi_1 "
                           "OR    barkod_numarasi   = :barkod_numarasi_2 ");

    query.SET_VALUE ( ":urun_kodu_1",       m_ui->lineEdit_hizmet_kodu->text()       );
    query.SET_VALUE ( ":urun_kodu_2",       m_ui->lineEdit_barkod_no->text() );
    query.SET_VALUE ( ":barkod_numarasi_1", m_ui->lineEdit_hizmet_kodu->text()       );
    query.SET_VALUE ( ":barkod_numarasi_2", m_ui->lineEdit_barkod_no->text() );

    if ( query.SELECT() > 0 ) {
        while ( query.NEXT() EQ true ) {
            if ( query.VALUE(0).toInt() NE record_id ) {
                QString a = query.VALUE(1).toString();
                if ( a  EQ m_ui->lineEdit_hizmet_kodu->text() ) {
                    if ( m_ui->lineEdit_hizmet_kodu->text().isEmpty() EQ false ) {
                        MSG_WARNING(  tr("Bu hizmet kodu ile bir ürün veya hizmet var. Hizmet kodunu değiştiriniz."), m_ui->lineEdit_hizmet_kodu );

                        return ADAK_FAIL;
                    }
                }
                else if ( query.VALUE(2).toString() EQ m_ui->lineEdit_hizmet_kodu->text() ) {
                    if ( m_ui->lineEdit_hizmet_kodu->text().isEmpty() EQ false ) {
                        MSG_WARNING(  tr ( "Bu hizmet kodu ile başka bir ürün veya hizmet barkod numarası kayıtlı. Hizmet kodunu değiştiriniz." ), m_ui->lineEdit_hizmet_kodu );

                        return ADAK_FAIL;
                    }

                }
                else if ( query.VALUE(1).toString() EQ m_ui->lineEdit_barkod_no->text() ) {
                    if ( m_ui->lineEdit_barkod_no->text().isEmpty() EQ false ) {
                        MSG_WARNING(  tr ( "Bu barkod numarası ile başka bir hizmet veya ürün kodu kayıtlı. Barkod numarasını değiştiriniz." ), m_ui->lineEdit_barkod_no );

                        return ADAK_FAIL;
                    }
                }
                else {
                    if ( m_ui->lineEdit_barkod_no->text().isEmpty() EQ false ) {
                        MSG_WARNING(  tr ( "Bu barkod numarası başka bir hizmette veya üründe barkod numarası olarak kayıtlı. Barkod numarasını değiştiriniz." ), m_ui->lineEdit_barkod_no );

                        return ADAK_FAIL;
                    }
                }
            }
        }
    }

    return ADAK_OK;
}