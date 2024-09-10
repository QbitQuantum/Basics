    AutoIsolateCleanup::~AutoIsolateCleanup() {
      while (Isolate::GetCurrent()) {
        // Isolates can be entered multiple times
        Isolate* i {Isolate::GetCurrent()};

        //internal::Isolate* ii {internal::Isolate::FromAPIIsolate(i)};
        //V8MONKEY_ASSERT(!ii->IsLockedForThisThread(), "An isolate was still locked");

        while (Isolate::GetCurrent() == i) {
          i->Exit();
        }

        i->Dispose();
      }
    }