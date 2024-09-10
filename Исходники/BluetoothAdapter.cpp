void
BluetoothAdapter::DispatchAttributeEvent(const Sequence<nsString>& aTypes)
{
  NS_ENSURE_TRUE_VOID(aTypes.Length());

  BluetoothAttributeEventInit init;
  init.mAttrs = aTypes;

  nsRefPtr<BluetoothAttributeEvent> event =
    BluetoothAttributeEvent::Constructor(
      this, NS_LITERAL_STRING(ATTRIBUTE_CHANGED_ID), init);

  DispatchTrustedEvent(event);
}