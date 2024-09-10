JSValue* JSHTMLInputElement::getValueProperty(ExecState* exec, int token) const
{
    switch (token) {
    case DefaultValueAttrNum: {
        HTMLInputElement* imp = static_cast<HTMLInputElement*>(impl());

        return jsString(imp->defaultValue());
    }
    case DefaultCheckedAttrNum: {
        HTMLInputElement* imp = static_cast<HTMLInputElement*>(impl());

        return jsBoolean(imp->defaultChecked());
    }
    case FormAttrNum: {
        HTMLInputElement* imp = static_cast<HTMLInputElement*>(impl());

        return toJS(exec, WTF::getPtr(imp->form()));
    }
    case AcceptAttrNum: {
        HTMLInputElement* imp = static_cast<HTMLInputElement*>(impl());

        return jsString(imp->accept());
    }
    case AccessKeyAttrNum: {
        HTMLInputElement* imp = static_cast<HTMLInputElement*>(impl());

        return jsString(imp->accessKey());
    }
    case AlignAttrNum: {
        HTMLInputElement* imp = static_cast<HTMLInputElement*>(impl());

        return jsString(imp->align());
    }
    case AltAttrNum: {
        HTMLInputElement* imp = static_cast<HTMLInputElement*>(impl());

        return jsString(imp->alt());
    }
    case CheckedAttrNum: {
        HTMLInputElement* imp = static_cast<HTMLInputElement*>(impl());

        return jsBoolean(imp->checked());
    }
    case DisabledAttrNum: {
        HTMLInputElement* imp = static_cast<HTMLInputElement*>(impl());

        return jsBoolean(imp->disabled());
    }
    case MaxLengthAttrNum: {
        HTMLInputElement* imp = static_cast<HTMLInputElement*>(impl());

        return jsNumber(imp->maxLength());
    }
    case NameAttrNum: {
        HTMLInputElement* imp = static_cast<HTMLInputElement*>(impl());

        return jsString(imp->name());
    }
    case ReadOnlyAttrNum: {
        HTMLInputElement* imp = static_cast<HTMLInputElement*>(impl());

        return jsBoolean(imp->readOnly());
    }
    case SizeAttrNum: {
        HTMLInputElement* imp = static_cast<HTMLInputElement*>(impl());

        return jsNumber(imp->size());
    }
    case SrcAttrNum: {
        HTMLInputElement* imp = static_cast<HTMLInputElement*>(impl());

        return jsString(imp->src());
    }
    case TabIndexAttrNum: {
        HTMLInputElement* imp = static_cast<HTMLInputElement*>(impl());

        return jsNumber(imp->tabIndex());
    }
    case TypeAttrNum: {
        HTMLInputElement* imp = static_cast<HTMLInputElement*>(impl());

        return jsString(imp->type());
    }
    case UseMapAttrNum: {
        HTMLInputElement* imp = static_cast<HTMLInputElement*>(impl());

        return jsString(imp->useMap());
    }
    case ValueAttrNum: {
        HTMLInputElement* imp = static_cast<HTMLInputElement*>(impl());

        return jsString(imp->value());
    }
    case IndeterminateAttrNum: {
        HTMLInputElement* imp = static_cast<HTMLInputElement*>(impl());

        return jsBoolean(imp->indeterminate());
    }
    case ConstructorAttrNum:
        return getConstructor(exec);
    }
    return 0;
}