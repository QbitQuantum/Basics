v8::Handle<v8::Value> V8CanvasRenderingContext2D::putImageDataCallback(const v8::Arguments& args)
{
    INC_STATS("DOM.CanvasRenderingContext2D.putImageData()");

    // Two froms:
    // * putImageData(ImageData, x, y)
    // * putImageData(ImageData, x, y, dirtyX, dirtyY, dirtyWidth, dirtyHeight)
    if (args.Length() != 3 && args.Length() != 7) {
        V8Proxy::setDOMException(SYNTAX_ERR);
        return notHandledByInterceptor();
    }

    CanvasRenderingContext2D* context = V8CanvasRenderingContext2D::toNative(args.Holder());

    ImageData* imageData = 0;

    // Need to check that the argument is of the correct type, since
    // toNative() expects it to be correct. If the argument was incorrect
    // we leave it null, and putImageData() will throw the correct exception
    // (TYPE_MISMATCH_ERR).
    if (V8DOMWrapper::isWrapperOfType(args[0], &V8ImageData::info))
        imageData = V8ImageData::toNative(v8::Handle<v8::Object>::Cast(args[0]));

    ExceptionCode ec = 0;

    if (args.Length() == 7)
        context->putImageData(imageData, toFloat(args[1]), toFloat(args[2]), toFloat(args[3]), toFloat(args[4]), toFloat(args[5]), toFloat(args[6]), ec);
    else
        context->putImageData(imageData, toFloat(args[1]), toFloat(args[2]), ec);

    if (ec != 0) {
        V8Proxy::setDOMException(ec);
        return notHandledByInterceptor();
    }

    return v8::Undefined();
}