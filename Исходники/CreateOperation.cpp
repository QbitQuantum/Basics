std::string CreateOperation::GetOpDescription() const
{
	char buffer[512];
	sprintf_s(buffer, sizeof(buffer), "%s, ID: %lli, Name: %s, Value: %s", GetTypeName(), m_elementGuid, m_name->GetString().c_str(), m_startingValue.ToString().c_str());
	return buffer;
}