void ExternalDiffProc::removeFiles()
{
    if (!filenames.empty()) {
        QDir d; // remove temporary files to diff on
        d.remove(filenames[0]);
        d.remove(filenames[1]);
    }
}