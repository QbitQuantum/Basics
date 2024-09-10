static int gf_load_font(DviParams *unused, DviFont *font)
{
    int    i;
    int    n;
    int    loc;
    int    hic;
    FILE    *p;
    Int32    word;
    int    op;
    long    alpha, beta, z;
#ifndef NODEBUG
    char    s[256];
#endif

    p = font->in;

    /* check preamble */
    loc = fuget1(p); hic = fuget1(p);
    if(loc != GF_PRE || hic != GF_ID)
        goto badgf;
    loc = fuget1(p);
#ifndef NODEBUG
    for(i = 0; i < loc; i++)
        s[i] = fuget1(p);
    s[i] = 0;
    DEBUG((DBG_FONTS, "(gf) %s: %s\n", font->fontname, s));
#else
    fseek(p, (long)loc, SEEK_CUR);
#endif
    /* now read character locators in postamble */
    if(fseek(p, (long)-1, SEEK_END) == -1)
        return -1;
    
    n = 0;
    while((op = fuget1(p)) == GF_TRAILER) {
        if(fseek(p, (long)-2, SEEK_CUR) < 0)
            break;
        n++;
    }
    if(op != GF_ID || n < 4)
        goto badgf;
    /* get the pointer to the postamble */
    fseek(p, (long)-5, SEEK_CUR);
    op = fuget4(p);
    /* jump to it */
    fseek(p, (long)op, SEEK_SET);
    if(fuget1(p) != GF_POST)
        goto badgf;
    /* skip pointer to last EOC */
    fuget4(p);
    /* get the design size */
    font->design = fuget4(p);
    /* the checksum */
    word = fuget4(p);
    if(word && font->checksum && font->checksum != word) {
        mdvi_warning(_("%s: bad checksum (expected %u, found %u)\n"),
                 font->fontname, font->checksum, word);
    } else if(!font->checksum)
        font->checksum = word;
    /* skip pixels per point ratio */
    fuget4(p);
    fuget4(p);
    font->chars = xnalloc(DviFontChar, 256);
    for(loc = 0; loc < 256; loc++)
        font->chars[loc].offset = 0;
    /* skip glyph "bounding box" */
    fseek(p, (long)16, SEEK_CUR);
    loc = 256;
    hic = -1;
    TFMPREPARE(font->scale, z, alpha, beta);
    while((op = fuget1(p)) != GF_POST_POST) {
        DviFontChar *ch;
        int    cc;

        /* get the character code */        
        cc = fuget1(p);
        if(cc < loc)
            loc = cc;
        if(cc > hic)
            hic = cc;
        ch = &font->chars[cc];
        switch(op) {
        case GF_LOC:
            fsget4(p); /* skip dx */
            fsget4(p); /* skip dy */
            break;
        case GF_LOC0:
            fuget1(p); /* skip dx */
                       /* dy assumed 0 */
            break;
        default:
            mdvi_error(_("%s: junk in postamble\n"), font->fontname);
            goto error;
        }
        ch->code = cc;
        ch->tfmwidth = fuget4(p);
        ch->tfmwidth = TFMSCALE(ch->tfmwidth, z, alpha, beta);
        ch->offset = fuget4(p);
        if(ch->offset == -1)
            ch->offset = 0;
        /* initialize the rest of the glyph information */
        ch->x = 0;
        ch->y = 0;
        ch->width = 0;
        ch->height = 0;
        ch->glyph.data = NULL;
        ch->shrunk.data = NULL;
        ch->grey.data = NULL;
        ch->flags = 0;
        ch->loaded = 0;
    }    

    if(op != GF_POST_POST)
        goto badgf;
    
    if(loc > 0 || hic < 255) {
        /* shrink to optimal size */
        memmove(font->chars, font->chars + loc,
            (hic - loc + 1) * sizeof(DviFontChar));
        font->chars = xresize(font->chars,
            DviFontChar, hic - loc + 1);
    }
    font->loc = loc;
    font->hic = hic;

    return 0;

badgf:
    mdvi_error(_("%s: File corrupted, or not a GF file\n"), font->fontname);
error:
    if(font->chars) {
        mdvi_free(font->chars);
        font->chars = NULL;
    }
    font->loc = font->hic = 0;
    return -1;
}