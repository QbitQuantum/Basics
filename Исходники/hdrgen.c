void Module::genhdrfile()
{
    OutBuffer hdrbufr;

    hdrbufr.printf("// D import file generated from '%s'", srcfile->toChars());
    hdrbufr.writenl();

    HdrGenState hgs;
    memset(&hgs, 0, sizeof(hgs));
    hgs.hdrgen = 1;

    toCBuffer(&hdrbufr, &hgs);

    // Transfer image to file
    hdrfile->setbuffer(hdrbufr.data, hdrbufr.offset);
    hdrbufr.data = NULL;

    char *pt = FileName::path(hdrfile->toChars());
    if (*pt)
        FileName::ensurePathExists(pt);
    mem.free(pt);
    hdrfile->writev();
}