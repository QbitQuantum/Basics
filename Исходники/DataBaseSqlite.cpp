DB_Error DataBaseSqlite::AddUser(shared_ptr<User> user)
{
    DB_Error ret = CreateTable("User");
    if (ret == DB_OK)
    {
        EntryList entries = m_pTableComponent->GetTableFormat("User");
        PDEBUG ("entry size: %lu\n", entries.size());
        if (!entries.empty())
        {
            string sql(INSERT_TABLE);
            sql += string("User") + VALUE + LPARENT;
            EntryList::iterator iter = entries.begin();
            EntryList::iterator end  = entries.end();
            for (; iter != end;)
            {
                sql += "@" + iter->name;
                if (++iter != end)
                {
                    sql += ", ";
                }
            }
            sql += string(RPARENT) + SEMI;

            SqliteCommand cmd(this, sql);

            // Ugly hard code!!
            PDEBUG ("Begin binding\n");
            ret = cmd.Bind("@name", user->name());
            ret = ret ? ret : cmd.Bind("@uuid", user->uuid());
            int64 date = 0;
            if (user->has_reg_date())
            {
                ret = user->reg_date();
            }
            ret = ret ? ret : cmd.Bind("@reg_date", date);

            date = 0;

            if (user->has_last_login())
            {
                date = user->last_login();
            }
            ret = ret ? ret : cmd.Bind("@last_login", date);
            // Bind others ...
            ret = ret ? ret : cmd.Execute();
            // Execute ....
        }
    }
    return ret;
}