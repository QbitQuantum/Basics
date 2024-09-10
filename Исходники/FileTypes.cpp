  FileTypes::Type FileTypes::nameToType(const String& name)
  {
    String tmp = name;
    tmp.toUpper();
    String tmp2;

    for (int i = 0; i < FileTypes::SIZE_OF_TYPE; ++i)
    {
      tmp2 = FileTypes::typeToName((FileTypes::Type)i);
      tmp2.toUpper();
      if (tmp == tmp2)
      {
        return (FileTypes::Type)i;
      }
    }

    return FileTypes::UNKNOWN;
  }