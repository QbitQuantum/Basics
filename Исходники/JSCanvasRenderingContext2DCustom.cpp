void JSCanvasRenderingContext2D::setWebkitLineDash(ExecState* exec, JSValue value)
{
    if (!isJSArray(value))
        return;

    Vector<float> dash;
    JSArray* valueArray = asArray(value);
    for (unsigned i = 0; i < valueArray->length(); ++i) {
        float elem = valueArray->getIndex(exec, i).toFloat(exec);
        if (elem <= 0 || !std::isfinite(elem))
            return;

        dash.append(elem);
    }

    CanvasRenderingContext2D* context = static_cast<CanvasRenderingContext2D*>(impl());
    context->setWebkitLineDash(dash);
}