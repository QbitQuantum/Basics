int Plotter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: isRubberBandDragged((*reinterpret_cast< stWaveData*(*)>(_a[1]))); break;
        case 1: moveWindow((*reinterpret_cast< QRect(*)>(_a[1])),(*reinterpret_cast< PlotSettings(*)>(_a[2]))); break;
        case 2: zoomIn(); break;
        case 3: zommOut(); break;
        case 4: updateZoom((*reinterpret_cast< QRect(*)>(_a[1])),(*reinterpret_cast< PlotSettings(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}