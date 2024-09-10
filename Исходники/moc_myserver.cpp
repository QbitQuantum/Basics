int MyServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updateTextBrowser((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: updateTextBrowserDlg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: addtoListWidget((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: deletefromListWidget((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: Service(); break;
        case 5: Accept(); break;
        case 6: DisplayError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 7: OnDisconnected(); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}