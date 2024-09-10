SqlMassInsert& SqlMassInsert::operator()(const ValueMap& data)
{
	for(int i = 0; i < data.GetCount(); i++)
		operator()((String)data.GetKey(i), data.GetValue(i));
	return *this;
}