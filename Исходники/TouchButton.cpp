void TouchButton::DrawButton(VideoPtr video, InputPtr input, SpriteResourceManager& spr)
{
	SpritePtr sprite = spr.GetSprite(video, m_buttonSprite);
	video->SetAlphaMode(GSAM_PIXEL);
	if (sprite)
	{
		sprite->SetRect(m_buttonFrame);
		sprite->SetOrigin(m_origin);
		sprite->Draw(m_pos);

		if (m_status == PRESSED)
		{
			video->SetAlphaMode(GSAM_ADD);
			sprite->Draw(m_pos);
			video->SetAlphaMode(GSAM_PIXEL);
		}
	}
}