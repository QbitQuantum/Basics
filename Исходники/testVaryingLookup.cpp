void
testVaryingLookup ()
{
    try
    {
	SimdInterpreter interp;
	interp.loadModule ("testVaryingLookup");

	cout << "Testing table lookups with varying data" << endl;

	testLookup1D (interp);
	testLookupCubic1D (interp);
	testLookup3D (interp);
	testInterpolate1D (interp);
	testInterpolateCubic1D (interp);

	cout << "ok\n" << endl;
    }
    catch (const std::exception &e)
    {
	cerr << "ERROR -- caught exception: " << endl << e.what() << endl;
	assert (false);
    }
}