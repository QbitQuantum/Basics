bool LongTimeEffect::save(uint32_t playerid, int32_t currentTime) {
    using namespace Database;
    PConnection connection = ConnectionManager::getInstance().getConnection();

    try {
        connection->beginTransaction();

        {
            InsertQuery insQuery(connection);
            insQuery.setServerTable("playerlteffects");
            const InsertQuery::columnIndex userColumn = insQuery.addColumn("plte_playerid");
            const InsertQuery::columnIndex effectColumn = insQuery.addColumn("plte_effectid");
            const InsertQuery::columnIndex nextCalledColumn = insQuery.addColumn("plte_nextcalled");
            const InsertQuery::columnIndex numberCalledColumn = insQuery.addColumn("plte_numbercalled");
            insQuery.addValue(userColumn, playerid);
            insQuery.addValue(effectColumn, effectId);
            insQuery.addValue(nextCalledColumn, executionTime - currentTime);
            insQuery.addValue(numberCalledColumn, numberOfCalls);
            insQuery.execute();
        }

        {
            InsertQuery insQuery(connection);
            insQuery.setServerTable("playerlteffectvalues");
            const InsertQuery::columnIndex userColumn = insQuery.addColumn("pev_playerid");
            const InsertQuery::columnIndex effectColumn = insQuery.addColumn("pev_effectid");
            const InsertQuery::columnIndex nameColumn = insQuery.addColumn("pev_name");
            const InsertQuery::columnIndex valueColumn = insQuery.addColumn("pev_value");

            for (const auto &value : values) {
                insQuery.addValue(nameColumn, value.first);
                insQuery.addValue(valueColumn, value.second);
                insQuery.addValue(userColumn, playerid);
                insQuery.addValue(effectColumn, effectId);
            }

            insQuery.execute();
        }

        connection->commitTransaction();
        return true;
    } catch (std::exception &e) {
        Logger::error(LogFacility::Other) << "Exception while saving long time effects: " << e.what() << Log::end;
        connection->rollbackTransaction();
        return false;
    }

    return true;
}