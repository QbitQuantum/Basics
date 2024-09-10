void add_map_option(LLComboBox& flyout, const std::string& map, const LLUUID& id, U8& did)
{
	flyout.remove(map);
	if (is_agent_mappable(id) && LLAvatarTracker::instance().isBuddyOnline(id))
	{
		flyout.add(map, -2);
		did |= 0x02; // Added map, needs rebuild.
	}
	did |= 0x01; // Checked map
}