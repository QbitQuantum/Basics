void * __cdecl _realloc_base (void * pBlock, size_t newsize)
{
        void *      pvReturn;
        size_t      origSize = newsize;

        //  if ptr is NULL, call malloc
        if (pBlock == NULL)
            return(_malloc_base(newsize));

        //  if ptr is nonNULL and size is zero, call free and return NULL
        if (newsize == 0)
        {
            _free_base(pBlock);
            return(NULL);
        }


#ifndef _WIN64
        if ( __active_heap == __V6_HEAP )
        {
            PHEADER     pHeader;
            size_t      oldsize;

            for (;;)
            {
                pvReturn = NULL;
                if (newsize <= _HEAP_MAXREQ)
                {
                    _mlock( _HEAP_LOCK );
                    __try
                    {

                    //  test if current block is in the small-block heap
                    if ((pHeader = __sbh_find_block(pBlock)) != NULL)
                    {
                        //  if the new size is not over __sbh_threshold, attempt
                        //  to reallocate within the small-block heap
                        if (newsize <= __sbh_threshold)
                        {
                            if (__sbh_resize_block(pHeader, pBlock, (int)newsize))
                                pvReturn = pBlock;
                            else if ((pvReturn = __sbh_alloc_block((int)newsize)) != NULL)
                            {
                                oldsize = ((PENTRY)((char *)pBlock -
                                                    sizeof(int)))->sizeFront - 1;
                                memcpy(pvReturn, pBlock, __min(oldsize, newsize));
                                // headers may have moved, get pHeader again
                                pHeader = __sbh_find_block(pBlock);
                                __sbh_free_block(pHeader, pBlock);
                            }
                        }

                        //  If the reallocation has not been (successfully)
                        //  performed in the small-block heap, try to allocate
                        //  a new block with HeapAlloc.
                        if (pvReturn == NULL)
                        {
                            if (newsize == 0)
                                newsize = 1;
                            newsize = (newsize + BYTES_PER_PARA - 1) &
                                      ~(BYTES_PER_PARA - 1);
                            if ((pvReturn = HeapAlloc(_crtheap, 0, newsize)) != NULL)
                            {
                                oldsize = ((PENTRY)((char *)pBlock -
                                                    sizeof(int)))->sizeFront - 1;
                                memcpy(pvReturn, pBlock, __min(oldsize, newsize));
                                __sbh_free_block(pHeader, pBlock);
                            }
                        }
                    }

                    }
                    __finally
                    {
                        _munlock( _HEAP_LOCK );
                    }

                    //  the current block is NOT in the small block heap iff pHeader
                    //  is NULL
                    if ( pHeader == NULL )
                    {
                        if (newsize == 0)
                            newsize = 1;
                        newsize = (newsize + BYTES_PER_PARA - 1) &
                                  ~(BYTES_PER_PARA - 1);
                        pvReturn = HeapReAlloc(_crtheap, 0, pBlock, newsize);
                    }
                }
                else    /* newsize > _HEAP_MAXREQ */
                {