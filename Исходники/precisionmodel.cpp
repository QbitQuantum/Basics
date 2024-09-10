void PrecisionModel::New(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    PrecisionModel *model;
    if (args.Length() == 0) {
        model = new PrecisionModel();
    } else {
        if (args[0]->IsString()) {
            //type
            if(args[0]->ToString()->Equals(String::NewFromUtf8(isolate, "FIXED"))) {
                model = new PrecisionModel(geos::geom::PrecisionModel::FIXED);
            } else if (args[0]->ToString()->Equals(String::NewFromUtf8(isolate, "FLOATING"))) {
                model = new PrecisionModel(geos::geom::PrecisionModel::FLOATING);
            } else {
                model = new PrecisionModel(geos::geom::PrecisionModel::FLOATING_SINGLE);
            }
        } else {
            //double
            model = new PrecisionModel(args[0]->NumberValue());
        }
    }
    model->Wrap(args.This());
    args.GetReturnValue().Set(args.This());
}