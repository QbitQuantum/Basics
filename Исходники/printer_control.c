leave()
{
  close_all();
  execlp("syscomm", "syscomm", 0);
  krash("leave", "syscomm load", 1);
}