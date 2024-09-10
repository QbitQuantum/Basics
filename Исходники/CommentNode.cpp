void CommentNode::Draw(NodeRenderer *r, const math::rectf& rc)
{
	if (rc.IsRectCollide(GetBoundingBox(false)))
		r->AddComment(this, m_sizeScaler);

}