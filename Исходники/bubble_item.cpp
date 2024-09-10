void MsgBubbleItem::SetShowTime(bool show)
{
	if(show)
	{
		std::wstring tm = GetMessageTime(msg_.timetag_, false);
		msg_time_->SetText(tm);
	}
	msg_time_->SetVisible(show);
}