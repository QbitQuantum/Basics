void MUH_FIS_KOPYALAMA_BATCH::SEARCH_EDIT_CLICKED ( QWidget * widget, QLineEdit * lineEdit  )
{
    Q_UNUSED ( widget );

    int fis_id = OPEN_MUH_FIS_ARAMA ( 0, MUHASEBE_MODULU, -1, ENUM_MUHASEBE_FISI, this );

    if ( fis_id < 1 ) {
        return;
    }

    SQL_QUERY query ( DB );

    query.PREPARE_SELECT("muh_fisler" , "fis_no" , "fis_id = :fis_id");

    query.SET_VALUE      ( ":fis_id" , fis_id );
    if ( query.SELECT() EQ 0 ) {
        MSG_WARNING( tr ( "Fiş bulunamadı"), NULL );
        SET_FOCUS( m_ui->lineEdit_yeni_fis_no );
        return;
    }

    query.NEXT();
    lineEdit->setText ( query.VALUE(0).toString() );
    m_fis_id = fis_id;
}