Local<Value> MultiPolygon::New(OGRMultiPolygon *geom, bool owned)
{
	Nan::EscapableHandleScope scope;

	if (!geom) {
		return scope.Escape(Nan::Null());
	}

	//make a copy of geometry owned by a feature
	// + no need to track when a feature is destroyed
	// + no need to throw errors when a method trys to modify an owned read-only geometry
	// - is slower

	if (!owned) {
		geom = static_cast<OGRMultiPolygon*>(geom->clone());
	};

	MultiPolygon *wrapped = new MultiPolygon(geom);
	wrapped->owned_ = true;

	UPDATE_AMOUNT_OF_GEOMETRY_MEMORY(wrapped);

	Local<Value> ext = Nan::New<External>(wrapped);
	Local<Object> obj = Nan::New(MultiPolygon::constructor)->GetFunction()->NewInstance(1, &ext);

	return scope.Escape(obj);
}