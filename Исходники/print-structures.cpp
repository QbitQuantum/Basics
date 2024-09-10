int print_console_ring(FILE * o, const PageTable & pt,
                       const vaddr_t & ring, const uint64_t & _length,
                       const uint64_t & producer, const uint64_t & consumer)
{
    int len = 0;
    int64_t prod = producer, cons = consumer, length = _length;
    ssize_t written;

    if ( _length > SSIZE_MAX )
        return len + FPRINTF(o, "Length(%"PRIu64") exceeds SSIZE_MAX(%zd)\n",
                             _length, (ssize_t)SSIZE_MAX);

    if ( (length & (length-1)) == 0 )
    {
        prod &= (length-1);
        cons &= (length-1);
    }

    if ( prod > length )
        return len + FPRINTF(o, "Producer index %"PRIu64" outside ring length %"PRIu64"\n",
                             prod, length);

    if ( cons > length )
        return len + FPRINTF(o, "Consumer index %"PRIu64" outside ring length %"PRIu64"\n",
                             cons, length);

    len += FPUTS("\n", o);

    try
    {
        if ( cons == 0 && prod == 0 )
        {
            LOG_DEBUG("Console ring: %"PRIu64" bytes at 0x%016"PRIx64"\n", length, ring);
            written = memory.write_block_vaddr_to_file(pt, ring, o, length);
            len += written;

            if ( written != length )
                LOG_INFO("Mismatch writing console ring to file. Written %zu bytes "
                         "of %"PRIu64"\n", written, length);
        }
        else
        {
            LOG_DEBUG("Console ring: %"PRIu64" bytes at 0x%016"PRIx64", prod %"PRId64", cons %"PRId64"\n",
                      length, ring, prod, cons);
            if ( cons >= prod )
            {
                written = memory.write_block_vaddr_to_file(pt, ring + cons,
                                                           o, length - cons);
                len += written;

                if ( (length - cons) != written )
                {
                    LOG_INFO("Mismatch writing console ring to file. Written %zu bytes "
                             "of %"PRIu64"\n", written, length - cons);
                }
                else
                {

                    written = memory.write_block_vaddr_to_file(pt, ring, o, prod);
                    len += written;

                    if ( prod != written )
                        LOG_INFO("Mismatch writing console ring to file. Written %zu bytes "
                                 "of %"PRIu64"\n", written, prod);
                }
            }
            else
            {
                written = memory.write_block_vaddr_to_file(pt, ring + cons, o, prod - cons);
                len += written;

                if ( (prod - cons) != written )
                    LOG_INFO("Mismatch writing console ring to file. Written %zu bytes "
                             "of %"PRIu64"\n", written, prod - cons );
            }
        }
    }
    catch ( const CommonError & e )
    {
        e.log();
    }

    len += FPUTS("\n", o);
    return len;
}