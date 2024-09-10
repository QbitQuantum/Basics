// wahbm compressed in place
//{{{ uint32_t wah_compressed_in_place_or(uint32_t *r_wah,
uint32_t wah_compressed_in_place_or(uint32_t *r_wah,
                                    uint32_t r_wah_size,
                                    uint32_t *wah,
                                    uint32_t wah_size)
{
    uint32_t wah_i, wah_v, wah_fill_size, wah_fill_value,
             r_wah_i, r_wah_v, r_wah_fill_size, r_wah_fill_value,
             end, num_words;

    r_wah_i = 0;


    for (wah_i = 0; wah_i < wah_size; ++wah_i)
    {
        wah_v = wah[wah_i];
        r_wah_v = r_wah[r_wah_i];

        if (wah_v == 0x80000000)
            abort();
        if (r_wah_v == 0x80000000)
            abort();

        if (wah_v >= 0x80000000) { // wah_v is a fill

            wah_fill_value = (wah_v >> 30) & 1;
            wah_fill_size = (wah_v & 0x3fffffff);

            while (wah_fill_size > 0) {

                if (r_wah_v >= 0x80000000) { // r_wah is a fill

                    /*
                    fprintf(stderr, "%u:%s\t%u:%s\n",
                            wah_i,int_to_binary(wah_v),
                            r_wah_i,int_to_binary(r_wah_v));
                    */

                    r_wah_fill_value = (r_wah_v >> 30) & 1;
                    r_wah_fill_size = (r_wah_v & 0x3fffffff);

                    // make a new fill based on the smaller one
                    num_words = MIN(wah_fill_size, r_wah_fill_size);

                    if (num_words > 1) {
                        r_wah[r_wah_i] = (1 << 31) +
                                         ((r_wah_fill_value |
                                           wah_fill_value) << 30) +
                                         num_words;
                    } else {
                        if ((r_wah_fill_value | wah_fill_value) == 1)
                            r_wah[r_wah_i] = 0x7fffffff;
                        else
                            r_wah[r_wah_i] = 0;
                    }

                    r_wah_fill_size -= num_words;
                    wah_fill_size -= num_words;

                    // save any values left on the end of r_wah run
                    if (r_wah_fill_size > 0) {
                        if (r_wah_fill_size == 1) {
                            // we no longer have a fill, write a literal
                            if (r_wah_fill_value == 1) { //all ones
                                r_wah[r_wah_i + num_words] = 0x7fffffff;
                                //fprintf(stderr,"2\n");
                            } else {  // all zeros
                                r_wah[r_wah_i + num_words] = 0;
                                //fprintf(stderr,"3\n");
                            }
                        } else {
                            // we still have a fill, write it
                            r_wah[r_wah_i + num_words] =
                                (1 << 31) +
                                (r_wah_fill_value << 30) +
                                r_wah_fill_size;
                            //fprintf(stderr,"4\n");
                        }
                    }

                    r_wah_i += num_words;
                } else { // r_wah is a literal
                    if (wah_fill_value == 1)
                        r_wah[r_wah_i] = 0x7fffffff;
                    r_wah_i += 1;
                    wah_fill_size -= 1;
                }

                if (r_wah_i < r_wah_size)
                    r_wah_v = r_wah[r_wah_i];

                if (r_wah_v == 0x80000000)
                    abort();
            }