QObject* CuteNews::createQmlObject(const QString &fileName) {
    initEngine();
    QDeclarativeContext *context = new QDeclarativeContext(m_engine->rootContext());
    QDeclarativeComponent *component = new QDeclarativeComponent(m_engine, fileName, this);
    
    if (QObject *obj = component->create(context)) {
        context->setParent(obj);
        return obj;
    }

    if (component->isError()) {
        foreach (const QDeclarativeError &error, component->errors()) {
            Logger::log("CuteNews::createQmlObject(). Error: " + error.toString());
        }        
    }