FT_Stream FreeTypeWrapper::CreateFTStreamForPath(const std::string& inFilePath)
{
    InputFile* inputFile = new InputFile;

    if(inputFile->OpenFile(inFilePath) != PDFHummus::eSuccess)
        return NULL;

    FT_Stream aStream = new FT_StreamRec();

    aStream->base = NULL;
    aStream->size = (unsigned long)inputFile->GetFileSize();
    aStream->pos = 0;
    aStream->descriptor.pointer = inputFile;
    aStream->pathname.pointer = NULL;
    aStream->read = InputFileReadSeek;
    aStream->close = InputFileClose;
    aStream->memory = NULL;
    aStream->cursor = NULL;
    aStream->limit = NULL;

    return aStream;
}