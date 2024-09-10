//==========================================================================
//
// Collects all sectors that might need a fake floor
//
//==========================================================================
void FDrawInfo::AddLowerMissingTexture(side_t * side, subsector_t *sub, fixed_t backheight)
{
	sector_t *backsec = side->segs[0]->backsector;
	if (!backsec) return;
	if (backsec->transdoor)
	{
		// Transparent door hacks alter the backsector's floor height so we should not
		// process the missing texture for them.
		if (backsec->transdoorheight == backsec->GetPlaneTexZ(sector_t::floor)) return;
	}

	totalms.Clock();
	// we need to check all segs of this sidedef
	for(int i=0; i<side->numsegs; i++)
	{
		seg_t *seg = side->segs[i];

		// we need find the seg belonging to the passed subsector
		if (seg->Subsector == sub)
		{
			MissingTextureInfo mti = {};
			MissingSegInfo msi;

			subsector_t * sub = seg->Subsector;

			if (sub->render_sector != sub->sector || seg->frontsector != sub->sector) 
			{
				totalms.Unclock();
				return;
			}

			// Ignore FF_FIX's because they are designed to abuse missing textures
			if (seg->backsector->e->XFloor.ffloors.Size() && seg->backsector->e->XFloor.ffloors[0]->flags&FF_FIX)
			{
				totalms.Unclock();
				return;
			}

			//@sync-hack
			for(unsigned int i=0;i<MissingLowerTextures.Size();i++)
			{
				if (MissingLowerTextures[i].sub == sub)
				{
					// Use the highest adjoining height to draw a fake floor if necessary
					if (backheight > MissingLowerTextures[i].planez) 
					{
						MissingLowerTextures[i].planez = backheight;
						MissingLowerTextures[i].seg = seg;
					}

					msi.MTI_Index = i;
					msi.seg=seg;
					MissingLowerSegs.Push(msi);
					totalms.Unclock();
					return;
				}
			}
			mti.seg=seg;
			mti.sub = sub;
			mti.planez=backheight;
			msi.MTI_Index = MissingLowerTextures.Push(mti);
			msi.seg=seg;
			MissingLowerSegs.Push(msi);
		}
	}
	totalms.Unclock();
}