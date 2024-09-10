BattlePStorage::BattlePStorage(BattlePlugin *p)
{
    for (int i = 0; i < lastEnum; i++) {
        calls[i] = NULL;
    }

    QHash<QString, Hook> functions = p->getHooks();

    if (functions.contains("battleStarting(BattleInterface&)")) {
        calls[battleStarting] = functions.value("battleStarting(BattleInterface&)");

        functions.remove("battleStarting(BattleInterface&)");
    }

    if (functions.contains("emitCommand(BattleInterface&,int,int,QByteArray)")) {
        calls[emitCommand] = functions.value("emitCommand(BattleInterface&,int,int,QByteArray)");

        functions.remove("emitCommand(BattleInterface&,int,int,QByteArray)");
    }

    if (!functions.empty()) {
        /* To Do: Some way to propagate an error about unreckognized stuff, maybe cancel the plugin entirely */
    }

    plugin = p;
}