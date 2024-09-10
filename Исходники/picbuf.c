static void
swapin_RowBuf (RowBuf *row, const PicBuf *picbuf)
{
    if (fseek (picbuf->sd, (long) row->index*picbuf->nb*picbuf->depth, SEEK_SET))
    {
        PError	("swapin_RowBuf (on seek)");
        exit	(ERROR);
    }

    if (fread ((char *) row->buf, picbuf->nb, picbuf->depth, picbuf->sd)
            != picbuf->depth)
    {
        PError	("swapin_RowBuf (on read)");
        exit	(ERROR);
    }
}