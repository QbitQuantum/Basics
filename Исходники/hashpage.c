/*
 *	_hash_init_metabuffer() -- Initialize the metadata page of a hash index.
 */
void
_hash_init_metabuffer(Buffer buf, double num_tuples, RegProcedure procid,
					  uint16 ffactor, bool initpage)
{
	HashMetaPage metap;
	HashPageOpaque pageopaque;
	Page		page;
	double		dnumbuckets;
	uint32		num_buckets;
	uint32		spare_index;
	uint32		i;

	/*
	 * Choose the number of initial bucket pages to match the fill factor
	 * given the estimated number of tuples.  We round up the result to the
	 * total number of buckets which has to be allocated before using its
	 * _hashm_spare element. However always force at least 2 bucket pages. The
	 * upper limit is determined by considerations explained in
	 * _hash_expandtable().
	 */
	dnumbuckets = num_tuples / ffactor;
	if (dnumbuckets <= 2.0)
		num_buckets = 2;
	else if (dnumbuckets >= (double) 0x40000000)
		num_buckets = 0x40000000;
	else
		num_buckets = _hash_get_totalbuckets(_hash_spareindex(dnumbuckets));

	spare_index = _hash_spareindex(num_buckets);
	Assert(spare_index < HASH_MAX_SPLITPOINTS);

	page = BufferGetPage(buf);
	if (initpage)
		_hash_pageinit(page, BufferGetPageSize(buf));

	pageopaque = (HashPageOpaque) PageGetSpecialPointer(page);
	pageopaque->hasho_prevblkno = InvalidBlockNumber;
	pageopaque->hasho_nextblkno = InvalidBlockNumber;
	pageopaque->hasho_bucket = -1;
	pageopaque->hasho_flag = LH_META_PAGE;
	pageopaque->hasho_page_id = HASHO_PAGE_ID;

	metap = HashPageGetMeta(page);

	metap->hashm_magic = HASH_MAGIC;
	metap->hashm_version = HASH_VERSION;
	metap->hashm_ntuples = 0;
	metap->hashm_nmaps = 0;
	metap->hashm_ffactor = ffactor;
	metap->hashm_bsize = HashGetMaxBitmapSize(page);
	/* find largest bitmap array size that will fit in page size */
	for (i = _hash_log2(metap->hashm_bsize); i > 0; --i)
	{
		if ((1 << i) <= metap->hashm_bsize)
			break;
	}
	Assert(i > 0);
	metap->hashm_bmsize = 1 << i;
	metap->hashm_bmshift = i + BYTE_TO_BIT;
	Assert((1 << BMPG_SHIFT(metap)) == (BMPG_MASK(metap) + 1));

	/*
	 * Label the index with its primary hash support function's OID.  This is
	 * pretty useless for normal operation (in fact, hashm_procid is not used
	 * anywhere), but it might be handy for forensic purposes so we keep it.
	 */
	metap->hashm_procid = procid;

	/*
	 * We initialize the index with N buckets, 0 .. N-1, occupying physical
	 * blocks 1 to N.  The first freespace bitmap page is in block N+1.
	 */
	metap->hashm_maxbucket = num_buckets - 1;

	/*
	 * Set highmask as next immediate ((2 ^ x) - 1), which should be
	 * sufficient to cover num_buckets.
	 */
	metap->hashm_highmask = (1 << (_hash_log2(num_buckets + 1))) - 1;
	metap->hashm_lowmask = (metap->hashm_highmask >> 1);

	MemSet(metap->hashm_spares, 0, sizeof(metap->hashm_spares));
	MemSet(metap->hashm_mapp, 0, sizeof(metap->hashm_mapp));

	/* Set up mapping for one spare page after the initial splitpoints */
	metap->hashm_spares[spare_index] = 1;
	metap->hashm_ovflpoint = spare_index;
	metap->hashm_firstfree = 0;

	/*
	 * Set pd_lower just past the end of the metadata.  This is to log full
	 * page image of metapage in xloginsert.c.
	 */
	((PageHeader) page)->pd_lower =
		((char *) metap + sizeof(HashMetaPageData)) - (char *) page;
}