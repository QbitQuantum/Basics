void rho_syncclient_save( const char* szModel, unsigned long hash )
{
    Hashtable<String, String>& hashObject = *((Hashtable<String, String>*)hash);
    String src_name = szModel;

    DBResult( res, db::CDBAdapter::getUserDB().executeSQL("SELECT source_id, partition, schema, sync_type from sources WHERE name=?", src_name) );
    if ( res.isEnd())
    {
        //TODO: report error - unknown source
        return;
    }

    int nSrcID = res.getIntByIdx(0);
    String obj = hashObject.get("object");

    String db_partition = res.getStringByIdx(1);
    bool isSchemaSrc = res.getStringByIdx(2).length() > 0;
    bool isSyncSrc = res.getStringByIdx(3).compare("none") != 0;
    String tableName = isSchemaSrc ? src_name : "object_values";
    db::CDBAdapter& db = db::CDBAdapter::getDB(db_partition.c_str());

    db.startTransaction();

    String update_type = "";
    String sql;
    Vector<String> arValues;
    if (isSchemaSrc)
    {
        sql = "SELECT object FROM " + tableName + " WHERE object=? LIMIT 1 OFFSET 0";
        arValues.addElement(obj);
    }
    else
    {
        sql = "SELECT object FROM " + tableName + " WHERE object=? AND source_id=? LIMIT 1 OFFSET 0";
        arValues.addElement(obj);
        arValues.addElement(convertToStringA(nSrcID));
    }
    DBResult( res1, db.executeSQLEx(sql.c_str(), arValues ) );
    if (!res1.isEnd())
    {
        if (isSyncSrc)
        {
            DBResult( resUpdateType, db.executeSQL( "SELECT update_type FROM changed_values WHERE object=? and source_id=? and sent=?", 
                obj, nSrcID, 0 ) );
            if (!resUpdateType.isEnd()) 
                update_type = resUpdateType.getStringByIdx(0);
            else
	            update_type = "update";
        }else
            update_type = "update";
    }
    else
    {
        rho_syncclient_create_object(szModel, hash);
    }

    if (!res.isEnd())
    {
        unsigned long item = rhom_load_item_by_object( db, src_name, nSrcID, obj, isSchemaSrc);
        Hashtable<String, String>& hashItem = *((Hashtable<String, String>*)item);

        for ( Hashtable<String,String>::iterator it = hashObject.begin();  it != hashObject.end(); ++it )
        {
            String key = it->first;
            String val  = it->second;

            if ( rhom_method_name_isreserved(key) )
                continue;

            // add rows excluding object, source_id and update_type
            Hashtable<String,String> fields;
            fields.put("source_id", convertToStringA(nSrcID));
            fields.put("object", obj);
            fields.put("attrib", key);
            fields.put("value", val);
            fields.put("update_type", update_type);
            if ( db::CDBAdapter::getDB(db_partition.c_str()).getAttrMgr().isBlobAttr(nSrcID, key.c_str()) )
                fields.put( "attrib_type", "blob.file");

            if ( hashItem.containsKey(key) )
            {
                bool isModified = hashItem.get(key) != val;
                if (isModified)
                {
                    if (isSyncSrc)
                    {
                        DBResult( resUpdateType, db.executeSQL( "SELECT update_type FROM changed_values WHERE object=? and attrib=? and source_id=? and sent=?", 
                            obj, key, nSrcID, 0 ) );
                        if (!resUpdateType.isEnd()) 
                        {
                            fields.put("update_type", resUpdateType.getStringByIdx(0) );
                            db.executeSQL( "DELETE FROM changed_values WHERE object=? and attrib=? and source_id=? and sent=?", 
                                obj, key, nSrcID, 0 );
                        }

                        db_insert_into_table(db, "changed_values", fields);
                    }
                        
                    if ( isSchemaSrc )
                        db.executeSQL( (String("UPDATE ") + tableName + " SET " + key + "=? WHERE object=?").c_str(), val, obj );
                    else
                        db.executeSQL( "UPDATE object_values SET value=? WHERE object=? and attrib=? and source_id=?", val, obj, key, nSrcID );
                }

            }else
            {
                if (isSyncSrc)
                    db_insert_into_table(db, "changed_values", fields);

                fields.remove("update_type");
                fields.remove("attrib_type");
                
                if (isSchemaSrc)
                    db.executeSQL( (String("UPDATE ") + tableName + " SET " + key + "=? WHERE object=?").c_str(), val, obj );
                else
                    db_insert_into_table(db, tableName, fields);
            }
        }
    }

    db.endTransaction();
}