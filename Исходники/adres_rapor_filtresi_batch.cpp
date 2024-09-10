int ADRES_RAPOR_FILTRESI_BATCH::CHECK_VAR ( QObject * p_object )
{

    SQL_QUERY sql_query ( DB );

    if ( p_object EQ m_ui->radioButton_firmalar ) {
        if ( m_ui->radioButton_firmalar->isChecked() EQ true ) {
            m_adres_kayit_turu = FIRMA_KAYDI;
        }
    }
    else if ( p_object EQ m_ui->radioButton_sahislar ) {
        if ( m_ui->radioButton_sahislar->isChecked() EQ true ) {
            m_adres_kayit_turu = SAHIS_KAYDI;
        }
    }
    else if ( p_object EQ m_ui->radioButton_firma_sahis ) {
        if ( m_ui->radioButton_firma_sahis->isChecked() EQ true ) {
            m_adres_kayit_turu = SAHIS_ARTI_FIRMA;
        }
    }
    else if ( p_object EQ m_ui->checkBox_grup_secimi ) {
        if ( m_ui->checkBox_grup_secimi->isChecked() EQ true ) {
            m_ui->frame_gruplar->setEnabled ( true );
            SET_FOCUS( m_ui->button_grup_ekle );
        }
        else {
            m_ui->frame_gruplar->setEnabled ( false );
            m_ui->textEdit_gruplar->clear();
        }
    }
    else if ( p_object EQ m_ui->checkBox_adres_kaydi_secimi ) {
        if ( m_ui->checkBox_adres_kaydi_secimi->isChecked() EQ true ) {
            m_ui->frame_adres_kayitlari->setEnabled ( true );
            SET_FOCUS( m_ui->button_adres_kaydi_ekle );
        }
        else {
            m_ui->frame_adres_kayitlari->setEnabled ( false );
        }
    }
    else if ( p_object EQ m_ui->button_grup_ekle ) {


        if ( OPEN_GRUP_SECIM( E9_PROGRAMI,ADRES_MODULU , &m_grup_idleri , DB , this , true) EQ true ) {
            m_ui->textEdit_gruplar->setText ( GRP_GRUP_ADLARINI_BUL(&m_grup_idleri , new QStringList() , new QStringList()) );
        }

    }

    else if ( p_object EQ m_ui->button_adres_kaydi_ekle ) {

        QList<int> adres_id = OPEN_ADRES_ARAMA_LIST( m_adres_kayit_turu,true, this );

        if ( adres_id.size() EQ 0 ) {
            return ADAK_OK;
        }

        QString adres_id_str = "";

        for ( int i = 0 ; i < adres_id.size() ; i++ ) {
            if ( adres_id_str.isEmpty() EQ false ) {
                adres_id_str.append(" OR ");
            }

            adres_id_str.append(QString(" adres_id=" + QVariant(adres_id.at(i)).toString()));
        }

        sql_query.PREPARE_SELECT ( "adr_adresler","firma_sahis_adi,email,adres_id",adres_id_str );

        if ( sql_query.SELECT() EQ 0 ) {
            ADAK_WARNING( tr ( "Seçili kayıt bulunamadı"), NULL, this );
            return ADAK_FAIL;
        }

        bool email_bulundu           = false;
        bool table_widget_temizlendi = false;

        while ( sql_query.NEXT() EQ true ) {
            if ( m_adres_rapor_turu EQ TOPLU_MAIL_GONDERIMI ) {
                if (sql_query.VALUE(1).toString().isEmpty() EQ true ) {
                    SQL_QUERY query (DB);
                    query.PREPARE_SELECT("adr_emailler","email_adresi","gizli_kayit=:gizli_kayit AND adres_kayit_id=:adres_kayit_id");
                    query.SET_VALUE(":gizli_kayit"   ,0 );
                    query.SET_VALUE(":adres_kayit_id",sql_query.VALUE(2).toInt());
                    if ( query.SELECT() EQ 0 ) {
                        continue;
                    }
                }
                email_bulundu = true;
            }

            QString firma_sahis_adi = sql_query.VALUE(0).toString();

            if ( table_widget_temizlendi EQ false ) {
                for ( int i = m_ui->tableWidget_adres_kayitlari->rowCount() ; i > 0 ; i-- ) {
                    m_ui->tableWidget_adres_kayitlari->removeRow(i-1);
                }

                table_widget_temizlendi = true;
            }

            m_ui->tableWidget_adres_kayitlari->insertRow ( m_ui->tableWidget_adres_kayitlari->rowCount() );
            m_ui->tableWidget_adres_kayitlari->setItem   ( m_ui->tableWidget_adres_kayitlari->rowCount() -1, 0, new QTableWidgetItem ( QVariant( sql_query.VALUE(2) ).toString()));
            m_ui->tableWidget_adres_kayitlari->setItem   ( m_ui->tableWidget_adres_kayitlari->rowCount() -1, 1, new QTableWidgetItem ( firma_sahis_adi ));
        }

        if ( m_adres_rapor_turu EQ TOPLU_MAIL_GONDERIMI ) {
            if (email_bulundu EQ false ) {
                ADAK_WARNING( tr ( "Seçili kayıtta email adresi bulunamadı."), NULL, this );
                return ADAK_FAIL;
            }
        }
    }
    else if ( p_object EQ m_ui->tableWidget_adres_kayitlari ) {
        if ( p_object->objectName() EQ "ITEM_DOUBLE_CLICKED" ) {
            int clicked_row = m_ui->tableWidget_adres_kayitlari->currentRow();
            m_ui->tableWidget_adres_kayitlari->removeRow ( clicked_row );
        }
    }

    return ADAK_OK;
}