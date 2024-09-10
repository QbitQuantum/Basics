    void run() {
        Bedroom::Bed bed = bedroom_->getBed();

        while (!bed.sleep (timeout_ms_))
            ++timeout_count_;
    }