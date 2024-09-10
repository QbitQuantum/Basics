bool js_cocos2dx_extension_WebSocket_send(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    WebSocket* cobj = (WebSocket *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");

    if(argc == 1){
        do
        {
            if (args.get(0).isString())
            {
                std::string data;
                jsval_to_std_string(cx, args.get(0), &data);
                cobj->send(data);
                break;
            }

            if (args.get(0).isObject())
            {
                uint8_t *bufdata = NULL;
                uint32_t len = 0;
                
                JSObject* jsobj = args.get(0).toObjectOrNull();
                if (JS_IsArrayBufferObject(jsobj))
                {
                    bufdata = JS_GetArrayBufferData(jsobj);
                    len = JS_GetArrayBufferByteLength(jsobj);
                }
                else if (JS_IsArrayBufferViewObject(jsobj))
                {
                    bufdata = (uint8_t*)JS_GetArrayBufferViewData(jsobj);
                    len = JS_GetArrayBufferViewByteLength(jsobj);
                }
                
                if (bufdata && len > 0)
                {
                    cobj->send(bufdata, len);
                    break;
                }
            }
            
            JS_ReportError(cx, "data type to be sent is unsupported.");

        } while (0);
        
        args.rval().setUndefined();

        return true;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
    return true;
}