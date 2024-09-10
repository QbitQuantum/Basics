am_shm_t *am_shm_create(const char *name, size_t usize) {
    struct mem_pool *pool = NULL;
    size_t size;
    char opened = AM_FALSE;
    void *area = NULL;
    am_shm_t *ret = NULL;
#ifdef _WIN32
    char dll_path[AM_URI_SIZE];
    DWORD error = 0;
    HMODULE hm = NULL;
    void *caller = _ReturnAddress();
#else
    int fdflags;
    int error = 0;
#endif

    ret = calloc(1, sizeof(am_shm_t));
    if (ret == NULL) return NULL;

#ifdef _WIN32
    if (GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
            GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCSTR) caller, &hm) &&
            GetModuleFileNameA(hm, dll_path, sizeof(dll_path) - 1) > 0) {
        PathRemoveFileSpecA(dll_path);
        strcat(dll_path, FILE_PATH_SEP);
        snprintf(ret->name[0], sizeof(ret->name[0]),
                AM_GLOBAL_PREFIX"%s_l", name); /* mutex/semaphore */
        snprintf(ret->name[1], sizeof(ret->name[1]),
                AM_GLOBAL_PREFIX"%s_s", name); /* shared memory name */
        snprintf(ret->name[2], sizeof(ret->name[2]),
                "%s.."FILE_PATH_SEP"log"FILE_PATH_SEP"%s_f", dll_path, name); /* shared memory file name */
        snprintf(ret->name[3], sizeof(ret->name[3]),
                AM_GLOBAL_PREFIX"%s_sz", name); /* shared memory name for global_size */
    } else {
        ret->error = AM_NOT_FOUND;
        return ret;
    }
#else
    snprintf(ret->name[0], sizeof(ret->name[0]),
            "/%s_l", name); /* mutex/semaphore */
    snprintf(ret->name[1], sizeof(ret->name[1]),
#ifdef __sun
            "/%s_s"
#else
            "%s_s"
#endif
            , name); /* shared memory name */
#endif

    size = page_size(usize + SIZEOF_mem_pool); /* need at least the size of the mem_pool header */

#ifdef _WIN32
    ret->h[0] = CreateMutexA(NULL, TRUE, ret->name[0]);
    error = GetLastError();
    if (ret->h[0] != NULL && error == ERROR_ALREADY_EXISTS) {
        do {
            error = WaitForSingleObject(ret->h[0], INFINITE);
        } while (error == WAIT_ABANDONED);
    } else {
        if (error == ERROR_ACCESS_DENIED) {
            ret->h[0] = OpenMutexA(SYNCHRONIZE, FALSE, ret->name[0]);
        }
        if (ret->h[0] == NULL) {
            ret->error = error;
            return ret;
        }
    }

    ret->h[1] = CreateFileA(ret->name[2], GENERIC_WRITE | GENERIC_READ,
            FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
            NULL, CREATE_NEW, FILE_FLAG_WRITE_THROUGH | FILE_FLAG_NO_BUFFERING, NULL);
    error = GetLastError();
    if (ret->h[1] == INVALID_HANDLE_VALUE && error == ERROR_FILE_EXISTS) {
        ret->h[1] = CreateFileA(ret->name[2], GENERIC_WRITE | GENERIC_READ,
                FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                NULL, OPEN_EXISTING, FILE_FLAG_WRITE_THROUGH | FILE_FLAG_NO_BUFFERING, NULL);
        error = GetLastError();
        if (ret->h[1] != INVALID_HANDLE_VALUE) {
            opened = AM_TRUE;
            size = GetFileSize(ret->h[1], NULL);
        }
    }

    if (ret->h[1] == INVALID_HANDLE_VALUE || error != 0) {
        CloseHandle(ret->h[0]);
        ret->error = error;
        am_shm_unlock(ret);
        return ret;
    }

    if (!opened) {
        ret->h[2] = CreateFileMappingA(ret->h[1], NULL, PAGE_READWRITE, 0, (DWORD) size, ret->name[1]);
        error = GetLastError();
    } else {
        ret->h[2] = OpenFileMappingA(FILE_MAP_READ | FILE_MAP_WRITE, FALSE, ret->name[1]);
        error = GetLastError();
        if (ret->h[2] == NULL && error == ERROR_FILE_NOT_FOUND) {
            ret->h[2] = CreateFileMappingA(ret->h[1], NULL, PAGE_READWRITE, 0, (DWORD) size, ret->name[1]);
            error = GetLastError();
        }
    }

    if (ret->h[2] == NULL || error != 0) {
        CloseHandle(ret->h[0]);
        CloseHandle(ret->h[1]);
        ret->error = error;
        am_shm_unlock(ret);
        return ret;
    }

    area = MapViewOfFile(ret->h[2], FILE_MAP_ALL_ACCESS, 0, 0, 0);
    error = GetLastError();
    if (area == NULL || (error != 0 && error != ERROR_ALREADY_EXISTS)) {
        CloseHandle(ret->h[0]);
        CloseHandle(ret->h[1]);
        CloseHandle(ret->h[2]);
        ret->error = error;
        am_shm_unlock(ret);
        return ret;
    }

    ret->h[3] = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, (DWORD) sizeof(size_t), ret->name[3]);
    if (ret->h[3] == NULL) {
        ret->error = GetLastError();
        CloseHandle(ret->h[0]);
        CloseHandle(ret->h[1]);
        CloseHandle(ret->h[2]);
        am_shm_unlock(ret);
        return ret;
    }
    ret->global_size = MapViewOfFile(ret->h[3], FILE_MAP_ALL_ACCESS, 0, 0, 0);
    if (ret->global_size == NULL) {
        ret->error = GetLastError();
        CloseHandle(ret->h[0]);
        CloseHandle(ret->h[1]);
        CloseHandle(ret->h[2]);
        CloseHandle(ret->h[3]);
        am_shm_unlock(ret);
        return ret;
    }
    *(ret->global_size) = ret->local_size = size;

#else

    ret->lock = mmap(NULL, sizeof(pthread_mutex_t),
            PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    if (ret->lock == MAP_FAILED) {
        ret->error = errno;
        return ret;
    } else {
        pthread_mutexattr_t attr;
        pthread_mutex_t *lock = (pthread_mutex_t *) ret->lock;
        pthread_mutexattr_init(&attr);
        pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
        pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
#if defined(__sun)
#if defined(__SunOS_5_10) 
#if defined(_POSIX_THREAD_PRIO_INHERIT)
        pthread_mutexattr_setprotocol(&attr, PTHREAD_PRIO_INHERIT);
        pthread_mutexattr_setrobust_np(&attr, PTHREAD_MUTEX_ROBUST_NP);
#endif
#else
        pthread_mutexattr_setrobust(&attr, PTHREAD_MUTEX_ROBUST);
#endif
#endif
#if defined(LINUX)
        pthread_mutexattr_setrobust_np(&attr, PTHREAD_MUTEX_ROBUST_NP);
#endif
        pthread_mutex_init(lock, &attr);
        pthread_mutexattr_destroy(&attr);
    }

    ret->global_size = mmap(NULL, sizeof(size_t),
            PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    if (ret->global_size == MAP_FAILED) {
        ret->error = errno;
        return ret;
    }

    *(ret->global_size) = ret->local_size = size;

    am_shm_lock(ret);

    ret->fd = shm_open(ret->name[1], O_CREAT | O_EXCL | O_RDWR, 0666);
    error = errno;
    if (ret->fd == -1 && error != EEXIST) {
        munmap(ret->lock, sizeof(pthread_mutex_t));
        ret->error = error;
        am_shm_unlock(ret);
        return ret;
    }
    if (ret->fd == -1) {
        ret->fd = shm_open(ret->name[1], O_RDWR, 0666);
        error = errno;
        if (ret->fd == -1) {
            munmap(ret->lock, sizeof(pthread_mutex_t));
            ret->error = error;
            am_shm_unlock(ret);
            return ret;
        }
        /* reset FD_CLOEXEC */
        fdflags = fcntl(ret->fd, F_GETFD);
        fdflags &= ~FD_CLOEXEC;
        fcntl(ret->fd, F_SETFD, fdflags);
        /* try with just a header */
        area = mmap(NULL, SIZEOF_mem_pool, PROT_READ | PROT_WRITE, MAP_SHARED, ret->fd, 0);
        if (area == MAP_FAILED) {
            ret->error = errno;
            am_shm_unlock(ret);
            return ret;
        }
        size = ((struct mem_pool *) area)->size;
        if (munmap(area, SIZEOF_mem_pool) == -1) {
            ret->error = errno;
            am_shm_unlock(ret);
            return ret;
        }
        area = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, ret->fd, 0);
        if (area == MAP_FAILED) {
            ret->error = errno;
            am_shm_unlock(ret);
            return ret;
        }
        opened = AM_TRUE;
    } else {
        /* reset FD_CLOEXEC */
        fdflags = fcntl(ret->fd, F_GETFD);
        fdflags &= ~FD_CLOEXEC;
        fcntl(ret->fd, F_SETFD, fdflags);
        if (ftruncate(ret->fd, size) == -1) {
            ret->error = errno;
            am_shm_unlock(ret);
            return ret;
        }
        area = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, ret->fd, 0);
        if (area == MAP_FAILED) {
            ret->error = errno;
            am_shm_unlock(ret);
            return ret;
        }
    }

#endif

    ret->init = !opened;

    pool = (struct mem_pool *) area;
    if (ret->init) {
        struct mem_chunk *e = (struct mem_chunk *) ((char *) pool + SIZEOF_mem_pool);
        pool->size = size;
        pool->user_offset = 0;
        pool->open = 1;
        pool->resize = 0;

        /* add all available (free) space as one chunk in a freelist */
        e->used = 0;
        e->usize = 0;
        e->size = pool->size - SIZEOF_mem_pool;
        e->lh.next = e->lh.prev = 0;
        /* update head prev/next pointers */
        pool->lh.next = pool->lh.prev = AM_GET_OFFSET(pool, e);
    } else {
        if (pool->user_offset > 0) {
            ret->user = AM_GET_POINTER(pool, pool->user_offset);
        }
        pool->open++;
    }

    ret->pool = pool;
    ret->error = 0;
    am_shm_unlock(ret);
    return ret;
}