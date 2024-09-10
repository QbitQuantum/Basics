void
vsDisplayList::ApplyOffset(const vsVector2D &offset)
{
	vsAssert( !m_instanceParent, "Tried to apply an offset to an instanced display list!" );

	vsTransform2D currentTransform;

	Rewind();
	op *o = PopOp();

	while(o)
	{
		if ( o->type == OpCode_VertexArray )
		{
			vsVector3D pos;
			int count = o->data.GetUInt();
			float *shuttle = (float *) o->data.p;

			for ( int i = 0; i < count; i++ )
			{
				shuttle[0] += offset.x;
				shuttle[1] += offset.y;

				shuttle += 3;
			}
		}

		o = PopOp();
	}
}