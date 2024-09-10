void qsKillTimers( QSEnv *env )
{
    QuickInterpreter *ip = QuickInterpreter::fromEnv(env);

    QHash<int, QSObject> *timers = ip->timers();
    for (QHash<int, QSObject>::ConstIterator it = timers->begin(); it != timers->end(); ++it) {
        ip->killTimer(it.key());
    }
    timers->clear();
}