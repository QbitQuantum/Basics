/* Open the given file, read & merge the colormap, convert the tiles. */
static void
process_file(char *fname)
{
    unsigned long count;

    if (!fopen_text_file(fname, RDTMODE)) {
        Fprintf(stderr, "can't open file \"%s\"\n", fname);
        exit(1);
    }
    merge_text_colormap();
    count = convert_tiles(&curr_tb, header.ntiles);
    Fprintf(stderr, "%s: %lu tiles\n", fname, count);
    header.ntiles += count;
    fclose_text_file();
}