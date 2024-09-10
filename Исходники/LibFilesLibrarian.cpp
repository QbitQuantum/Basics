void LibFiles::WriteFiles(FILE *stream, ObjInt align)
{
    int i =0;
    for (FileIterator it = FileBegin(); it != FileEnd(); ++it)
    {
        Align(stream, align);
        (*it)->offset = ftell(stream);
        WriteData(stream, (*it)->data, (*it)->name);
    }
}