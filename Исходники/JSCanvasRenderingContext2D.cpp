JSValue* jsCanvasRenderingContext2DPrototypeFunctionFillRect(ExecState* exec, JSObject*, JSValue* thisValue, const ArgList& args)
{
    if (!thisValue->isObject(&JSCanvasRenderingContext2D::s_info))
        return throwError(exec, TypeError);
    JSCanvasRenderingContext2D* castedThisObj = static_cast<JSCanvasRenderingContext2D*>(thisValue);
    CanvasRenderingContext2D* imp = static_cast<CanvasRenderingContext2D*>(castedThisObj->impl());
    float x = args[0]->toFloat(exec);
    float y = args[1]->toFloat(exec);
    float width = args[2]->toFloat(exec);
    float height = args[3]->toFloat(exec);

    imp->fillRect(x, y, width, height);
    return jsUndefined();
}