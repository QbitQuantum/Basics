FSerializer &Serialize(FSerializer &arc, const char *key, sector_t &p, sector_t *def)
{
	// save the Scroll data here because it's a lot easier to handle a default.
	// Just writing out the full array can massively inflate the archive for no gain.
	DVector2 scroll = { 0,0 }, nul = { 0,0 };
	if (arc.isWriting() && level.Scrolls.Size() > 0) scroll = level.Scrolls[p.sectornum];

	if (arc.BeginObject(key))
	{
		arc("floorplane", p.floorplane, def->floorplane)
			("ceilingplane", p.ceilingplane, def->ceilingplane)
			("lightlevel", p.lightlevel, def->lightlevel)
			("special", p.special, def->special)
			("seqtype", p.seqType, def->seqType)
			("seqname", p.SeqName, def->SeqName)
			("friction", p.friction, def->friction)
			("movefactor", p.movefactor, def->movefactor)
			("stairlock", p.stairlock, def->stairlock)
			("prevsec", p.prevsec, def->prevsec)
			("nextsec", p.nextsec, def->nextsec)
			.Array("planes", p.planes, def->planes, 2, true)
			// These cannot change during play.
			//("heightsec", p.heightsec)
			//("bottommap", p.bottommap)
			//("midmap", p.midmap)
			//("topmap", p.topmap)
			("damageamount", p.damageamount, def->damageamount)
			("damageinterval", p.damageinterval, def->damageinterval)
			("leakydamage", p.leakydamage, def->leakydamage)
			("damagetype", p.damagetype, def->damagetype)
			("sky", p.sky, def->sky)
			("moreflags", p.MoreFlags, def->MoreFlags)
			("flags", p.Flags, def->Flags)
			.Array("portals", p.Portals, def->Portals, 2, true)
			("zonenumber", p.ZoneNumber, def->ZoneNumber)
			.Array("interpolations", p.interpolations, 4, true)
			("soundtarget", p.SoundTarget)
			("secacttarget", p.SecActTarget)
			("floordata", p.floordata)
			("ceilingdata", p.ceilingdata)
			("lightingdata", p.lightingdata)
			("fakefloor_sectors", p.e->FakeFloor.Sectors)
			("midtexf_lines", p.e->Midtex.Floor.AttachedLines)
			("midtexf_sectors", p.e->Midtex.Floor.AttachedSectors)
			("midtexc_lines", p.e->Midtex.Ceiling.AttachedLines)
			("midtexc_sectors", p.e->Midtex.Ceiling.AttachedSectors)
			("linked_floor", p.e->Linked.Floor.Sectors)
			("linked_ceiling", p.e->Linked.Ceiling.Sectors)
			("colormap", p.ColorMap, def->ColorMap)
			.Terrain("floorterrain", p.terrainnum[0], &def->terrainnum[0])
			.Terrain("ceilingterrain", p.terrainnum[1], &def->terrainnum[1])
			("scrolls", scroll, nul)
			.EndObject();

		if (arc.isReading() && !scroll.isZero())
		{
			if (level.Scrolls.Size() == 0)
			{
				level.Scrolls.Resize(numsectors);
				memset(&level.Scrolls[0], 0, sizeof(level.Scrolls[0])*level.Scrolls.Size());
				level.Scrolls[p.sectornum] = scroll;
			}
		}
	}
	return arc;
}