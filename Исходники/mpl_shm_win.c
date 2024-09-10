/* A template function which creates/attaches shm seg handle
 * to the shared memory. Used by user-exposed functions below
 */
static inline int MPL_shm_seg_create_attach_templ(MPL_shm_hnd_t hnd, intptr_t seg_sz,
                                                  void **shm_addr_ptr, int offset, int flag)
{
    HANDLE lhnd = INVALID_HANDLE_VALUE;
    int rc = MPL_SHM_SUCCESS;
    ULARGE_INTEGER seg_sz_large;
    seg_sz_large.QuadPart = seg_sz;

    if (!MPLI_shm_ghnd_is_valid(hnd)) {
        rc = MPLI_shm_ghnd_set_uniq(hnd);
        if (rc) {
            goto fn_exit;
        }
    }

    if (flag & MPLI_SHM_FLAG_SHM_CREATE) {
        lhnd = CreateFileMapping(INVALID_HANDLE_VALUE, NULL,
                                 PAGE_READWRITE, seg_sz_large.HighPart, seg_sz_large.LowPart,
                                 MPLI_shm_ghnd_get_by_ref(hnd));
        if (lhnd == NULL) {
            rc = MPL_SHM_EINTERN;
            goto fn_exit;
        }
        MPLI_shm_lhnd_set(hnd, lhnd);
    } else {
        if (!MPLI_shm_lhnd_is_valid(hnd)) {
            /* Strangely OpenFileMapping() returns NULL on error! */
            lhnd = OpenFileMapping(FILE_MAP_WRITE, FALSE, MPLI_shm_ghnd_get_by_ref(hnd));
            if (lhnd == NULL) {
                rc = MPL_SHM_EINTERN;
                goto fn_exit;
            }

            MPLI_shm_lhnd_set(hnd, lhnd);
        }
    }

    if (flag & MPLI_SHM_FLAG_SHM_ATTACH) {
        if (flag & MPLI_SHM_FLAG_FIXED_ADDR) {
            void *start_addr = (void *) *shm_addr_ptr;
            /* The start_addr must be a multiple of the system's memory allocation granularity,
             * or the function fails. To determine the memory allocation granularity of the system,
             * use the GetSystemInfo function. If there is not enough address space at the
             * specified address, the function fails.
             * If the function fails, the return value is NULL.*/
            *shm_addr_ptr = MapViewOfFileEx(MPLI_shm_lhnd_get(hnd),
                                            FILE_MAP_WRITE, 0, offset, 0, start_addr);
        } else {
            *shm_addr_ptr = MapViewOfFile(MPLI_shm_lhnd_get(hnd), FILE_MAP_WRITE, 0, offset, 0);
        }
        if (*shm_addr_ptr == NULL) {
            rc = MPL_SHM_EINVAL;
        }
    }

  fn_exit:
    return rc;
}