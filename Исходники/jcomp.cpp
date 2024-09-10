void CppCompiler::writeLogFile(const char* filepath, StringBuffer& log)
{
    if(!filepath || !*filepath || !log.length())
        return;

    Owned <IFile> f = createIFile(filepath);
    if(f->exists())
        f->remove();

    Owned <IFileIO> fio = f->open(IFOcreaterw);
    if(fio.get())
        fio->write(0, log.length(), log.str());
}