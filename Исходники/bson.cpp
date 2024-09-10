void
encodeArray(bson_buffer *bb, const char *name, const Local<Value> element) {
    Local<Array> a = Array::Cast(*element);
    bson_buffer *arr = bson_append_start_array(bb, name);

    for (int i = 0, l=a->Length(); i < l; i++) {
        Local<Value> val = a->Get(Number::New(i));
        stringstream keybuf;
        string keyval;
        keybuf << i << endl;
        keybuf >> keyval;

        if (val->IsString()) {
            encodeString(arr, keyval.c_str(), val);
        }
        else if (val->IsInt32()) {
            encodeInteger(arr, keyval.c_str(), val);
        }
        else if (val->IsNumber()) {
            encodeNumber(arr, keyval.c_str(), val);
        }
        else if (val->IsBoolean()) {
            encodeBoolean(arr, keyval.c_str(), val);
        }
        else if (val->IsArray()) {
            encodeArray(arr, keyval.c_str(), val);
        }
        else if (val->IsObject()) {
            bson bson(encodeObject(val));
            bson_append_bson(arr, keyval.c_str(), &bson);
            bson_destroy(&bson);
        }
    }
    bson_append_finish_object(arr);
}