bool
FileType::List( CommandInterpreter& inInterpreter )
{
  return DirectoryType::ListSelection( inInterpreter, ".", inInterpreter.GetToken(), &FileUtils::IsFile );
}