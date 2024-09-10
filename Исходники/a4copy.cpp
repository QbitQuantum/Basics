 void setup_processor(CopyProcessor& p) {
     if (_start_index) {
         static int processor_count = 0;
         if (processor_count++)
             TERMINATE("--start-index only works with one processor (-t1)");
         p._start_index = _start_index;
     }
     p._metadata_only = _metadata_only;
 }