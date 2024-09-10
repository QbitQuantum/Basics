void DataTableSupport::setFilename(const fs::path & filename)
{
  if(myFilename == filename)
    return;

  myFilename = filename;

  if(myEngine && myEngine->getState() == ::pipelib::PipelineState::RUNNING)
  {
    if(myWriter.get())
    {
      // Write the final state of the old filename
      myWriter->write();
    }

    // Start the new writer
    createWriter();
  }
}