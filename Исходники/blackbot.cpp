bool
BlackBot::step(R dt)
{
  const Player &me(client.getPlayers()[pid]);
  // walk forward
  cinput.y=1;
  cinput.devno=inputID;
  
  if (followMode) follow();
  reachDir();
  sendInput();
  return true;
}