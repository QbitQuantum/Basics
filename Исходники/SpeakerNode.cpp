void SpeakerNode::Draw(NodeRenderer *r, const math::rectf& rc)
{
	if (rc.IsRectCollide(GetBoundingBox(false)))
		r->AddSpeaker(this, m_glowFactor);
	for (int i = 0; i < m_subTweets.size(); ++i)
	{
		r->AddSpeakerTweetNode(this, m_subTweets[i]);
	}

	for (int i = 0; i < m_subTweets.size(); ++i)
	{
		m_subTweets[i]->Draw(r,rc);
	}
}