void HyperBusReciever::destroyStaticHyperBus(const QString &key)
{
    HyperBusReciever *res = static_hyperbus_objs.value(key);
    if(!res)
        return;

    static_hyperbus_objs.remove(key);
    delete res;
}