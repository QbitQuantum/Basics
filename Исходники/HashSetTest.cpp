static void testSetCopy()
{
	// Add 1000..1999 to a HashSet.
	HashSet<Uptr> a;
	for(Uptr i = 0;i < 1000;++i)
	{
		a.add(i + 1000);
	}

	// Copy the set to a new HashSet.
	HashSet<Uptr> b {a};

	// Test that both the new and old HashSet contain the expected numbers.
	for(Uptr i = 0;i < 1000;++i)
	{
		errorUnless(!a.contains(i));
		errorUnless(a.contains(i + 1000));
		errorUnless(!a.contains(i + 2000));
		
		errorUnless(!b.contains(i));
		errorUnless(b.contains(i + 1000));
		errorUnless(!b.contains(i + 2000));
	}
	
	// Test copying a set from itself.
	b = b;
	
	// Test that the set wasn't changed by the copy-to-self.
	for(Uptr i = 0;i < 1000;++i)
	{
		errorUnless(!b.contains(i));
		errorUnless(b.contains(i + 1000));
		errorUnless(!b.contains(i + 2000));
	}

	// Test removing an element from the set.
	b.remove(1000);
	errorUnless(a.contains(1000));
	errorUnless(!b.contains(1000));
}