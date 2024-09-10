static bool readzipdirectory(const char *archname, FILE *f, int entries, int offset, uint size, vector<zipfile> &files)
{
    uchar *buf = new uchar[size], *src = buf;
    if(fseek(f, offset, SEEK_SET) < 0 || fread(buf, 1, size, f) != size) { delete[] buf; return false; }
    loopi(entries)
    {
        if(src + ZIP_FILE_SIZE > &buf[size]) break;

        zipfileheader hdr;
        hdr.signature = lilswap(*(uint *)src); src += 4;
        hdr.version = lilswap(*(ushort *)src); src += 2;
        hdr.needversion = lilswap(*(ushort *)src); src += 2;
        hdr.flags = lilswap(*(ushort *)src); src += 2;
        hdr.compression = lilswap(*(ushort *)src); src += 2;
        hdr.modtime = lilswap(*(ushort *)src); src += 2;
        hdr.moddate = lilswap(*(ushort *)src); src += 2;
        hdr.crc32 = lilswap(*(uint *)src); src += 4;
        hdr.compressedsize = lilswap(*(uint *)src); src += 4;
        hdr.uncompressedsize = lilswap(*(uint *)src); src += 4;
        hdr.namelength = lilswap(*(ushort *)src); src += 2;
        hdr.extralength = lilswap(*(ushort *)src); src += 2;
        hdr.commentlength = lilswap(*(ushort *)src); src += 2;
        hdr.disknumber = lilswap(*(ushort *)src); src += 2;
        hdr.internalattribs = lilswap(*(ushort *)src); src += 2;
        hdr.externalattribs = lilswap(*(uint *)src); src += 4;
        hdr.offset = lilswap(*(uint *)src); src += 4;
        if(hdr.signature != ZIP_FILE_SIGNATURE) break;
        if(!hdr.namelength || !hdr.uncompressedsize || (hdr.compression && (hdr.compression != Z_DEFLATED || !hdr.compressedsize)))
        {
            src += hdr.namelength + hdr.extralength + hdr.commentlength;
            continue;
        }
        if(src + hdr.namelength > &buf[size]) break;

        string pname;
        int namelen = min((int)hdr.namelength, (int)sizeof(pname)-1);
        memcpy(pname, src, namelen);
        pname[namelen] = '\0';
        path(pname);
        char *name = newstring(pname);

        zipfile &f = files.add();
        f.name = name;
        f.header = hdr.offset;
        f.size = hdr.uncompressedsize;
        f.compressedsize = hdr.compression ? hdr.compressedsize : 0;
#ifndef STANDALONE
        if(dbgzip) conoutf(CON_DEBUG, "%s: file %s, size %d, compress %d, flags %x", archname, name, hdr.uncompressedsize, hdr.compression, hdr.flags);
#endif

        src += hdr.namelength + hdr.extralength + hdr.commentlength;
    }
    delete[] buf;

    return files.length() > 0;
}