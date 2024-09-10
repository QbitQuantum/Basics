void
WPiano::timerEvent(QTimerEvent *ev)
{
	if (ev->timerId() == update_timer_.timerId()) {
		if (playing() && cursor_time_ != player_->time()) {
			vmd_time_t prev_time = cursor_time_;
			setCursorTime(player_->time());
			if (timeVisible(prev_time))
				look_at_cursor();
		} else if (mouse_captured_)
			clipCursor();
	}
}