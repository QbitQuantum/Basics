float ArmorComponent::GetNonLocationalDamageMod() {
	class_t pcl = (class_t)entity.oldEnt->client->ps.stats[STAT_CLASS];

	for (int regionNum = 0; regionNum < g_numDamageRegions[pcl]; regionNum++) {
		damageRegion_t *region = &g_damageRegions[pcl][regionNum];

		if (!region->nonlocational) continue;

		armorLogger.Debug("Found non-locational damage modifier of %.2f.", region->modifier);

		return region->modifier;
	}

	armorLogger.Debug("No non-locational damage modifier found.");

	return 1.0f;
}