static PyObject *
mmap_resize_method(mmap_object *self,
                   PyObject *args)
{
    Py_ssize_t new_size;
    CHECK_VALID(NULL);
    if (!PyArg_ParseTuple(args, "n:resize", &new_size) ||
        !is_resizeable(self)) {
        return NULL;
#ifdef MS_WINDOWS
    } else {
        DWORD dwErrCode = 0;
        DWORD off_hi, off_lo, newSizeLow, newSizeHigh;
        /* First, unmap the file view */
        UnmapViewOfFile(self->data);
        self->data = NULL;
        /* Close the mapping object */
        CloseHandle(self->map_handle);
        self->map_handle = NULL;
        /* Move to the desired EOF position */
        newSizeHigh = (DWORD)((self->offset + new_size) >> 32);
        newSizeLow = (DWORD)((self->offset + new_size) & 0xFFFFFFFF);
        off_hi = (DWORD)(self->offset >> 32);
        off_lo = (DWORD)(self->offset & 0xFFFFFFFF);
        SetFilePointer(self->file_handle,
                       newSizeLow, &newSizeHigh, FILE_BEGIN);
        /* Change the size of the file */
        SetEndOfFile(self->file_handle);
        /* Create another mapping object and remap the file view */
        self->map_handle = CreateFileMapping(
            self->file_handle,
            NULL,
            PAGE_READWRITE,
            0,
            0,
            self->tagname);
        if (self->map_handle != NULL) {
            self->data = (char *) MapViewOfFile(self->map_handle,
                                                FILE_MAP_WRITE,
                                                off_hi,
                                                off_lo,
                                                new_size);
            if (self->data != NULL) {
                self->size = new_size;
                Py_INCREF(Py_None);
                return Py_None;
            } else {
                dwErrCode = GetLastError();
                CloseHandle(self->map_handle);
                self->map_handle = NULL;
            }
        } else {
            dwErrCode = GetLastError();
        }
        PyErr_SetFromWindowsErr(dwErrCode);
        return NULL;
#endif /* MS_WINDOWS */

#ifdef UNIX
#ifndef HAVE_MREMAP
    } else {