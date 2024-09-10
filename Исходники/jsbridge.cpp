void jsBridge::removeTmpFile()
{
    if (files.isEmpty())
        return;
    QFile *tmpf = files.dequeue();
    tmpf->remove();
    delete tmpf;
}