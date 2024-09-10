void GUITextBox::Draw()
{
	if(IsVisible())
	{
		COLOR4 color = GetColor();
		Box(GetX(), GetY(), GetWidth(), GetHeight(),
			color.r, color.g, color.b, color.a);

		if(GetCaption() && GetCaptionFont())
		{
			COLOR4 c_color = GetCaptionColor();
			glColor4ub(c_color.r, c_color.g, c_color.b, c_color.a);
			PrintText(GetCaption(), GetCaptionFont(),
				GetX() + GetCaptionX(), GetY() + GetCaptionY());
		}

		if(GetTextFont())
		{
			COLOR4 t_color = GetTextColor();
			glColor4ub(t_color.r, t_color.g, t_color.b, t_color.a);
			PrintText(GetText(), GetTextFont(),
				GetX() + GetTextX(), GetY() + GetTextY());
		}
	}
}