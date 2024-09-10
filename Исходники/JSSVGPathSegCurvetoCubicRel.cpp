JSValue jsSVGPathSegCurvetoCubicRelY1(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSSVGPathSegCurvetoCubicRel* castedThis = static_cast<JSSVGPathSegCurvetoCubicRel*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    SVGPathSegCurvetoCubicRel* imp = static_cast<SVGPathSegCurvetoCubicRel*>(castedThis->impl());
    JSValue result = jsNumber(imp->y1());
    return result;
}