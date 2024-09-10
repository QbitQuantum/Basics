int myclianttest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: readyRead(); break;
        case 1: bytesWritten((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 2: disconnected(); break;
        case 3: list((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: connected(); break;
        case 5: test(); break;
        case 6: mycomputer((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 8: doubleClickedServer((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 9: setpath((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: getpath(); break;
        case 11: servercomputer((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 12: serverfiledown((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 13: getserverpath(); break;
        case 14: download(); break;
        case 15: Serverclicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 16: gotomotherpath(); break;
        case 17: gotoservermotherpath(); break;
        default: ;
        }
        _id -= 18;
    }
    return _id;
}