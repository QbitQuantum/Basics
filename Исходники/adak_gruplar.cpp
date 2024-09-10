void GRP_KAYDI_GRUPLARA_EKLE ( int program_id , int module_id ,int record_id , QList<int> * grup_idleri )
{
    QString gruplar_str = "";

    SQL_QUERY query    ( DB );

    if (grup_idleri->size() NE 0) {
        for ( int i = 0 ; i < grup_idleri->size() ; i++ ) {
            gruplar_str.append("\t");
            gruplar_str.append(QVariant(grup_idleri->at(i)).toString());
            gruplar_str.append("\t");
        }
    }

    query.PREPARE_SELECT ( "adak_kaydin_gruplari","id,gruplar","record_id = :record_id AND module_id = :module_id AND program_id = :program_id" ,"");

    query.SET_VALUE ( ":record_id" , record_id  );
    query.SET_VALUE ( ":module_id" , module_id  );
    query.SET_VALUE ( ":program_id", program_id );

    if ( query.SELECT() NE 0 ) {
        query.NEXT();
        int id              = query.VALUE(0).toInt();
        QStringList gruplar = query.VALUE(1).toString().split("\t",QString::SkipEmptyParts);

        query.PREPARE_UPDATE("adak_kaydin_gruplari","id","gruplar","id = :id");
        query.SET_VALUE(":gruplar" ,QVariant(gruplar_str).toByteArray());
        query.SET_VALUE(":id",id);
        query.UPDATE();

        for ( int i = 0 ; i < grup_idleri->size() ; i++ ) {
            if (gruplar.contains(QVariant(grup_idleri->at(i)).toString()) EQ true) {
                gruplar.removeAt(i);
                continue;
            }
            query.PREPARE_SELECT("adak_gruplar","gruptaki_kayit_sayisi","grup_id=:grup_id","");
            query.SET_VALUE(":grup_id",grup_idleri->at(i));
            if ( query.SELECT() EQ 0 ) {
                return;
            }
            query.NEXT();

            int value = query.VALUE(0).toInt();

            query.PREPARE_UPDATE("adak_gruplar","grup_id","gruptaki_kayit_sayisi","grup_id=:grup_id");
            query.SET_VALUE(":gruptaki_kayit_sayisi",(value+1));
            query.SET_VALUE(":grup_id",grup_idleri->at(i));
            query.UPDATE();
        }

        for ( int i = 0 ; i < gruplar.size() ; i++ ) {
            if (gruplar.at(i).toInt() NE 0 ) {
                query.PREPARE_SELECT("adak_gruplar","gruptaki_kayit_sayisi","grup_id=:grup_id","");
                query.SET_VALUE(":grup_id",gruplar.at(i));
                if ( query.SELECT() EQ 0 ) {
                    return;
                }
                query.NEXT();

                int value = query.VALUE(0).toInt();

                query.PREPARE_UPDATE("adak_gruplar","grup_id","gruptaki_kayit_sayisi","grup_id=:grup_id AND gruptaki_kayit_sayisi > 0 ");
                query.SET_VALUE(":gruptaki_kayit_sayisi",(value - 1));
                query.SET_VALUE(":grup_id",gruplar.at(i));
                query.UPDATE();
            }
        }

        return;
    }

    query.PREPARE_INSERT("adak_kaydin_gruplari","id", "record_id,gruplar,module_id,program_id ");

    query.SET_VALUE(":record_id", record_id    );
    query.SET_VALUE(":gruplar",   QVariant(gruplar_str).toByteArray() );
    query.SET_VALUE(":module_id", module_id    );
    query.SET_VALUE(":program_id",program_id   );

    query.INSERT();

    for ( int i = 0 ; i < grup_idleri->size() ; i++ ) {
        query.PREPARE_SELECT("adak_gruplar","gruptaki_kayit_sayisi","grup_id=:grup_id","");
        query.SET_VALUE(":grup_id",grup_idleri->at(i));
        if ( query.SELECT() EQ 0 ) {
            return;
        }
        query.NEXT();

        int value = query.VALUE(0).toInt();

        query.PREPARE_UPDATE("adak_gruplar","grup_id","gruptaki_kayit_sayisi","grup_id=:grup_id");
        query.SET_VALUE(":gruptaki_kayit_sayisi",(value+1));
        query.SET_VALUE(":grup_id",grup_idleri->at(i));
        query.UPDATE();;
    }
}