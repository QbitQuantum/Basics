int Context2D::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: changed((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 1: save(); break;
        case 2: restore(); break;
        case 3: scale((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2]))); break;
        case 4: rotate((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 5: translate((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2]))); break;
        case 6: transform((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2])),(*reinterpret_cast< qreal(*)>(_a[3])),(*reinterpret_cast< qreal(*)>(_a[4])),(*reinterpret_cast< qreal(*)>(_a[5])),(*reinterpret_cast< qreal(*)>(_a[6]))); break;
        case 7: setTransform((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2])),(*reinterpret_cast< qreal(*)>(_a[3])),(*reinterpret_cast< qreal(*)>(_a[4])),(*reinterpret_cast< qreal(*)>(_a[5])),(*reinterpret_cast< qreal(*)>(_a[6]))); break;
        case 8: { CanvasGradient _r = createLinearGradient((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2])),(*reinterpret_cast< qreal(*)>(_a[3])),(*reinterpret_cast< qreal(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< CanvasGradient*>(_a[0]) = _r; }  break;
        case 9: { CanvasGradient _r = createRadialGradient((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2])),(*reinterpret_cast< qreal(*)>(_a[3])),(*reinterpret_cast< qreal(*)>(_a[4])),(*reinterpret_cast< qreal(*)>(_a[5])),(*reinterpret_cast< qreal(*)>(_a[6])));
            if (_a[0]) *reinterpret_cast< CanvasGradient*>(_a[0]) = _r; }  break;
        case 10: clearRect((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2])),(*reinterpret_cast< qreal(*)>(_a[3])),(*reinterpret_cast< qreal(*)>(_a[4]))); break;
        case 11: fillRect((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2])),(*reinterpret_cast< qreal(*)>(_a[3])),(*reinterpret_cast< qreal(*)>(_a[4]))); break;
        case 12: strokeRect((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2])),(*reinterpret_cast< qreal(*)>(_a[3])),(*reinterpret_cast< qreal(*)>(_a[4]))); break;
        case 13: beginPath(); break;
        case 14: closePath(); break;
        case 15: moveTo((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2]))); break;
        case 16: lineTo((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2]))); break;
        case 17: quadraticCurveTo((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2])),(*reinterpret_cast< qreal(*)>(_a[3])),(*reinterpret_cast< qreal(*)>(_a[4]))); break;
        case 18: bezierCurveTo((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2])),(*reinterpret_cast< qreal(*)>(_a[3])),(*reinterpret_cast< qreal(*)>(_a[4])),(*reinterpret_cast< qreal(*)>(_a[5])),(*reinterpret_cast< qreal(*)>(_a[6]))); break;
        case 19: arcTo((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2])),(*reinterpret_cast< qreal(*)>(_a[3])),(*reinterpret_cast< qreal(*)>(_a[4])),(*reinterpret_cast< qreal(*)>(_a[5]))); break;
        case 20: rect((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2])),(*reinterpret_cast< qreal(*)>(_a[3])),(*reinterpret_cast< qreal(*)>(_a[4]))); break;
        case 21: arc((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2])),(*reinterpret_cast< qreal(*)>(_a[3])),(*reinterpret_cast< qreal(*)>(_a[4])),(*reinterpret_cast< qreal(*)>(_a[5])),(*reinterpret_cast< bool(*)>(_a[6]))); break;
        case 22: fill(); break;
        case 23: stroke(); break;
        case 24: clip(); break;
        case 25: { bool _r = isPointInPath((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 26: drawImage((*reinterpret_cast< DomImage*(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2])),(*reinterpret_cast< qreal(*)>(_a[3]))); break;
        case 27: drawImage((*reinterpret_cast< DomImage*(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2])),(*reinterpret_cast< qreal(*)>(_a[3])),(*reinterpret_cast< qreal(*)>(_a[4])),(*reinterpret_cast< qreal(*)>(_a[5]))); break;
        case 28: drawImage((*reinterpret_cast< DomImage*(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2])),(*reinterpret_cast< qreal(*)>(_a[3])),(*reinterpret_cast< qreal(*)>(_a[4])),(*reinterpret_cast< qreal(*)>(_a[5])),(*reinterpret_cast< qreal(*)>(_a[6])),(*reinterpret_cast< qreal(*)>(_a[7])),(*reinterpret_cast< qreal(*)>(_a[8])),(*reinterpret_cast< qreal(*)>(_a[9]))); break;
        case 29: { ImageData _r = getImageData((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2])),(*reinterpret_cast< qreal(*)>(_a[3])),(*reinterpret_cast< qreal(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< ImageData*>(_a[0]) = _r; }  break;
        case 30: putImageData((*reinterpret_cast< ImageData(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2])),(*reinterpret_cast< qreal(*)>(_a[3]))); break;
        default: ;
        }
        _id -= 31;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< qreal*>(_v) = globalAlpha(); break;
        case 1: *reinterpret_cast< QString*>(_v) = globalCompositeOperation(); break;
        case 2: *reinterpret_cast< QVariant*>(_v) = strokeStyle(); break;
        case 3: *reinterpret_cast< QVariant*>(_v) = fillStyle(); break;
        case 4: *reinterpret_cast< qreal*>(_v) = lineWidth(); break;
        case 5: *reinterpret_cast< QString*>(_v) = lineCap(); break;
        case 6: *reinterpret_cast< QString*>(_v) = lineJoin(); break;
        case 7: *reinterpret_cast< qreal*>(_v) = miterLimit(); break;
        case 8: *reinterpret_cast< qreal*>(_v) = shadowOffsetX(); break;
        case 9: *reinterpret_cast< qreal*>(_v) = shadowOffsetY(); break;
        case 10: *reinterpret_cast< qreal*>(_v) = shadowBlur(); break;
        case 11: *reinterpret_cast< QString*>(_v) = shadowColor(); break;
        }
        _id -= 12;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setGlobalAlpha(*reinterpret_cast< qreal*>(_v)); break;
        case 1: setGlobalCompositeOperation(*reinterpret_cast< QString*>(_v)); break;
        case 2: setStrokeStyle(*reinterpret_cast< QVariant*>(_v)); break;
        case 3: setFillStyle(*reinterpret_cast< QVariant*>(_v)); break;
        case 4: setLineWidth(*reinterpret_cast< qreal*>(_v)); break;
        case 5: setLineCap(*reinterpret_cast< QString*>(_v)); break;
        case 6: setLineJoin(*reinterpret_cast< QString*>(_v)); break;
        case 7: setMiterLimit(*reinterpret_cast< qreal*>(_v)); break;
        case 8: setShadowOffsetX(*reinterpret_cast< qreal*>(_v)); break;
        case 9: setShadowOffsetY(*reinterpret_cast< qreal*>(_v)); break;
        case 10: setShadowBlur(*reinterpret_cast< qreal*>(_v)); break;
        case 11: setShadowColor(*reinterpret_cast< QString*>(_v)); break;
        }
        _id -= 12;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 12;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 12;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 12;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 12;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 12;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 12;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}