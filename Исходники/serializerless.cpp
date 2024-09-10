SerializerLess::SerializerLess(Serializer& _ser)
	: Serializer()
	, m_ref(nullptr)
{
	SliceBuffer(_ser, _ser.GetCursor(), _ser.GetBufferSize());
}