void SpecReader::readSpecification (KeySet const & cks)
{
	KeySet ks (cks);
	Key mp;

	ks.rewind (); // we need old fashioned loop, because it can handle ks.cut during iteration
	for (Key k = ks.next (); k; k = ks.next ())
	{
		// search for mountpoint
		Key m = k.getMeta<const Key> ("mountpoint");
		if (m)
		{
			SpecMountpointReader smr (backends, bbi);
			backends[k] = smr.readMountpointSpecification (ks.cut (k));
		}
	}
}