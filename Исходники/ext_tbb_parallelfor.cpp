// f_parallel_for
//  arraydata - input array to process
//  func - worker function of the form worker($begin, $end)
//  blocksize - optional blocksize, refer to TBB documentation
//
// Call 'func' for non-overlapping ranges which cover the range [begin,end)
// This will use threads as appropriate for the machine.
// Note that globals are only accessible as a copy within 'func', so this version is only
// useful to generate external outputs.
void f_parallel_for(int64 begin, int64 end, CVarRef func, int64 blocksize /* = -1 */) {
        TbbInitializeIfNeeded();

        TbbContext myContext  = TbbContext::Entry("parallel_for");

        std::vector<Variant> outArray;
        outArray.resize(end-begin);

        if (blocksize == -1) {
                // Use auto_partitioner for block size
                tbb::parallel_for(tbb::blocked_range<int64>(begin, end), PforTaskParameters(myContext, func, &outArray), tbb::auto_partitioner());
        } else {
                // Use manually set block size
                tbb::parallel_for(tbb::blocked_range<int64>(begin, end, blocksize), PforTaskParameters(myContext, func, &outArray));
        }

        myContext.Exit();
}