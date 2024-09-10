void SG_Spatial::getAABBox(MT_Point3 *box) const
{
	m_bbox.getaa(box, GetWorldTransform());
}