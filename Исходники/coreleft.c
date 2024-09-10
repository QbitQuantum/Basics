    unsigned cdecl coreleft(void)
    {
      #ifdef __WATCOMC__

        struct _heapinfo entry;
        unsigned left;

        left=0;
        entry._pentry=NULL;

        while (1)
        {
          if (_heapwalk(&entry) != _HEAPOK)
            break;

          if (entry._useflag==_FREEENTRY)
            left += entry._size;
        }

        return (left);
      #else
        return (_memavl());
      #endif
    }