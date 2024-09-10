  /**
   * \brief Fetch the Logo for the given channel id
   * \param channel_id       String containing the 4TR channel_id
   * \param filename         filename returned here
   */
  int GetChannelLogo(const std::string& channel_id, std::string& filename)
  {
    char command[512];

    snprintf(command, 512, "ForTheRecord/Scheduler/ChannelLogo/%s/100/100/false/2011-01-01", channel_id.c_str());
    
    filename = _tempnam(NULL, "ftrico");
    int retval = ForTheRecordRPCToFile(command, "", filename);

    return retval;
  }