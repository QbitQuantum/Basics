// The exclusions list is a comma separated list of: the word "all" and/or CRCs in standard hex notation (0x and 8 digits with leading 0's if required).
// The list is case insensitive and order insensitive.
// E.g. Disable all CRC hacks:          CrcHacksExclusions=all
// E.g. Disable hacks for these CRCs:   CrcHacksExclusions=0x0F0C4A9C, 0x0EE5646B, 0x7ACF7E03
bool IsCrcExcluded(string exclusionList, uint32 crc)
{
	string target = format( "0x%08x", crc );
	exclusionList = ToLower( exclusionList );
	return ( exclusionList.find( target ) != string::npos || exclusionList.find( "all" ) != string::npos );
}