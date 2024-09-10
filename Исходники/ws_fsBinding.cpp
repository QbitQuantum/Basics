void CFileSpraySoapBindingEx::xsltTransform(const char* xml, const char* sheet, IProperties *params, StringBuffer& ret)
{
    StringBuffer xsl;
    if (!checkFileExists(sheet))
        throw MakeStringException(ECLWATCH_FILE_NOT_EXIST, "Cannot open stylesheet %s",sheet);

    Owned<IXslProcessor> proc  = getXslProcessor();
    Owned<IXslTransform> trans = proc->createXslTransform();

    trans->setXmlSource(xml, strlen(xml));
    trans->loadXslFromFile(sheet);

    if (params)
    {
        Owned<IPropertyIterator> it = params->getIterator();
        for (it->first(); it->isValid(); it->next())
        {
            const char *key = it->getPropKey();
            //set parameter in the XSL transform skipping over the @ prefix, if any
            const char* paramName = *key == '@' ? key+1 : key;
            trans->setParameter(paramName, StringBuffer().append('\'').append(params->queryProp(key)).append('\'').str());
        }
    }

    trans->transform(ret);
}