  bool LoadModel(std::string filename)
  {
    bool success = saveRestore.ReadFile(filename);
    if (success)
      anInt = saveRestore.LoadParameter(anInt, "anInt");

    return success;
  }