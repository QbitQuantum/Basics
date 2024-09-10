int Client::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: newMessage((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: newParticipant((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: participantLeft((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: newConnection((*reinterpret_cast< Connection*(*)>(_a[1]))); break;
        case 4: connectionError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 5: disconnected(); break;
        case 6: readyForUse(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}