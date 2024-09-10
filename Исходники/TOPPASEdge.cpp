  TOPPASEdge::EdgeStatus TOPPASEdge::getListToolStatus_(TOPPASInputFileListVertex * source_input_list, TOPPASToolVertex * target_tool, int target_param_index)
  {
    QVector<TOPPASToolVertex::IOInfo> target_input_files;
    target_tool->getInputParameters(target_input_files);
    if (target_param_index >= target_input_files.size())
    {
      return ES_TOOL_API_CHANGED;
    }

    const QStringList & file_names = source_input_list->getFileNames();
    if (file_names.empty())
    {
      // file names are not specified yet
      return ES_NOT_READY_YET;
    }

    if (target_param_index < 0)
    {
      return ES_NO_TARGET_PARAM;
    }

    const TOPPASToolVertex::IOInfo & target_param = target_input_files[target_param_index];
    StringList target_param_types = target_param.valid_types;

    if (target_param_types.empty())
    {
      // no file types specified --> allow
      return ES_VALID;
    }

    // check file type compatibility
    foreach(const QString &q_file_name, file_names)
    {
      bool type_mismatch = true;
      const String & file_name = String(q_file_name);
      String::SizeType extension_start_index = file_name.rfind(".");
      if (extension_start_index != String::npos)
      {
        String extension = file_name.substr(extension_start_index + 1);
        extension.toLower();
        for (StringList::iterator it = target_param_types.begin(); it != target_param_types.end(); ++it)
        {
          String other_ext = *it;
          other_ext.toLower();
          if (extension == other_ext || extension == "gz" || extension == "bz2")
          {
            type_mismatch = false;
            break;
          }
        }
      }

      if (type_mismatch)
      {
        return ES_FILE_EXT_MISMATCH;
      }
    }