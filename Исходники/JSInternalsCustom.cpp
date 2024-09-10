void JSInternals::setUserPreferredLanguages(ExecState* exec, JSValue value)
{
    if (!isJSArray(value)) {
        throwError(exec, createSyntaxError(exec, "setUserPreferredLanguages: Expected Array"));
        return;
    }
    
    Vector<String> languages;
    JSArray* array = asArray(value);
    for (unsigned i = 0; i < array->length(); ++i) {
        String language = ustringToString(array->getIndex(i).toString(exec)->value(exec));
        languages.append(language);
    }
    
    Internals* imp = static_cast<Internals*>(impl());
    imp->setUserPreferredLanguages(languages);
}