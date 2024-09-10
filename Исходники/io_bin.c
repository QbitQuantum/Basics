/*@T
 *
 * The header data consists of a count of the number of balls (a 32-bit
 * integer) and a scale parameter (a 32-bit floating point number).
 * The scale parameter tells the viewer how big the view box is supposed
 * to be in the coordinate system of the simulation; right now, it is
 * always set to be 1 (i.e. the view box is $[0,1] \times [0,1]$)
 *@c*/
void write_header(FILE* fp, int n)
{
    float scale = 1.0;
    uint32_t nn = htonl((uint32_t) n);
    uint32_t nscale = htonf(&scale);
    fprintf(fp, "%s\n", VERSION_TAG);
    fwrite(&nn,     sizeof(nn),     1, fp);
    fwrite(&nscale, sizeof(nscale), 1, fp);
}