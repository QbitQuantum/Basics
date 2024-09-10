void IrcChannelPrivate::changeModes(const QString& value, const QStringList& arguments)
{
    Q_Q(IrcChannel);
    const IrcNetwork* network = q->network();

    QMap<QString, QString> ms = modes;
    QStringList args = arguments;

    bool add = true;
    for (int i = 0; i < value.size(); ++i) {
        const QString m = value.at(i);
        if (m == QLatin1String("+")) {
            add = true;
        } else if (m == QLatin1String("-")) {
            add = false;
        } else {
            if (add) {
                QString a;
                if (!args.isEmpty() && network && network->channelModes(IrcNetwork::TypeB | IrcNetwork::TypeC).contains(m))
                    a = args.takeFirst();
                ms.insert(m, a);
            } else {
                ms.remove(m);
            }
        }
    }

    if (modes != ms) {
        setKey(ms.value(QLatin1String("k")));
        modes = ms;
        emit q->modeChanged(q->mode());
    }
}