void DirInstaller::doMovesDeletes(const StrMap &moves, const HashDir &del)
{
  DirMap created;
  StrSet removed;
  for(StrMap::const_iterator it = moves.begin(); it != moves.end(); it++)
    {
      ptr->owner->moveFile(it->first, it->second);
      created[it->second] = Hash();
      removed.insert(it->first);
    }
  for(HashDir::const_iterator it = del.begin(); it != del.end(); it++)
    {
      ptr->owner->deleteFile(it->second);
      removed.insert(it->second);
    }
  index.addMany(created, removed);
}