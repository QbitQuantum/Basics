uint32_t
nsMenuBarListener::GetModifiers(nsIDOMKeyEvent* aKeyEvent)
{
  uint32_t modifiers = 0;
  WidgetInputEvent* inputEvent =
    static_cast<WidgetInputEvent*>(aKeyEvent->GetInternalNSEvent());
  MOZ_ASSERT(inputEvent);

  if (inputEvent->IsShift()) {
    modifiers |= MODIFIER_SHIFT;
  }

  if (inputEvent->IsControl()) {
    modifiers |= MODIFIER_CONTROL;
  }

  if (inputEvent->IsAlt()) {
    modifiers |= MODIFIER_ALT;
  }

  if (inputEvent->IsMeta()) {
    modifiers |= MODIFIER_META;
  }

  if (inputEvent->IsOS()) {
    modifiers |= MODIFIER_OS;
  }

  return modifiers;
}