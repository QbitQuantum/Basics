/*
    Documented in qv8engine.cpp
*/
v8::Handle<v8::Value> QV8Include::include(const v8::Arguments &args)
{
    if (args.Length() == 0)
        return v8::Undefined();

    QV8Engine *engine = V8ENGINE();
    QDeclarativeContextData *context = engine->callingContext();

    if (!context || !context->isJSContext) 
        V8THROW_ERROR("Qt.include(): Can only be called from JavaScript files");

    QUrl url(context->resolvedUrl(QUrl(engine->toString(args[0]->ToString()))));
    
    v8::Local<v8::Function> callbackFunction;
    if (args.Length() >= 2 && args[1]->IsFunction())
        callbackFunction = v8::Local<v8::Function>::Cast(args[1]);

    QString localFile = QDeclarativeEnginePrivate::urlToLocalFileOrQrc(url);

    v8::Local<v8::Object> result;

    if (localFile.isEmpty()) {

        QV8Include *i = new QV8Include(url, engine, context, 
                                       v8::Context::GetCallingQmlGlobal(), 
                                       callbackFunction);
        result = v8::Local<v8::Object>::New(i->result());

    } else { 

        QFile f(localFile);

        if (f.open(QIODevice::ReadOnly)) {
            QByteArray data = f.readAll();
            QString code = QString::fromUtf8(data);
            QDeclarativeScriptParser::extractPragmas(code);

            QDeclarativeContextData *importContext = new QDeclarativeContextData;
            importContext->isInternal = true;
            importContext->isJSContext = true;
            importContext->url = url;
            importContext->setParent(context, true);

            v8::TryCatch try_catch;

            v8::Local<v8::Script> script = engine->qmlModeCompile(code, url.toString());

            if (!try_catch.HasCaught()) {
                v8::Local<v8::Object> qmlglobal = v8::Context::GetCallingQmlGlobal();
                engine->contextWrapper()->addSubContext(qmlglobal, script, importContext);
                script->Run(qmlglobal);
            }

            if (try_catch.HasCaught()) {
                result = resultValue(Exception);
                result->Set(v8::String::New("exception"), try_catch.Exception());
            } else {
                result = resultValue(Ok);
            }

        } else {
            result = resultValue(NetworkError);
        }

        callback(engine, callbackFunction, result);
    }

    if (result.IsEmpty())
        return v8::Undefined();
    else 
        return result;
}