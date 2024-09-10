v8::Local<v8::Value> Geometry::_toJSONSync(Nan::NAN_METHOD_ARGS_TYPE info) {
    Nan::EscapableHandleScope scope;
    Geometry* g = Nan::ObjectWrap::Unwrap<Geometry>(info.Holder());
    std::string json;
    if (info.Length() < 1)
    {
        if (!mapnik::util::to_geojson(json,g->feat_->get_geometry()))
        {
            // Fairly certain this situation can never be reached but
            // leaving it none the less
            /* LCOV_EXCL_START */
            Nan::ThrowError("Failed to generate GeoJSON");
            return scope.Escape(Nan::Undefined());
            /* LCOV_EXCL_STOP */
        }
    }
    else
    {
        if (!info[0]->IsObject()) {
            Nan::ThrowTypeError("optional first arg must be an options object");
            return scope.Escape(Nan::Undefined());
        }
        v8::Local<v8::Object> options = info[0]->ToObject();
        if (options->Has(Nan::New("transform").ToLocalChecked()))
        {
            v8::Local<v8::Value> bound_opt = options->Get(Nan::New("transform").ToLocalChecked());
            if (!bound_opt->IsObject()) {
                Nan::ThrowTypeError("'transform' must be an object");
                return scope.Escape(Nan::Undefined());
            }

            v8::Local<v8::Object> obj = bound_opt->ToObject();
            if (obj->IsNull() || obj->IsUndefined() || !Nan::New(ProjTransform::constructor)->HasInstance(obj)) {
                Nan::ThrowTypeError("mapnik.ProjTransform expected as first arg");
                return scope.Escape(Nan::Undefined());
            }
            ProjTransform* tr = Nan::ObjectWrap::Unwrap<ProjTransform>(obj);
            mapnik::proj_transform const& prj_trans = *tr->get();
            mapnik::geometry::geometry<double> const& geom = g->feat_->get_geometry();
            if (!to_geojson_projected(json,geom,prj_trans))
            {
                // Fairly certain this situation can never be reached but
                // leaving it none the less
                /* LCOV_EXCL_START */
                Nan::ThrowError("Failed to generate GeoJSON");
                return scope.Escape(Nan::Undefined());
                /* LCOV_EXCL_STOP */
            }
        }
    }
    return scope.Escape(Nan::New<v8::String>(json).ToLocalChecked());
}