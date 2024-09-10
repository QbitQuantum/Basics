int MUH_HESAP_EKLEME_FISI::GET_FIS_RECORD ( int p_fis_id )
{
    SQL_QUERY query ( DB );

    query.PREPARE_SELECT("muh_hesaplar" , "tam_hesap_kodu, hesap_ismi, hesap_seviyesi, hesap_kodu" ,
                         "hesap_id = :hesap_id");
    query.SET_VALUE      (":hesap_id", p_fis_id );

    if ( query.SELECT() EQ 0 ) {
        return ADAK_FAIL;
    }

    query.NEXT();

    m_ui->line_edit_hesap_kodu->setText( query.VALUE(0).toString() );
    m_ui->lineEdit_hesap_ismi->setText( query.VALUE(1).toString() );

    m_ana_hesap_seviyesi = query.VALUE(2).toInt();
    m_ana_hesap_kodu     = query.VALUE(3).toString();


    m_ui->line_edit_hesap_kodu->setEnabled( false );
    m_ui->lineEdit_hesap_ismi->setEnabled( false );

    if ( m_ana_hesap_seviyesi EQ 1 ) {
        m_ui->line_edit_hesap_kodu->setEnabled( true );
        m_ui->lineEdit_hesap_ismi->setEnabled ( true );
    }

    query.PREPARE_SELECT("muh_hesaplar" , "hesap_id, hesap_kodu, hesap_ismi" ,
                         "parent_id = :parent_id");
    query.SET_VALUE  ( ":parent_id", p_fis_id );

    if ( query.SELECT("hesap_kodu") EQ 0 ) {
        return ADAK_OK;
    }

    int current_row = 0;

    while ( query.NEXT() EQ true ) {

        current_row        = ADD_NEW_LINE();

        QLineEdit * lineEdit_hesap_kodu     =  ( QLineEdit * ) m_ui->tablewidget_alt_hesaplar->cellWidget ( current_row, HESAP_KODU_COLUMN      );
        QLineEdit * lineEdit_hesap_ismi     =  ( QLineEdit * ) m_ui->tablewidget_alt_hesaplar->cellWidget ( current_row, HESAP_ISMI_COLUMN      );
        QLineEdit * lineEdit_gruplar        =  ( QLineEdit * ) m_ui->tablewidget_alt_hesaplar->cellWidget ( current_row, HESAP_GRUPLAR          );
        QLineEdit * lineEdit_tam_hesap_kodu =  ( QLineEdit * ) m_ui->tablewidget_alt_hesaplar->cellWidget ( current_row, TAM_HESAP_KODU_COLUMN  );

        QTableWidgetItem * new_item;

        new_item = new QTableWidgetItem         ( query.VALUE(0).toString() );
        m_ui->tablewidget_alt_hesaplar->setItem (  current_row, ROW_ID_COLUMN, new_item );

        new_item = new QTableWidgetItem         ( QVariant ( p_fis_id ).toString() );
        m_ui->tablewidget_alt_hesaplar->setItem ( current_row, ANA_HESAP_ID_COLUMN, new_item );

        lineEdit_hesap_kodu->setText        ( query.VALUE(1).toString() );
        lineEdit_hesap_ismi->setText        ( query.VALUE(2).toString() );
        lineEdit_tam_hesap_kodu->setText    ( m_ui->line_edit_hesap_kodu->text() + m_delimeter + query.VALUE(1).toString() );

        QList<int> grup_idleri;

        lineEdit_gruplar->setText(GRP_KAYDIN_GRUPLARINI_BUL(E9_PROGRAMI,MUHASEBE_MODULU,query.VALUE(0).toInt(),&grup_idleri,new QStringList(), new QStringList()));

        QString    grup_id_str = "";

        for ( int i = 0 ; i < grup_idleri.size() ; i++ ) {
            if ( grup_id_str.isEmpty() EQ false ) {
                grup_id_str.append("\t");
            }
            grup_id_str .append( QVariant(grup_idleri.at(i)).toString());
        }

        m_ui->tablewidget_alt_hesaplar->setItem(current_row,GRUP_IDLERI,new QTableWidgetItem(grup_id_str));
    }

    return ADAK_OK;
}