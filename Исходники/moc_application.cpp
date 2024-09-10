int Application::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: update((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: setToZero(); break;
        case 2: onExit(); break;
        case 3: Tick(); break;
        case 4: Screen(); break;
        case 5: Hide(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}