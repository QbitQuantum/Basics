int unpack(const wchar_t* path)
{
    FILE* fp = 0;
    _wfopen_s(&fp, path, L"rb");
    if (fp == 0)
    {
        wprintf_s(L"%s open fail\n", path);
        return 1;
    }
    fseek(fp, 0, SEEK_SET);

    YKCHDR hdr = { 0 };
    fread(&hdr, sizeof(YKCHDR), 1, fp);

    if (memcmp(hdr.signature, "YKC001", 6) != 0)
    {
        wprintf_s(L"%s format error\n", path);
        exit(1);
    }

    char* toc = new char[hdr.toc_length];
    fseek(fp, hdr.toc_offset, SEEK_SET);
    fread(toc, 1, hdr.toc_length, fp);

    YKCENTRY* table = (YKCENTRY*)toc;

    fs::path rawname = path;
    auto outdir = rawname.replace_extension();

    for (unsigned int i = 0; i != hdr.toc_length / sizeof(YKCENTRY); ++i)
    {
        char elefn[200];
        fseek(fp, table[i].filename_offset, SEEK_SET);
        fread(elefn, 1, table[i].filename_length, fp);

        auto outname = outdir;
        outname.append(elefn);

        char* buff = new char[table[i].data_length];
        fseek(fp, table[i].data_offset, SEEK_SET);
        fread(buff, 1, table[i].data_length, fp);

        if (memcmp(buff, "YKG000", 6) == 0)
        {
            write_pic(outname, buff, table[i].data_length);
        }
        else
        {
            write_file(outname, buff, table[i].data_length);
        }

        delete[] buff;
    }
    fclose(fp);
    delete[] toc;

    return 0;
}