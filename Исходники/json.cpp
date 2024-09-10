static JSBool
JO(JSContext *cx, Value *vp, StringifyContext *scx)
{
    JSObject *obj = &vp->toObject();

    CycleDetector detect(scx, obj);
    if (!detect.init(cx))
        return JS_FALSE;

    if (!scx->sb.append('{'))
        return JS_FALSE;

    Value vec[3] = { NullValue(), NullValue(), NullValue() };
    AutoArrayRooter tvr(cx, JS_ARRAY_LENGTH(vec), vec);
    Value& outputValue = vec[0];
    Value& whitelistElement = vec[1];
    AutoIdRooter idr(cx);
    jsid& id = *idr.addr();

    Value *keySource = vp;
    bool usingWhitelist = false;

    // if the replacer is an array, we use the keys from it
    if (scx->replacer && JS_IsArrayObject(cx, scx->replacer)) {
        usingWhitelist = true;
        vec[2].setObject(*scx->replacer);
        keySource = &vec[2];
    }

    JSBool memberWritten = JS_FALSE;
    AutoIdVector props(cx);
    if (!GetPropertyNames(cx, &keySource->toObject(), JSITER_OWNONLY, &props))
        return JS_FALSE;

    for (size_t i = 0, len = props.length(); i < len; i++) {
        outputValue.setUndefined();

        if (!usingWhitelist) {
            if (!js_ValueToStringId(cx, IdToValue(props[i]), &id))
                return JS_FALSE;
        } else {
            // skip non-index properties
            jsuint index = 0;
            if (!js_IdIsIndex(props[i], &index))
                continue;

            if (!scx->replacer->getProperty(cx, props[i], &whitelistElement))
                return JS_FALSE;

            if (!js_ValueToStringId(cx, whitelistElement, &id))
                return JS_FALSE;
        }

        // We should have a string id by this point. Either from 
        // JS_Enumerate's id array, or by converting an element
        // of the whitelist.
        JS_ASSERT(JSID_IS_ATOM(id));

        if (!JS_GetPropertyById(cx, obj, id, Jsvalify(&outputValue)))
            return JS_FALSE;

        if (outputValue.isObjectOrNull() && !js_TryJSON(cx, &outputValue))
            return JS_FALSE;

        // call this here, so we don't write out keys if the replacer function
        // wants to elide the value.
        if (!CallReplacerFunction(cx, id, obj, scx, &outputValue))
            return JS_FALSE;

        JSType type = JS_TypeOfValue(cx, Jsvalify(outputValue));

        // elide undefined values and functions and XML
        if (outputValue.isUndefined() || type == JSTYPE_FUNCTION || type == JSTYPE_XML)
            continue;

        // output a comma unless this is the first member to write
        if (memberWritten && !scx->sb.append(','))
            return JS_FALSE;
        memberWritten = JS_TRUE;

        if (!WriteIndent(cx, scx, scx->depth))
            return JS_FALSE;

        // Be careful below, this string is weakly rooted
        JSString *s = js_ValueToString(cx, IdToValue(id));
        if (!s)
            return JS_FALSE;

        JS::Anchor<JSString *> anchor(s);
        size_t length = s->length();
        const jschar *chars = s->getChars(cx);
        if (!chars)
            return JS_FALSE;

        if (!write_string(cx, scx->sb, chars, length) ||
            !scx->sb.append(':') ||
            !(scx->gap.empty() || scx->sb.append(' ')) ||
            !Str(cx, id, obj, scx, &outputValue, true)) {
            return JS_FALSE;
        }
    }

    if (memberWritten && !WriteIndent(cx, scx, scx->depth - 1))
        return JS_FALSE;

    return scx->sb.append('}');
}