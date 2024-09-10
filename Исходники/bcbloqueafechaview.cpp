void BcBloqueaFechaView::inicializa()
{
    BL_FUNC_DEBUG
    BcTreeWidgetItem *itemlevel0;
    BcTreeWidgetItem *itemlevel1 = 0;

    QString consultabd;
    mui_treeWidget->setColumnCount ( 2 );
    QStringList cabecera;
    cabecera << _ ( "Ejercicio" ) << _ ( "Estado" );
    mui_treeWidget->setColumnWidth ( 0, 200 );
    mui_treeWidget->setHeaderLabels ( cabecera );

    mui_treeWidget->clear();
    mui_treeWidget->setSortingEnabled ( FALSE );

    /// Consultamos a la base de datos.
    consultabd.sprintf ( "SELECT * FROM ejercicios WHERE periodo = 0 ORDER BY ejercicio DESC" );
    BlDbRecordSet *curPeri, *curEjer = mainCompany() ->loadQuery ( consultabd );

    while ( !curEjer->eof() ) {

        itemlevel0 = new BcTreeWidgetItem ( mui_treeWidget );
        itemlevel0->setText ( 0, curEjer->value( "ejercicio" ) ); /// Columna 0.

        if ( curEjer->value( "bloqueado" ) == "t" ) {
            itemlevel0->setText ( 1, qsbloqueado );
        } else {
            itemlevel0->setText ( 1, qsabierto );
        } // end if

        itemlevel0->ej = curEjer->value( "ejercicio" );
        itemlevel0->per = curEjer->value( "periodo" );


        consultabd.sprintf ( "SELECT * FROM ejercicios WHERE ejercicio = '%s' ORDER BY periodo DESC", curEjer->value( "ejercicio" ).toAscii().constData() );
        curPeri = mainCompany() ->loadQuery ( consultabd );
        while ( !curPeri->eof() ) {
            switch ( curPeri->value( "periodo" ).toInt() ) {
            case 12:
                itemlevel1 = new BcTreeWidgetItem ( itemlevel0 );
                itemlevel1->setText ( 0, _ ( "Diciembre" ) ); /// Columna 0.
                break;
            case 11:
                itemlevel1 = new BcTreeWidgetItem ( itemlevel0 );
                itemlevel1->setText ( 0, _ ( "Noviembre" ) ); /// Columna 0.
                break;
            case 10:
                itemlevel1 = new BcTreeWidgetItem ( itemlevel0 );
                itemlevel1->setText ( 0, _ ( "Octubre" ) ); /// Columna 0.
                break;
            case 9:
                itemlevel1 = new BcTreeWidgetItem ( itemlevel0 );
                itemlevel1->setText ( 0, _ ( "Septiembre" ) ); /// Columna 0.
                break;
            case 8:
                itemlevel1 = new BcTreeWidgetItem ( itemlevel0 );
                itemlevel1->setText ( 0, _ ( "Agosto" ) ); /// Columna 0.
                break;
            case 7:
                itemlevel1 = new BcTreeWidgetItem ( itemlevel0 );
                itemlevel1->setText ( 0, _ ( "Julio" ) ); /// Columna 0.
                break;
            case 6:
                itemlevel1 = new BcTreeWidgetItem ( itemlevel0 );
                itemlevel1->setText ( 0, _ ( "Junio" ) ); /// Columna 0.
                break;
            case 5:
                itemlevel1 = new BcTreeWidgetItem ( itemlevel0 );
                itemlevel1->setText ( 0, _ ( "Mayo" ) ); /// Columna 0.
                break;
            case 4:
                itemlevel1 = new BcTreeWidgetItem ( itemlevel0 );
                itemlevel1->setText ( 0, _ ( "Abril" ) ); /// Columna 0.
                break;
            case 3:
                itemlevel1 = new BcTreeWidgetItem ( itemlevel0 );
                itemlevel1->setText ( 0, _ ( "Marzo" ) ); /// Columna 0.
                break;
            case 2:
                itemlevel1 = new BcTreeWidgetItem ( itemlevel0 );
                itemlevel1->setText ( 0, _ ( "Febrero" ) ); /// Columna 0.
                break;
            case 1:
                itemlevel1 = new BcTreeWidgetItem ( itemlevel0 );
                itemlevel1->setText ( 0, _ ( "Enero" ) ); /// Columna 0.
                break;
            } // end switch
            itemlevel1->ej = curEjer->value( "ejercicio" );
            itemlevel1->per = curPeri->value( "periodo" );
            curPeri->value( "bloqueado" ) == "t" ? itemlevel1->setText ( 1, qsbloqueado ) : itemlevel1->setText ( 1, qsabierto );
            curPeri->nextRecord();
        } // end while
        curEjer->nextRecord();
    } // end while

    
}