void JSHTMLScriptElement::putValueProperty(ExecState* exec, int token, JSValue* value, int /*attr*/)
{
    switch (token) {
    case TextAttrNum: {
        HTMLScriptElement* imp = static_cast<HTMLScriptElement*>(impl());

        imp->setText(valueToStringWithNullCheck(exec, value));
        break;
    }
    case HtmlForAttrNum: {
        HTMLScriptElement* imp = static_cast<HTMLScriptElement*>(impl());

        imp->setHtmlFor(valueToStringWithNullCheck(exec, value));
        break;
    }
    case EventAttrNum: {
        HTMLScriptElement* imp = static_cast<HTMLScriptElement*>(impl());

        imp->setEvent(valueToStringWithNullCheck(exec, value));
        break;
    }
    case CharsetAttrNum: {
        HTMLScriptElement* imp = static_cast<HTMLScriptElement*>(impl());

        imp->setCharset(valueToStringWithNullCheck(exec, value));
        break;
    }
    case DeferAttrNum: {
        HTMLScriptElement* imp = static_cast<HTMLScriptElement*>(impl());

        imp->setDefer(value->toBoolean(exec));
        break;
    }
    case SrcAttrNum: {
        HTMLScriptElement* imp = static_cast<HTMLScriptElement*>(impl());

        imp->setSrc(valueToStringWithNullCheck(exec, value));
        break;
    }
    case TypeAttrNum: {
        HTMLScriptElement* imp = static_cast<HTMLScriptElement*>(impl());

        imp->setType(valueToStringWithNullCheck(exec, value));
        break;
    }
    }
}