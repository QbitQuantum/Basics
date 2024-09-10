void TimeSigMap::add(int tick, const SigEvent& ev)
      {
      (*this)[tick] = ev;
      normalize();
      }