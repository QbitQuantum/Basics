void GeometryFactory::New(const FunctionCallbackInfo<Value>& args) {
    GeometryFactory* factory;
    if (args.Length() == 0) {
        factory = new GeometryFactory();
    } else if (args.Length() == 1) {
        PrecisionModel* model = ObjectWrap::Unwrap<PrecisionModel>(args[0]->ToObject());
        factory = new GeometryFactory(model->_model);
    } else {
        PrecisionModel* model = ObjectWrap::Unwrap<PrecisionModel>(args[0]->ToObject());
        int newSRID = args[1]->IntegerValue();
        factory = new GeometryFactory(model->_model, newSRID);
    }
    factory->Wrap(args.This());
    args.GetReturnValue().Set(args.This());
}