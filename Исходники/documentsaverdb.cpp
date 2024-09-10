void DocumentSaverDB::saveDocumentPositions( KraftDoc *doc )
{
    DocPositionList posList = doc->positions();

    // invert all pos numbers to avoid a unique violation
    // FIXME: We need non-numeric ids
    QSqlQuery upq;
    QString queryStr = "UPDATE docposition SET ordNumber = -1 * ordNumber WHERE docID=";
    queryStr +=  doc->docID().toString();
    queryStr += " AND ordNumber > 0";
    upq.prepare( queryStr );
    upq.exec();

    int ordNumber = 1;

    QSqlTableModel model;
    model.setTable("docposition");
    model.setEditStrategy(QSqlTableModel::OnManualSubmit);

    QVector<int> deleteIds;

    DocPositionListIterator it( posList );
    while( it.hasNext() ) {
        DocPositionBase *dpb = it.next();

        DocPosition *dp = static_cast<DocPosition*>(dpb);
        QSqlRecord record ;
        bool doInsert = true;

        int posDbID = dp->dbId().toInt();
        kDebug() << "Saving Position DB-Id: " << posDbID << endl;

        if( dp->toDelete() ) {
            kDebug() << "Delete item " << dp->dbId().toString() << endl;

            // store the id to delete, rather than killing the model index.
            // did that before here, which removed wrong items.
            deleteIds << posDbID;

            // delete all existing attributes no, which will not disturb the model index
            dp->attributes().dbDeleteAll( dp->dbId() );
            continue;
        }

        if( posDbID > -1 ) {
            const QString selStr = QString("docID=%1 AND positionID=%2").arg( doc->docID().toInt() ).arg( posDbID );
            // kDebug() << "Selecting with " << selStr << endl;
            model.setFilter( selStr );
            model.select();
            if ( model.rowCount() > 0 ) {
                if( ! dp->toDelete() )
                    record = model.record(0);
                doInsert = false;
            } else {
                kError() << "ERR: Could not select document position record" << endl;
                return;
            }
        } else {
            // The record is new
            record = model.record();
        }

        if( record.count() > 0 ) {
            // kDebug() << "Updating position " << dp->position() << " is " << dp->text() << endl;
            QString typeStr = PosTypePosition;
            double price = dp->unitPrice().toDouble();

            if ( dp->type() == DocPositionBase::ExtraDiscount ) {
                typeStr = PosTypeExtraDiscount;
            }

            record.setValue( "docID",     QVariant(doc->docID().toInt()));
            record.setValue( "ordNumber", QVariant(ordNumber));
            record.setValue( "text",      QVariant(dp->text()));
            record.setValue( "postype",   QVariant(typeStr));
            record.setValue( "amount",    QVariant(dp->amount()));
            int unitId = dp->unit().id();
            record.setValue( "unit",      QVariant(unitId));
            record.setValue( "price",     QVariant(price));
            record.setValue( "taxType",   QVariant(dp->taxType()));

            ordNumber++; // FIXME

            if( doInsert ) {
                kDebug() << "Inserting!" << endl;
                model.insertRecord(-1, record);
                model.submitAll();
                dp->setDbId( KraftDB::self()->getLastInsertID().toInt() );
            } else {
                kDebug() << "Updating!" << endl;
                model.setRecord(0, record);
                model.submitAll();
            }
        } else {
            kDebug() << "ERR: No record object found!" << endl;
        }

        dp->attributes().save( dp->dbId() );

        QSqlError err = model.lastError();
        if( err.type() != QSqlError::NoError ) {
            kDebug() << "SQL-ERR: " << err.text() << " in " << model.tableName() << endl;
        }

    }
    model.submitAll();

    /*  remove the docpositions that were marked to be deleted */
    if( deleteIds.count() ) {
        QSqlQuery delQuery;
        delQuery.prepare( "DELETE FROM docposition WHERE positionID=:id" );
        foreach( int id, deleteIds ) {
            kDebug() << "Deleting attribute id " << id;
            delQuery.bindValue( ":id", id );
            delQuery.exec();
        }