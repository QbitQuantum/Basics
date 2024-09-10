void GestureMoveRight::action()
{
  //sendInput(0x0020);//space
  sendInput(0xff08);//backspace
  cout << "move right" << endl;
}