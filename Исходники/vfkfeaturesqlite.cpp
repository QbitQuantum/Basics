/*!
  \brief Read FID from DB
*/
OGRErr VFKFeatureSQLite::SetFIDFromDB()
{
    CPLString   osSQL;
    
    osSQL.Printf("SELECT %s FROM %s WHERE rowid = %d",
                 FID_COLUMN, m_poDataBlock->GetName(), m_iRowId);
    if (ExecuteSQL(osSQL.c_str()) != OGRERR_NONE)
        return OGRERR_FAILURE;

    m_nFID = sqlite3_column_int(m_hStmt, 0);
  
    FinalizeSQL();
    
    return OGRERR_NONE;
}