already_AddRefed<nsIPersistentProperties>
ProxyAccessibleWrap::Attributes()
{
  RefPtr<nsPersistentProperties> attributes = new nsPersistentProperties();
  nsAutoString unused;
  AutoTArray<Attribute, 10> attrs;
  Proxy()->Attributes(&attrs);
  for (size_t i = 0; i < attrs.Length(); i++) {
    attributes->SetStringProperty(
      attrs.ElementAt(i).Name(), attrs.ElementAt(i).Value(), unused);
  }

  return attributes.forget();
}