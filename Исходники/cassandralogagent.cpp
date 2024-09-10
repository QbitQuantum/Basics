void CCassandraLogAgent::ensureTransSeedTable()
{
    //Create transaction seed table as needed
    StringBuffer transSeedTableKeys;
    StringArray transSeedTableColumnNames, transSeedTableColumnTypes;
    transSeedTableColumnNames.append("id");
    transSeedTableColumnTypes.append("int");
    transSeedTableColumnNames.append("application");
    transSeedTableColumnTypes.append("varchar");
    transSeedTableKeys.set("application"); //primary keys

    //The defaultDB has transactions table.
    setSessionOptions(defaultDB.str());
    cassSession->connect();
    createTable(defaultDB.str(), transactionTable.str(), transSeedTableColumnNames, transSeedTableColumnTypes, transSeedTableKeys.str());

    unsigned id = 0;
    VStringBuffer st("SELECT id FROM %s LIMIT 1;", transactionTable.str());
    if (!executeSimpleSelectStatement(st.str(), id))
    {
        st.setf("INSERT INTO %s (id, application) values ( 10000, '%s');",
                transactionTable.str(), loggingTransactionApp.get());
        executeSimpleStatement(st.str());

        if (!strieq(defaultTransactionApp.get(), loggingTransactionApp.get()))
        {
            st.setf("INSERT INTO %s (id, application) values ( 10000, '%s');",
                    transactionTable.str(), defaultTransactionApp.get());
            executeSimpleStatement(st.str());
        }
    }
    cassSession->disconnect();
}