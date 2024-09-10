void SwgSnapshot::decodePersistedBuffs   (Archive::ReadIterator &data, DB::BufferString &dbString) const
{
	const unsigned version = 2;

	std::string packedValue;

	Archive::AutoDeltaMap<uint32, Buff::PackedBuff> temp;
	Archive::get(data,  temp);
	std::map<uint32, Buff::PackedBuff> const& rawMap = temp.getMap();

	FormattedString<200> formater;

	if(rawMap.empty())
	{
		packedValue = " ";
	}
	else
	{
		packedValue += formater.sprintf(versionFormat, version);

		for(std::map<uint32, Buff::PackedBuff>::const_iterator i = rawMap.begin(); i != rawMap.end(); ++i)
		{
			uint32 tempCrc = (*i).first;
			Buff::PackedBuff const & tempPacked = (*i).second;
			packedValue += formater.sprintf(versionTwoFormat, tempCrc, tempPacked.endtime, tempPacked.value, tempPacked.duration, tempPacked.caster.getValue(), tempPacked.stackCount);
		}
	}

	dbString.setValue(packedValue);
}