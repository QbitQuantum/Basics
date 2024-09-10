void DatabasePool::_createPoolConnection() {

    Database *db = new Database;
    db->connect(_databaseHostname, _databaseUsername, _databasePassword, _databaseName);

    _countConnections++;

    // Verbindung zum Pool hinzufügen:
    _pool.append(db);
}