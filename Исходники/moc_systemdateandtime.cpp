int ONVIF::SystemDateAndTime::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< DateTimeType*>(_v) = dateTimeType(); break;
        case 1: *reinterpret_cast< bool*>(_v) = daylightSavings(); break;
        case 2: *reinterpret_cast< QString*>(_v) = tz(); break;
        case 3: *reinterpret_cast< QDateTime*>(_v) = utcTime(); break;
        case 4: *reinterpret_cast< QDateTime*>(_v) = localTime(); break;
        case 5: *reinterpret_cast< bool*>(_v) = result(); break;
        default: break;
        }
        _id -= 6;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setDateTimeType(*reinterpret_cast< DateTimeType*>(_v)); break;
        case 1: setDaylightSavings(*reinterpret_cast< bool*>(_v)); break;
        case 2: setTz(*reinterpret_cast< QString*>(_v)); break;
        case 3: setutcTime(*reinterpret_cast< QDateTime*>(_v)); break;
        case 4: setlocalTime(*reinterpret_cast< QDateTime*>(_v)); break;
        case 5: setResult(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
        _id -= 6;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 6;
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}