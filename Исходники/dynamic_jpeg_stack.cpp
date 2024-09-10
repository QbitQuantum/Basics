Handle<Value>
DynamicJpegStack::New(const Arguments &args)
{
    HandleScope scope;

    if (args.Length() > 1)
        return VException("One argument max - buffer type.");

    buffer_type buf_type = BUF_RGB;
    if (args.Length() == 1) {
        if (!args[0]->IsString())
            return VException("First argument must be a string. Either 'rgb', 'bgr', 'rgba' or 'bgra'.");

        String::AsciiValue bt(args[0]->ToString());
        if (!(str_eq(*bt, "rgb") || str_eq(*bt, "bgr") ||
                str_eq(*bt, "rgba") || str_eq(*bt, "bgra")))
        {
            return VException("Buffer type must be 'rgb', 'bgr', 'rgba' or 'bgra'.");
        }

        if (str_eq(*bt, "rgb"))
            buf_type = BUF_RGB;
        else if (str_eq(*bt, "bgr"))
            buf_type = BUF_BGR;
        else if (str_eq(*bt, "rgba"))
            buf_type = BUF_RGBA;
        else if (str_eq(*bt, "bgra"))
            buf_type = BUF_BGRA;
        else
            return VException("Buffer type wasn't 'rgb', 'bgr', 'rgba' or 'bgra'.");
    }

    DynamicJpegStack *jpeg = new DynamicJpegStack(buf_type);
    jpeg->Wrap(args.This());
    return args.This();
}