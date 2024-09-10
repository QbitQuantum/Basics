      //
      // Destructor
      //
      Item::~Item()
      {
        ASSERT(curCacheSize - record->fastFind->Size() >= 0);

        curCacheSize -= record->fastFind->Size();
        items.Unlink(this);
        AIL_mem_free_lock(data);
      }