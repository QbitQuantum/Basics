/* Write 3 byte bed header */
static int write_bed_header(FILE *bed)
{
    short m;
    size_t count;
    swab(&magic_no, &m, 2);
    count = fwrite(&m, sizeof(short), 1, bed);
    count += fwrite(&mode, sizeof(char), 1, bed);
    return count;
}