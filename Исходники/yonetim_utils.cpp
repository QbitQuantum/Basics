void CHECK_VERSION_UPGRADES (QString program_version_column_name , QString program_version_db_name, void UPGRADE_TO_VERSION_FUNC(QString) )
{
    SQL_QUERY query      ( DB );

    query.PREPARE_SELECT(program_version_db_name,program_version_column_name);

    if ( query.SELECT() EQ 0 ) {
        return;
    }
    query.NEXT();

    double program_version_in_db = query.VALUE(0).toDouble();
    double new_program_version   = ADAK_PROGRAM_VERSION(ADAK_VERITABANI_ID()).toDouble();

    if (program_version_in_db EQ new_program_version) {
        return;
    }

    if ( program_version_in_db > new_program_version ) {
        ADAK_ERROR(QObject::tr("Version of this program is smaller than the version of the database. Update the program, otherwise the data will be corrupted."),NULL,NULL);
        exit(77);//Bu programın versiyonu , veritabanının versiyonundan daha küçük. Programı güncelleyin , aksi taktirde verileriniz bozulur.
    }

    VERITABANLARINI_GUNCELLE();

//    QSplashScreen * splash = CREATE_SPLASH_SCREEN();
//    splash->show();
//    splash->showMessage((QString(QObject::tr("Upgrading Programme. Please wait..."))), Qt::AlignCenter, Qt::white );//Programınızın versiyonu yükseltiliyor. Lütfen Bekleyiniz...

    double current_program_version = program_version_in_db;

    DB->START_TRANSACTION();

    while ( current_program_version < new_program_version ) {        

        QString version = QVariant(current_program_version).toString();

        QStringList info = version.split(".",QString::SkipEmptyParts,Qt::CaseInsensitive);

        version.clear();

        if (info.size() NE 2) {
            version.append(info.at(0) + ".00");
        }
        else {
            if (info.at(1).size() NE 2) {
                version.append(info.at(0) + "." + info.at(1) + "0");
            }
            else {
                version.append(info.at(0) + "." + info.at(1));
            }
        }

        UPGRADE_TO_VERSION_FUNC(version);
        current_program_version = ROUND (current_program_version + 0.01);
    }

    query.PREPARE_UPDATE (program_version_db_name , "" , program_version_column_name , "");
    query.SET_VALUE ( QString(":%1").arg(program_version_column_name) , ADAK_PROGRAM_VERSION(ADAK_VERITABANI_ID()).toDouble());

    query.UPDATE();

//    splash->finish(NULL);

//    ADAK_WARNING(QObject::tr("Version of programme is upgrade.\n")+
//                QObject::tr("Please check User Authority for new properties. \n")+
//                QObject::tr("You can set User Authorization in the User's Screen.\n\n")+
//                QObject::tr("You can use Management Actions -> E9 repair for resolving some errors.")
//                ,NULL,NULL);

    DB->COMMIT_TRANSACTION();
}