 virtual void slaveDone(size32_t slaveIdx, MemoryBuffer &mb)
 {
     if (mb.length()) // if 0 implies aborted out from this slave.
     {
         rowcount_t rc;
         mb.read(rc);
         recordsProcessed += rc;
     }
 }