void JointTransform::PopulateStructure( Reflect::Structure& comp )
{
    comp.AddField( &JointTransform::m_SegmentScaleCompensate, TXT( "m_SegmentScaleCompensate" ) );
}