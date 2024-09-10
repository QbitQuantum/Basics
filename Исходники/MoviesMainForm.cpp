bool MoviesMainForm::handleKeyPress(const EventType& event)
{
    if (showTheatres == displayMode_ || showMovies == displayMode_)
    {
        ExtendedList& list = (showTheatres==displayMode()?theatresList_:moviesList_);
        int option = ExtendedList::optionScrollPagesWithLeftRight;
        if (application().runningOnTreo600())
            option = 0;
        if (list.handleKeyDownEvent(event, option | ExtendedList::optionFireListSelectOnCenter))
            return true;
        if (isAlNum(event.data.keyDown.chr) && 256 > event.data.keyDown.chr)
        {
            if (showMovies == displayMode_)
            {
                Movie m;
                m.title.assign(1, event.data.keyDown.chr);
                int pos = std::lower_bound(movies.begin(), movies.end(), &m, MovieTitleFirstLetterLess()) - movies.begin();
                if (pos == movies.size())
                    --pos;
                moviesList_.setSelection(pos, ExtendedList::redraw);
            }
            else 
                scrollTheatresListToLetter(event.data.keyDown.chr);
            return true;
        }
    }
    return false;
}