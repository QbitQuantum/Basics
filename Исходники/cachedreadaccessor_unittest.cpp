 // Test the CachedReadAccessor Pread() method.
 // This is the main method exposed by CachedReadAccessor.
 bool TestCachedReadAccessorPreadPerformance() {
   uint32 segment_id = 0;
   // Read request that is contained in 1 block.
   FileBundleReaderSegment segment(file_pool_,
                                   path_base_,
                                   segment_names_[segment_id],
                                   segment_names_[segment_id],
                                   segment_id);
   uint32 request_count = 1500; // typical 1500B for some Fusion packets.
   uint32 best_mb_per_sec = 0;
   uint32 best_kilobytes = 0;
   for(uint32 bytes = 1 << 14; bytes < 1 << 22; bytes <<= 1) {
     uint32 kilobytes = bytes / 1024;
     std::string prefix = "Cached read 2x " + Itoa(kilobytes) + "KB";
     uint32 mb_per_sec = TestReadAll(segment, request_count, 2, bytes, prefix);
     if (mb_per_sec > best_mb_per_sec) {
       best_mb_per_sec = mb_per_sec;
       best_kilobytes = kilobytes;
     }
   }
   uint32 uncached_mb_per_sec = TestReadAll(segment, request_count, 0, 0,
               std::string("Uncached read"));
   if (best_mb_per_sec > uncached_mb_per_sec) {
     std::cerr << "Cached is optimal " << best_mb_per_sec <<
       " MB/sec cached with " << best_kilobytes << "KB buffers vs Uncached "
       << uncached_mb_per_sec << " MB/sec" << std::endl;
   } else {
     std::cerr << "Uncached is optimal " << uncached_mb_per_sec <<
       " MB/sec vs Cached " << best_mb_per_sec << " MB/sec with " <<
       best_kilobytes << "KB buffers" << std::endl;
   }
   return true;
 }