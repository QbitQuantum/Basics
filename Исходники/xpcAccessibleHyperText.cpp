NS_IMETHODIMP
xpcAccessibleHyperText::GetDefaultTextAttributes(nsIPersistentProperties** aAttributes)
{
  NS_ENSURE_ARG_POINTER(aAttributes);
  *aAttributes = nullptr;

  if (mIntl.IsNull())
    return NS_ERROR_FAILURE;

  nsCOMPtr<nsIPersistentProperties> props;
  if (mIntl.IsAccessible()) {
    props = Intl()->DefaultTextAttributes();
  } else {
#if defined(XP_WIN)
    return NS_ERROR_NOT_IMPLEMENTED;
#else
    AutoTArray<Attribute, 10> attrs;
    mIntl.AsProxy()->DefaultTextAttributes(&attrs);
    uint32_t attrCount = attrs.Length();
    nsAutoString unused;
    for (uint32_t i = 0; i < attrCount; i++) {
      props->SetStringProperty(attrs[i].Name(), attrs[i].Value(), unused);
    }
#endif
  }
  props.forget(aAttributes);

  return NS_OK;
}