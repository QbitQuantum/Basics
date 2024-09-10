long int CmdMessenger::getAsLong() {
  char str[255];
  this->copyString(str, 255);
  return atol(str);
}