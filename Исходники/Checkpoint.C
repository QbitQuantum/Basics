void
Checkpoint::updateCheckpointFiles(CheckpointFileNames file_struct)
{
  int ret = 0;          // return code for file operations

  // Update the list of stored files
  _file_names.push_back(file_struct);

  // Remove un-wanted files
  if (_file_names.size() > _num_files)
  {
    // Extract the filenames to be removed
    CheckpointFileNames delete_files = _file_names.front();

    // Remove these filenames from the list
    _file_names.pop_front();

    // Get thread and proc information
    processor_id_type proc_id = processor_id();

    // Delete checkpoint files (_mesh.cpr)

    if (proc_id == 0)
    {
      ret = remove(delete_files.checkpoint.c_str());
      if (ret != 0)
        mooseWarning("Error during the deletion of file '" << delete_files.checkpoint << "': " << ret);

      // Delete the system files (xdr and xdr.0000, ...)
      ret = remove(delete_files.system.c_str());
      if (ret != 0)
        mooseWarning("Error during the deletion of file '" << delete_files.system << "': " << ret);
    }

    {
      std::ostringstream oss;
      oss << delete_files.system
          << "." << std::setw(4)
          << std::setprecision(0)
          << std::setfill('0')
          << proc_id;
      ret = remove(oss.str().c_str());
      if (ret != 0)
        mooseWarning("Error during the deletion of file '" << oss.str().c_str() << "': " << ret);
    }

    unsigned int n_threads = libMesh::n_threads();

    // Remove material property files
    if (_material_property_storage.hasStatefulProperties() || _bnd_material_property_storage.hasStatefulProperties())
    {
      ret = remove(delete_files.material.c_str());
      if (ret != 0)
        mooseWarning("Error during the deletion of file '" << delete_files.material << "': " << ret);

      for (THREAD_ID tid = 0; tid < n_threads; tid++)
      {
        std::ostringstream oss;
        oss << delete_files.material << '-' << proc_id;
        if (n_threads > 1)
          oss << "-" << tid;
        ret = remove(oss.str().c_str());
        if (ret != 0)
          mooseWarning("Error during the deletion of file '" << oss.str().c_str() << "': " << ret);
      }
    }

    // Remove the restart files (rd)
    {
      for (THREAD_ID tid = 0; tid < n_threads; tid++)
      {
        std::ostringstream oss;
        oss << delete_files.restart << "-" << proc_id;
        if (n_threads > 1)
          oss << "-" << tid;
        ret = remove(oss.str().c_str());
        if (ret != 0)
          mooseWarning("Error during the deletion of file '" << oss.str().c_str() << "': " << ret);
      }
    }
  }
}