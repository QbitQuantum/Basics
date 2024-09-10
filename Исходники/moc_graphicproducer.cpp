int GraphicProducer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: strikePath((*reinterpret_cast< const VectorPath(*)>(_a[1])),(*reinterpret_cast< const GraphicContext(*)>(_a[2]))); break;
        case 1: fillPath((*reinterpret_cast< const VectorPath(*)>(_a[1])),(*reinterpret_cast< const GraphicContext(*)>(_a[2])),(*reinterpret_cast< Qt::FillRule(*)>(_a[3]))); break;
        case 2: parsingDone((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: { bool _r = parseStream((*reinterpret_cast< const char*(*)>(_a[1])),(*reinterpret_cast< ulong(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: { bool _r = parsePDF((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}