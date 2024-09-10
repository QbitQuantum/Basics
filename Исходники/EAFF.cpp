void AudioENF::setDefaultHeader()
{
	enfHeader.formatID = FourCC("ENF");
	enfHeader.locationID.NationID = FourCC("NORW");
	enfHeader.locationID.RegionID = FourCC("OSLO");
    setLocalTime();
	enfHeader.sampleRate = 1000;
	enfHeader.bitsperSample = 16;
	enfHeader.dataSize = 0;
}