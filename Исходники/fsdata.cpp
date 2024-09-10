//static
void FSData::sendInfo(LLUUID destination, LLUUID sessionid, std::string myName, EInstantMessage dialog)
{
	LLSD system_info = getSystemInfo();
	std::string part1 = system_info["Part1"].asString();
	std::string part2 = system_info["Part2"].asString();

	pack_instant_message(
		gMessageSystem,
		gAgent.getID(),
		FALSE,
		gAgent.getSessionID(),
		destination,
		myName,
		part1,
		IM_ONLINE,
		dialog,
		sessionid
		);
	gAgent.sendReliableMessage();
	pack_instant_message(
		gMessageSystem,
		gAgent.getID(),
		FALSE,
		gAgent.getSessionID(),
		destination,
		myName,
		part2,
		IM_ONLINE,
		dialog,
		sessionid
		);
	gAgent.sendReliableMessage();

	gIMMgr->addMessage(gIMMgr->computeSessionID(dialog,destination),destination,myName,
				"Information Sent: " + part1 + "\n" + part2);
}