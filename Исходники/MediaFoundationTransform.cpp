void MediaFoundationTransform::SetUint32Property(PROPERTYKEY key, UINT32 value)
{
	PROPVARIANT propVar;

	InitPropVariantFromUInt32(value, &propVar);
	HRESULT hr = _propertyStore->SetValue(key, propVar);
	hr = S_OK;
}