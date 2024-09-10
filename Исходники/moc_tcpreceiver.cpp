int TCPReceiver::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: stringRead((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: connectionError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: connectionReady(); break;
        case 3: connectionNotReady(); break;
        case 4: newConnection(); break;
        case 5: endConnection(); break;
        case 6: clientWriteString((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 7: { QByteArray _r = clientReadString();
            if (_a[0]) *reinterpret_cast< QByteArray*>(_a[0]) = _r; }  break;
        case 8: stop(); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}