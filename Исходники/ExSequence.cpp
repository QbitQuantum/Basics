void ExSequenceTcb::initializeHistory()
{
  currentOLAPBuffer_ = NULL;
  currentHistRowInOLAPBuffer_ = 0;
  currentHistRowPtr_ = NULL;

  currentRetOLAPBuffer_ = NULL;
  currentRetHistRowInOLAPBuffer_ = 0;
  currentRetHistRowPtr_ = NULL;

  numberHistoryRows_ = 0;
  histRowsToReturn_ = 0;
  partitionEnd_ = FALSE;

  // allocate the minimum number of olap buffers
  if (firstOLAPBuffer_ == NULL)
  {
    for (Int32 i = 0 ; i < minNumberOfOLAPBuffers_; i++)
    {
      if ( ! addNewOLAPBuffer( FALSE /* No Memory Pressure Check */ ) ) 
        // LCOV_EXCL_START
        ex_assert(0, "No memory for minimal OLAP window!");
        // LCOV_EXCL_STOP
    }
  }  
  else
  {
    if (!shrinkOLAPBufferList())
      // LCOV_EXCL_START
      ex_assert(0,"initializeHistory-- can not shrink buffer list");
       // LCOV_EXCL_STOP
  }

  // Initialize all the settings needed for unbounded following (and overflow)
  if ( isUnboundedFollowing() )
  {
      //last row in partition
    if (lastRow_ == NULL)
    {
      lastRow_ = new(heap_) char[recLen()];
      ex_assert( lastRow_ , "No memory available for OLAP Operator");
    }

    // initialize parameters needed for overflow handling
    OLAPBuffersFlushed_ = FALSE;
    
    firstOLAPBufferFromOF_ = NULL;
    numberOfOLAPBuffersFromOF_ = 0;
    
    memoryPressureDetected_ = FALSE;
    numberOfRowsReturnedBeforeReadOF_ = 0;

    createCluster();

    // Cluster needs to know the first buffer in the OLAP list of buffers
    // (Currently only used when reading buffers from overflow for
    //  "bounded following", where Cluster::read() may need to jump back to
    //  first buffer in the list.)
    cluster_->firstBufferInList_ = firstOLAPBuffer_ ;

  } // if ( isUnboundedFollowing() )
}