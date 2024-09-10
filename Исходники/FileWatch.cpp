// returns true if there was new data
bool FileWatch::update()
{
  process();
  return data.size() > 0;
}