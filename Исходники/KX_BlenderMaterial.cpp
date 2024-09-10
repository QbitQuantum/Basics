KX_BlenderMaterial::~KX_BlenderMaterial()
{
	Material *ma = mMaterial->material;
	// Restore Blender material data
	ma->r = mSavedData.r;
	ma->g = mSavedData.g;
	ma->b = mSavedData.b;
	ma->alpha = mSavedData.a;
	ma->specr = mSavedData.specr;
	ma->specg = mSavedData.specg;
	ma->specb = mSavedData.specb;
	ma->spec = mSavedData.spec;
	ma->ref = mSavedData.ref;
	ma->har = mSavedData.hardness;
	ma->emit = mSavedData.emit;

	// cleanup work
	if (mConstructed)
		// clean only if material was actually used
		OnExit();
}