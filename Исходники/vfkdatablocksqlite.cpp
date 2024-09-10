/*!
  \brief Update VFK_DB_TABLE table

  \param nGeometries number of geometries to update
*/
void VFKDataBlockSQLite::UpdateVfkBlocks(int nGeometries) {
    CPLString osSQL;

    VFKReaderSQLite *poReader = (VFKReaderSQLite*) m_poReader;

    /* update number of features in VFK_DB_TABLE table */
    const int nFeatCount = (int)GetFeatureCount();
    if (nFeatCount > 0) {
        osSQL.Printf("UPDATE %s SET num_features = %d WHERE table_name = '%s'",
                     VFK_DB_TABLE, nFeatCount, m_pszName);
        poReader->ExecuteSQL(osSQL.c_str());
    }

    /* update number of geometries in VFK_DB_TABLE table */
    if (nGeometries > 0) {
        CPLDebug("OGR-VFK",
                 "VFKDataBlockSQLite::UpdateVfkBlocks(): name=%s -> "
                 "%d geometries saved to internal DB", m_pszName, nGeometries);

        osSQL.Printf("UPDATE %s SET num_geometries = %d WHERE table_name = '%s'",
                     VFK_DB_TABLE, nGeometries, m_pszName);
        poReader->ExecuteSQL(osSQL.c_str());
    }
}