NS_IMETHODIMP
xpcAccessible::GetAttributes(nsIPersistentProperties** aAttributes)
{
  NS_ENSURE_ARG_POINTER(aAttributes);
  *aAttributes = nullptr;

  if (IntlGeneric().IsNull()) {
    return NS_ERROR_FAILURE;
  }

  if (Accessible* acc = Intl()) {
    nsCOMPtr<nsIPersistentProperties> attributes = acc->Attributes();
    attributes.swap(*aAttributes);
    return NS_OK;
  }

  ProxyAccessible* proxy = IntlGeneric().AsProxy();
  AutoTArray<Attribute, 10> attrs;
  proxy->Attributes(&attrs);

  nsCOMPtr<nsIPersistentProperties> props =
    do_CreateInstance(NS_PERSISTENTPROPERTIES_CONTRACTID);
  uint32_t attrCount = attrs.Length();
  nsAutoString unused;
  for (uint32_t i = 0; i < attrCount; i++) {
    props->SetStringProperty(attrs[i].Name(), attrs[i].Value(), unused);
  }

  props.forget(aAttributes);
  return NS_OK;
}