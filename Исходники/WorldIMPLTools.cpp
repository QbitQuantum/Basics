//function which updates the playerlist.
void World::updatePlayerList() {
    using namespace Database;

    PConnection connection = ConnectionManager::getInstance().getConnection();

    try {
        connection->beginTransaction();

        DeleteQuery delQuery(connection);
        delQuery.setServerTable("onlineplayer");
        delQuery.execute();

        if (!Players.empty()) {
            InsertQuery insQuery(connection);
            insQuery.setServerTable("onlineplayer");
            const InsertQuery::columnIndex column = insQuery.addColumn("on_playerid");

            Players.for_each([&](Player *player) {
                insQuery.addValue<TYPE_OF_CHARACTER_ID>(column, player->getId());
            });

            insQuery.execute();
        }

        connection->commitTransaction();
    } catch (std::exception &e) {
        Logger::error(LogFacility::World) << "Exception during saving online player list: " << e.what() << Log::end;
        connection->rollbackTransaction();
    }
}