/* zsync_configure_zstream_for_zdata(self, &z_stream_s, zoffset, &outoffset)
 * Rewrites the state in the given zlib stream object to be ready to decompress
 * data from the compressed version of this zsync stream at the given offset in
 * the compressed file. Returns the offset in the uncompressed stream that this
 * corresponds to in the 4th parameter. 
 */
void zsync_configure_zstream_for_zdata(const struct zsync_state *zs,
                                       struct z_stream_s *zstrm,
                                       long zoffset, long long *poutoffset) {
    configure_zstream_for_zdata(zs->zmap, zstrm, zoffset, poutoffset);
    {                           /* Load in prev 32k sliding window for backreferences */
        long long pos = *poutoffset;
        int lookback = (pos > 32768) ? 32768 : pos;

        /* Read in 32k of leading uncompressed context - needed because the deflate
         * compression method includes back-references to previously-seen strings. */
        unsigned char wbuf[32768];
        rcksum_read_known_data(zs->rs, wbuf, pos - lookback, lookback);

        /* Fake an output buffer of 32k filled with data to zlib */
        zstrm->next_out = wbuf + lookback;
        zstrm->avail_out = 0;
        updatewindow(zstrm, lookback);
    }
}