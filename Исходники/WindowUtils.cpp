AutoScroller::~AutoScroller()
{
    if(scrollInfo_.fMask == 0)
    {
        scrollInfo_.fMask = SIF_ALL;
        BOOL res = GetScrollInfo(window_->GetHWND(), winSB(orient_), &scrollInfo_);
        if(!res)
            return;
    }
    bool autoScroll = scrollInfo_.nPos + static_cast<int>(scrollInfo_.nPage) >= scrollInfo_.nMax;
    if(autoScroll)
    {
        memset(&scrollInfo_, 0, sizeof(scrollInfo_));
        scrollInfo_.cbSize = sizeof(scrollInfo_);
        scrollInfo_.fMask = SIF_ALL;
        BOOST_VERIFY(GetScrollInfo(window_->GetHWND(), winSB(orient_), &scrollInfo_));
        window_->ScrollLines(scrollInfo_.nMax);
    }
}