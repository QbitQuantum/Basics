void IdentityInfo::removeMethod(const MethodName &method)
{
    QVariantMap methods = impl->fields["methods"].toMap();
    methods.remove(method);
    impl->fields["methods"] = methods;
}