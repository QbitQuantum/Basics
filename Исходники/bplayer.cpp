 void stopPlay()
 {
     if (!nowPlaying_ || NULL == playThread_) return;
     progressThread_->stop();
     playThread_->stop();
     beeper_.rest(1);
     delete progressThread_;
     delete playThread_;
     playThread_ = NULL;
     progressThread_ = NULL;
     nowPlaying_ = false;
     progressIcon_->reset();
 }