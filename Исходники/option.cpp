void TOptions::Add(const UnicodeString & Value)
{
  if (!FNoMoreSwitches &&
      (Value.Length() == 2) &&
      (Value[1] == Value[2]) &&
      (FSwitchMarks.Pos(Value[1]) > 0))
  {
    FNoMoreSwitches = true;
  }
  else
  {
    bool Switch = false;
    intptr_t Index = 0; // shut up
    if (!FNoMoreSwitches &&
        (Value.Length() >= 2) &&
        (FSwitchMarks.Pos(Value[1]) > 0))
    {
      Index = 2;
      Switch = true;
      while (Switch && (Index <= Value.Length()))
      {
        if (Value.IsDelimiter(FSwitchValueDelimiters, Index))
        {
          break;
        }
        // this is to treat /home/martin as parameter, not as switch
        else if ((Value[Index] != L'?') && !IsLetter(Value[Index]))
        {
          Switch = false;
          break;
        }
        ++Index;
      }
    }

    if (Switch)
    {
      TOption Option;
      Option.Type = otSwitch;
      Option.Name = Value.SubString(2, Index - 2);
      Option.Value = Value.SubString(Index + 1, Value.Length());
      Option.Used = false;
      FOptions.push_back(Option);
    }
    else
    {
      TOption Option;
      Option.Type = otParam;
      Option.Value = Value;
      Option.Used = false;
      FOptions.push_back(Option);
      ++FParamCount;
    }
  }

  FOriginalOptions = FOptions;
}