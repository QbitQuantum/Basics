LevelDBStorage::~LevelDBStorage()
{
  terminate(process);
  wait(process);
  delete process;
}