  bool AlchemyCreateProfile::processApplication()
  {
    // process parameters passed in by user
    if (!loadParams())
    {
      getContext() << Context::PRIORITY_error
                   << "Application failed while loading parameters"
                   << Context::endl;
      return false;
    }
    printParams();

    if (!readData(m_trainFile, m_trainData, "training data"))
    {
      getContext() << Context::PRIORITY_error
                   << "Application failed while reading training data"
                   << Context::endl;
      return false;
    }
    else if (!m_trainData.size())
    {
      getContext() << Context::PRIORITY_error
                   << "No training data was read; aborting execution"
                   << Context::endl;
      return false;
    }

    if (!createProfile())
    {
      getContext() << Context::PRIORITY_error
                   << "Application failed while creating prediction profile"
                   << Context::endl;
      return false;
    }

    return true;
  }