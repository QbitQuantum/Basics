inline
void SwitchVectorEndian(std::vector<unsigned short>& data)
{
	BOOST_STATIC_ASSERT(sizeof(unsigned short)==2);

	SwabType* p_data=reinterpret_cast <SwabType*>(&data[0]);

	swab(p_data,
		p_data,
		static_cast<int>(data.size()*2));
}