Local<Value> Geometry::getConstructor(OGRwkbGeometryType type) {
    Nan::EscapableHandleScope scope;

    type = wkbFlatten(type);
    switch (type) {
    case wkbPoint:
        return scope.Escape(Nan::New(Point::constructor)->GetFunction());
    case wkbLineString:
        return scope.Escape(Nan::New(LineString::constructor)->GetFunction());
    case wkbLinearRing:
        return scope.Escape(Nan::New(LinearRing::constructor)->GetFunction());
    case wkbPolygon:
        return scope.Escape(Nan::New(Polygon::constructor)->GetFunction());
    case wkbGeometryCollection:
        return scope.Escape(Nan::New(GeometryCollection::constructor)->GetFunction());
    case wkbMultiPoint:
        return scope.Escape(Nan::New(MultiPoint::constructor)->GetFunction());
    case wkbMultiLineString:
        return scope.Escape(Nan::New(MultiLineString::constructor)->GetFunction());
    case wkbMultiPolygon:
        return scope.Escape(Nan::New(MultiPolygon::constructor)->GetFunction());
    default:
        return scope.Escape(Nan::Null());
    }
}