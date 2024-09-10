void Remove::exec(uint id) {
  vector<Room *> & rooms = roomIndex();
  Room * room = rooms[id];
  if (!room) return;
  map().remove(room->getPosition());
  RoomCollection * home = roomHomes()[id];
  if (home) home->erase(room);
  rooms[id] = 0;
  // don't return previously used ids for now
  // unusedIds().push(id);
  const ExitsList & exits = room->getExitsList();
  for(int dir = 0; dir < exits.size(); ++dir) {
    const Exit & e = exits[dir];
    for (set<uint>::const_iterator i = e.inBegin(); i != e.inEnd(); ++i) {
      Room * other = rooms[*i];
      if (other) other->exit(factory()->opposite(dir)).removeOut(id);
    }
    for (set<uint>::const_iterator i = e.outBegin(); i != e.outEnd(); ++i) { 
      Room * other = rooms[*i];
      if (other) other->exit(factory()->opposite(dir)).removeIn(id);
    }
  }
  delete room;
}