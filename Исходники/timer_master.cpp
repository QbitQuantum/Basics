void TimerMaster::Update(int jiffies) {
  CHECK_GE(jiffies, timer_jiffies_);
  TimerVec &v0 = vecs_[0];
  while (jiffies - timer_jiffies_ >= 0) {
    vector<pair<TimerSlot*, boost::shared_ptr<Timer> > > timers;
    {
      boost::mutex::scoped_lock lock(mutex_);
      const int index = timer_jiffies_ & kTVMask;
      if (!index && !CascadeTimers(&vecs_[1], INDEX(1)) &&
          !CascadeTimers(&vecs_[2], INDEX(2))) {
        CascadeTimers(&vecs_[3], INDEX(3));
      }
      TList *l = &v0[index];
      for (TList::iterator it = l->begin();
           it != l->end();) {
        TimerSlot *s = &*it;
        ++it;
        s->unlink();
        boost::weak_ptr<Timer> weak_timer = s->weak_timer;
        boost::shared_ptr<Timer> timer = weak_timer.lock();
        if (weak_timer.expired()) {
          delete s;
          continue;
        }
        timers.push_back(make_pair(s, timer));
      }
    }
    const int old_timer_jiffies = timer_jiffies_;
    ++timer_jiffies_;
    for (vector<pair<TimerSlot*, boost::shared_ptr<Timer> > >::iterator it =
         timers.begin(); it != timers.end(); ++it) {
      it->second->Expired();
    }
    {
      for (int i = 0; i < timers.size(); ++i) {
        TimerSlot *s = timers[i].first;
        boost::shared_ptr<Timer> timer = timers[i].second;
        if (timer->period()) {
          boost::mutex::scoped_lock lock(mutex_);
          InternalAddTimer(s, timer, timer->timeout() + old_timer_jiffies);
        } else {
          delete s;
        }
      }
    }
  }
}