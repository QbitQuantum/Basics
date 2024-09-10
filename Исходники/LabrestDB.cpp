bool LabrestAPI::LabrestDB::lockResource(int resourceId, ::std::string username, int duration)
{
//    ::std::cout << "LabrestDB::lockResource()  called" << ::std::endl;
    
    bool status;
    
    int lock_st_id; 

    sqlite3_stmt *ppStmt;
    
    sqlite3_exec(db, "BEGIN", 0, 0, 0);
    
    if (ExistsResource(resourceId))
    {    
    if (ResourceIsNotLock(resourceId))
    {
        sqlite3_prepare(db,"insert into using_resource(username,resource_id, "
                "start_time, duration, end_time) "
               "values(?,?,datetime(), ?, ?);" ,-1,&ppStmt,0);
       
        sqlite3_bind_text(ppStmt,1,username.c_str(),username.length(),NULL);

        sqlite3_bind_int(ppStmt, 2, resourceId);
        
        if (duration == -1) sqlite3_bind_null(ppStmt,3);
            else sqlite3_bind_int(ppStmt, 3, duration);
        
        sqlite3_bind_null(ppStmt,4);
        
        if (sqlite3_step(ppStmt) == SQLITE_DONE)
        {
            status = true;
        }
        else
        {
            status = false;
        }
        sqlite3_finalize(ppStmt);
    
        if (status)
         
            {
                sqlite3_prepare(db,"update resource set lock_status = "
                        "(select id from using_resource where "
                     "resource_id = ? and end_time isnull)"
                        " where id = ?;" ,-1,&ppStmt,0);
                
                sqlite3_bind_int(ppStmt, 1, resourceId);
                
                sqlite3_bind_int(ppStmt, 2, resourceId);
                
                if (sqlite3_step(ppStmt) == SQLITE_DONE)
                {
                    status = true;
                }
                else
                {
                    status = false;
                }
                sqlite3_finalize(ppStmt);
                
                sqlite3_prepare(db,"select id from resource where parent = ?;" ,-1,&ppStmt,0);
                                
                sqlite3_bind_int(ppStmt, 1, resourceId);
                
                while (sqlite3_step(ppStmt) == SQLITE_ROW)
                {
                    lockResource(sqlite3_column_int(ppStmt,0), username, duration);
                }
                sqlite3_finalize(ppStmt);          
        }
        
        Event ev;
    
        ev.TypeEvent = CB_LOCK;
        ev.id = EvQueuePtr->next_id;
        ev.resourceId = resourceId;
        ev.userDest = "";
        ev.userSrc = username;
    
        EvQueuePtr->push_back(ev);
        
        sqlite3_exec(db, "COMMIT", 0, 0, 0);
    }
    else
    {
        sqlite3_exec(db, "COMMIT", 0, 0, 0);
        
        ::LabrestAPI::ResourceIsLock rl;
        
        rl.ice_throw();
    }
    }
    else
    {
        sqlite3_exec(db, "COMMIT", 0, 0, 0);
        
        ::LabrestAPI::InvalidValue iv;
        
        iv.ice_throw();
    }
    
    return status;
}