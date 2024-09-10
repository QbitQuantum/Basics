/**
 * rt_shootray() was told to call this on a hit.
 *
 * This callback routine utilizes the application structure which
 * describes the current state of the raytrace.
 *
 * This callback routine is provided a circular linked list of
 * partitions, each one describing one in and out segment of one
 * region for each region encountered.
 *
 * The 'segs' segment list is unused in this example.
 */
int
hit_voxelize(struct application *ap, struct partition *PartHeadp, struct seg *UNUSED(segs))
{
    struct partition *pp            = PartHeadp->pt_forw;
    struct rayInfo   *voxelHits     = (struct rayInfo*) ap->a_uptr;
    fastf_t           sizeVoxel     = voxelHits->sizeVoxel;
    fastf_t          *fillDistances = voxelHits->fillDistances;

    while (pp != PartHeadp) {
	/**
	 * hitInp, hitOutp are hit structures to save distances where
	 * ray entered and exited the present partition.  hitDistIn,
	 * hitDistOut are the respective distances from the origin of
	 * ray.  voxelNumIn, voxelNumOut are the voxel numbers where
	 * ray entered and exited the present partition.
	 */

	struct hit *hitInp      = pp->pt_inhit;
	struct hit *hitOutp     = pp->pt_outhit;
	fastf_t     hitDistIn   = hitInp->hit_dist - 1.;
	fastf_t     hitDistOut  = hitOutp->hit_dist - 1.;
	int         voxelNumIn  = (int)(hitDistIn / sizeVoxel);
	int         voxelNumOut = (int)(hitDistOut / sizeVoxel);

	if (EQUAL((hitDistOut / sizeVoxel), floor(hitDistOut / sizeVoxel)))
	    voxelNumOut = FMAX(voxelNumIn, voxelNumOut - 1);

	/**
	 * If voxel entered and voxel exited are same then nothing can
	 * be evaluated till we see the next partition too. If not,
	 * evaluate entry voxel. Also, all the intermediate voxels are
	 * in.
	 */
	if (voxelNumIn == voxelNumOut) {
	    fillDistances[voxelNumIn]                                                                     += hitDistOut - hitDistIn;
	    getRegionByName(voxelHits->regionList + voxelNumIn, pp->pt_regionp->reg_name)->regionDistance += hitDistOut - hitDistIn;
	} else {
	    int j;

	    fillDistances[voxelNumIn]                                                                     += (voxelNumIn + 1) * sizeVoxel - hitDistIn;
	    getRegionByName(voxelHits->regionList + voxelNumIn, pp->pt_regionp->reg_name)->regionDistance += (voxelNumIn + 1) * sizeVoxel - hitDistIn;

	    for (j = voxelNumIn + 1; j < voxelNumOut; ++j) {
		fillDistances[j]                                                                     += sizeVoxel;
		getRegionByName(voxelHits->regionList + j, pp->pt_regionp->reg_name)->regionDistance += sizeVoxel;
	    }

	    fillDistances[voxelNumOut]                                                                     += hitDistOut - (voxelNumOut * sizeVoxel);
	    getRegionByName(voxelHits->regionList + voxelNumOut, pp->pt_regionp->reg_name)->regionDistance += hitDistOut - (voxelNumOut * sizeVoxel);
	}

	pp = pp->pt_forw;
    }

    return 0;

}