      bool aligned_reallocate(block &b, size_t n) noexcept
      {
        block reallocatedBlock{ _aligned_realloc(b.ptr, n, alignment), n };

        if (reallocatedBlock) {
          b = reallocatedBlock;
          return true;
        }
        return false;
      }