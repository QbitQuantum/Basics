void ResourceManifest::addToArchive(IPropertyTree *archive)
{
    IPropertyTree *additionalFiles = ensurePTree(archive, "AdditionalFiles");

    //xsi namespace required for proper representaion after PTree::setPropBin()
    if (!additionalFiles->hasProp("@xmlns:xsi"))
        additionalFiles->setProp("@xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");

    Owned<IPropertyTreeIterator> resources = manifest->getElements("Resource[@resourcePath]");
    ForEach(*resources)
    {
        IPropertyTree &item = resources->query();
        const char *respath = item.queryProp("@resourcePath");

        VStringBuffer xpath("Resource[@resourcePath='%s']", respath);
        if (!additionalFiles->hasProp(xpath.str()))
        {
            IPropertyTree *resTree = additionalFiles->addPropTree("Resource", createPTree("Resource"));

            const char *filepath = item.queryProp("@originalFilename");
            resTree->setProp("@originalFilename", filepath);
            resTree->setProp("@resourcePath", respath);

            MemoryBuffer content;
            loadResource(filepath, content);
            resTree->setPropBin(NULL, content.length(), content.toByteArray());
        }
    }

    StringBuffer xml;
    toXML(manifest, xml);

    IPropertyTree *manifest = additionalFiles->addPropTree("Manifest", createPTree("Manifest", ipt_none));
    manifest->setProp("@originalFilename", absFilename.str());
    manifest->setProp(NULL, xml.str());
}