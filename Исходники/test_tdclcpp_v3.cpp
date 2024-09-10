    fixtureStore() : m_db(NULL)
    {
        nsdatabase::setCheckTablePtr(true);
        bool db_created = g_db_created;

        m_db = database::create();
        if (!m_db)
            printf("Error database::create()\n");
        short ret = createTestDataBase(m_db);
        if (ret)
        {    
            printf("Error createDataBase\n");
            return;
        }
        if (!db_created)
            ret = createTestTable(m_db);
        else
        {
             m_db->open(makeUri(PROTOCOL, HOSTNAME, DBNAMEV3, BDFNAME), TYPE_SCHEMA_BDF,TD_OPEN_NORMAL);
             ret = m_db->stat();
        }
        if (ret)
            printf("Error createTable\n");
    }