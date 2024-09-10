void RoyalSocietyApp::update()
{
	if(leftClicked_)
	{
		leftClicked_ = false;
		// check for button presses
		if(helpButton_->isInside(mousePos_))
		{
			if(help_)
				help_ = false;
			else help_ = true;
		}
		if(newWinButton_->isInside(mousePos_))
		{
			Window* window = new Window(Vec2i(120, 100), winTexture_);
			sentinel_->insertBefore(sentinel_->next_, window); 
			window = 0;
		}
		if(reverseButton_->isInside(mousePos_))
		{
			sentinel_->reverse(sentinel_);
		}

		/*
			Matt: For the left and right buttons, if there is only one window displayed,
			the window is (seemingly) deleted.  This is probably due to your sentinel not
			actually containing data.

			The lines I added in the following two if statements check to see if there is 
			only one other node besides the sentinel.  If this is the case (meaning both 
			the next_ and prev_ of the current node will be pointing to the sentinel, the 
			window will not (seemingly) delete itself when the moveToBack or moveToFront is called.
		*/
		if(leftButton_->isInside(mousePos_))
		{
			// Matt: Note addition of following line
			if(sentinel_->next_->prev_ != sentinel_ || sentinel_->next_->next_ != sentinel_)
				sentinel_->moveToBack(sentinel_->prev_);
		}
		if(rightButton_->isInside(mousePos_))
		{
			// Matt: Note addition of following line
			if(sentinel_->next_->prev_ != sentinel_ || sentinel_->next_->next_ != sentinel_)
				sentinel_->moveToFront(sentinel_->next_);
		}
		if(deleteButton_->isInside(mousePos_))
		{
			if(sentinel_ != sentinel_->next_)
				sentinel_->remove(sentinel_->next_);
		}
	}
}