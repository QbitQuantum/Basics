void DocumentationPlugin::reload()
{
    clear();
    for (QValueList<DocumentationCatalogItem *>::iterator it = catalogs.begin();
        it != catalogs.end(); ++it)
    {
        createTOC(*it);
    }
}