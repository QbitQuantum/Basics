/*!
 * Modifies the detail definitions. The default detail definitions are
 * queried from QContactManagerEngine::schemaDefinitions and then modified
 * with this function in the transform leaf classes.
 *
 * \a definitions The detail definitions to modify.
 * \a contactType The contact type the definitions apply for.
 */
void CntTransformOnlineAccount::detailDefinitions(QMap<QString, QContactDetailDefinition> &definitions, const QString& contactType) const
{
    Q_UNUSED(contactType);

    if(definitions.contains(QContactOnlineAccount::DefinitionName)) {
        QContactDetailDefinition d = definitions.value(QContactOnlineAccount::DefinitionName);
        QMap<QString, QContactDetailFieldDefinition> fields = d.fields();
        QContactDetailFieldDefinition f;

        // Not all fields are supported
        fields.remove(QContactOnlineAccount::FieldCapabilities);
        fields.remove(QContactOnlineAccount::FieldDetailUri);
        fields.remove(QContactOnlineAccount::FieldLinkedDetailUris);
        fields.remove(QContactOnlineAccount::FieldServiceProvider);
        fields.remove(QContactOnlineAccount::FieldContext);

        // Support only certain subtypes 
        f.setDataType(QVariant::StringList);
        QVariantList subTypes;
        subTypes << QString(QLatin1String(QContactOnlineAccount::SubTypeSip));
        subTypes << QString(QLatin1String(QContactOnlineAccount::SubTypeSipVoip));
        subTypes << QString(QLatin1String(QContactOnlineAccount::SubTypeVideoShare));
        f.setAllowableValues(subTypes);
        fields[QContactOnlineAccount::FieldSubTypes] = f;

        d.setFields(fields);

        // Replace original definitions
        definitions.insert(d.name(), d);
    }
}