    uint64 psMysqlConnection::GenericInsertWithID(const char *table,const char **fieldnames,psStringArray& fieldvalues)
    {
        csString command;
        const size_t count = fieldvalues.GetSize();
        uint i;
        command = "INSERT INTO ";
        command.Append(table);
        command.Append(" (");
        for (i=0;i<count;i++)
        {
            if (i>0)
                command.Append(",");
            command.Append(fieldnames[i]);
        }

        command.Append(") VALUES (");
        for (i=0;i<count;i++)
        {
            if (i>0)
                command.Append(",");
            if (fieldvalues[i]!=NULL)
            {
                command.Append("'");
                csString escape;
                Escape( escape, fieldvalues[i] );
                command.Append(escape);
                command.Append("'");
            }
            else
            {
                command.Append("NULL");
            }
        }
        command.Append(")");

        if (Command("%s", command.GetDataSafe())!=1)
            return 0;

        return GetLastInsertID();
    }