bool
nsDOMUIEvent::GetModifierStateInternal(const nsAString& aKey)
{
    WidgetInputEvent* inputEvent = mEvent->AsInputEvent();
    MOZ_ASSERT(inputEvent, "mEvent must be WidgetInputEvent or derived class");
    if (aKey.EqualsLiteral(NS_DOM_KEYNAME_SHIFT)) {
        return inputEvent->IsShift();
    }
    if (aKey.EqualsLiteral(NS_DOM_KEYNAME_CONTROL)) {
        return inputEvent->IsControl();
    }
    if (aKey.EqualsLiteral(NS_DOM_KEYNAME_META)) {
        return inputEvent->IsMeta();
    }
    if (aKey.EqualsLiteral(NS_DOM_KEYNAME_ALT)) {
        return inputEvent->IsAlt();
    }

    if (aKey.EqualsLiteral(NS_DOM_KEYNAME_ALTGRAPH)) {
        return inputEvent->IsAltGraph();
    }
    if (aKey.EqualsLiteral(NS_DOM_KEYNAME_OS)) {
        return inputEvent->IsOS();
    }

    if (aKey.EqualsLiteral(NS_DOM_KEYNAME_CAPSLOCK)) {
        return inputEvent->IsCapsLocked();
    }
    if (aKey.EqualsLiteral(NS_DOM_KEYNAME_NUMLOCK)) {
        return inputEvent->IsNumLocked();
    }

    if (aKey.EqualsLiteral(NS_DOM_KEYNAME_FN)) {
        return inputEvent->IsFn();
    }
    if (aKey.EqualsLiteral(NS_DOM_KEYNAME_SCROLLLOCK)) {
        return inputEvent->IsScrollLocked();
    }
    if (aKey.EqualsLiteral(NS_DOM_KEYNAME_SYMBOLLOCK)) {
        return inputEvent->IsSymbolLocked();
    }
    return false;
}