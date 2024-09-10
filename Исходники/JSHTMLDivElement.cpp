JSValue* JSHTMLDivElement::getValueProperty(ExecState* exec, int token) const
{
    switch (token) {
    case AlignAttrNum: {
        HTMLDivElement* imp = static_cast<HTMLDivElement*>(impl());
        return jsString(exec, imp->align());
    }
    case ConstructorAttrNum:
        return getConstructor(exec);
    }
    return 0;
}