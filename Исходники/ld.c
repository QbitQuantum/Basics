void append_text_reloc(int segment, int offset, char *symbol)
{
    if (ntreloc >= treloc_max) {
        Reloc *p;

        treloc_max *= 2;
        if ((p=realloc(text_relocation_table, treloc_max*sizeof(Reloc))) == NULL)
            TERMINATE("out of memory");
        text_relocation_table = p;
    }
    text_relocation_table[ntreloc].segment = segment;
    text_relocation_table[ntreloc].offset = offset;
    text_relocation_table[ntreloc].symbol = symbol;
    ++ntreloc;
}