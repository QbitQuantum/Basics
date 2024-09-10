static void xsltTransform(const char* xml, const char* sheet, IProperties *params, StringBuffer& ret)
{
    if(!checkFileExists(sheet))
        throw MakeStringException(-1, "Could not find stylesheet %s.",sheet);
    Owned<IXslProcessor> proc = getXslProcessor();
    Owned<IXslTransform> trans = proc->createXslTransform();
    trans->setXmlSource(xml, strlen(xml));
    trans->loadXslFromFile(sheet);
    trans->copyParameters(params);
    trans->transform(ret);
}