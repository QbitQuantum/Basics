BattleScripting::BattleScripting(QScriptEngine *engine, BaseBattleWindowInterface *_interface)
{
    myinterface = _interface;
    myengine = engine;
    myengine->setParent(this);
    setParent(_interface);

    registerObject(ProxyDataContainer);
    registerObject(TeamProxy);
    registerObject(PokeProxy);
    registerObject(MoveProxy);
    registerObject(AuxPokeDataProxy);
    registerObject(FieldProxy);
    qScriptRegisterMetaType<BattleChoice>(engine, &toBattleChoice, &fromBattleChoice);

    advbattledata_proxy *data = _interface->getBattleData();
    ProxyDataContainer *pdata = data->exposedData();
    int me = data->isPlayer(1) ? 1 : 0;
    int opp = !me;

    QScriptValue battle = myengine->newQObject(_interface);
    myengine->globalObject().setProperty("battle", battle);
    battle.setProperty("data", myengine->newQObject(dynamic_cast<QObject*>(pdata)));
    battle.setProperty("me", QScriptValue(me));
    battle.setProperty("opp", QScriptValue(opp));
    battle.setProperty("id", _interface->battleId());

    /* Removes clientscripting' print function and add ours. Client scripting's print function
      can still be accessed with sys.print() */
    QScriptValue printfun = myengine->newFunction(nativePrint);
    printfun.setData(myengine->newQObject(this));
    myengine->globalObject().setProperty("print", myengine->nullValue());
    myengine->globalObject().setProperty("print", printfun);

    _interface->addOutput(this);
}