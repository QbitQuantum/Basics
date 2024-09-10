void MainThread::think() {
  MoveList<LEGAL_ALL> ml(rootPos);
  Move m = (ml.size() == 0) ? MOVE_RESIGN : ml.at(size_t(my_rand.rand(ml.size()))).move;
  sync_cout << "bestmove " << m << sync_endl;
}