const StringBuffer &CEspApplicationPort::getNavBarContent(IEspContext &context, StringBuffer &content, StringBuffer &contentType, bool rawxml)
{
    if (xslp)
    {
        Owned<IPropertyTree> navtree=createPTree("EspNavigationData");
        {
            ReadLockBlock rblock(rwLock);
            int count = getBindingCount();
            for (int idx = 0; idx<count; idx++)
                bindings[idx]->queryBinding()->getNavigationData(context, *navtree.get());
        }

        StringBuffer xml;
        buildNavTreeXML(navtree.get(), xml);
        if (rawxml)
        {
            content.swapWith(xml);
            contentType.clear().append(HTTP_TYPE_APPLICATION_XML_UTF8);
        }
        else
        {
            const char* viewType = navtree->queryProp("@viewType");

            Owned<IXslTransform> xform = xslp->createXslTransform();

            StringBuffer xslsource;
            if (viewType && *viewType)
            {
                xslsource.append(getCFD()).appendf("./xslt/%s.xsl", stricmp(viewType, "tree") != 0 ? viewType: "navigation");
            }
            else
            {
                xslsource.append(getCFD()).append("./xslt/nav.xsl");

            }
            xform->loadXslFromFile(xslsource.str());


            xform->setXmlSource(xml.str(), xml.length()+1);
            xform->transform(content);
            contentType.clear().append("text/html; charset=UTF-8");
        }
    }
    return content;
}