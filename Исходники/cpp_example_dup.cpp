//! [ksDeepCopy]
kdb::KeySet ksDeepCopy (kdb::KeySet orig)
{
	kdb::KeySet deepCopy;
	orig.rewind ();
	while (orig.next ())
	{
		deepCopy.append (orig.current ().dup ());
	}
	return deepCopy;
}