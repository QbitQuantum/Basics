bool StPlayList::saveM3U(const StCString& thePath) {
    StRawFile aFile;
    if(thePath.isEmpty()
    || !aFile.openFile(StRawFile::WRITE, thePath)) {
        return false;
    }

    StMutexAuto anAutoLock(myMutex);
    aFile.write(stCString("#EXTM3U"));

    for(StPlayItem* anItem = myFirst; anItem != NULL; anItem = anItem->getNext()) {
        const StFileNode* aNode = anItem->getFileNode();
        if(aNode == NULL) {
            continue;
        } else if(aNode->size() < 2) {
            aFile.write(stCString("\n#EXTINF:0,"));
            if(anItem->hasCustomTitle()) {
                aFile.write(anItem->getTitle());
            }
            aFile.write(stCString("\n"));
            aFile.write(aNode->getPath());
        }
    }
    aFile.write(stCString("\n"));
    return true;
}