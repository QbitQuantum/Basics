 Slice::~Slice()
 {
     try
     {
         GetDocTable().Cleanup(m_buffer);
         m_shard.ReleaseSliceBuffer(m_buffer);
     }
     catch (...)
     {
         LogB(Logging::Error, "Slice", "Exception caught in Slice::~Slice()","");
     }
 }