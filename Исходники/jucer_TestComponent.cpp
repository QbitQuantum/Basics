void TestComponent::setFilename (const String& newName)
{
    File newFile;

    if (newName.isNotEmpty())
    {
        if (ownerDocument != nullptr)
            newFile = ownerDocument->getCppFile().getSiblingFile (newName);
        else
            newFile = File::getCurrentWorkingDirectory().getChildFile (newName);
    }

    if (! recursiveFiles.contains (newFile.getFullPathName()))
    {
        recursiveFiles.add (newFile.getFullPathName());

        loadedDocument = nullptr;

        filename = newName;
        lastModificationTime = findFile().getLastModificationTime();

        loadedDocument = JucerDocument::createForCppFile (nullptr, findFile());

        updateContents();
        repaint();

        recursiveFiles.remove (recursiveFiles.size() - 1);
    }
}