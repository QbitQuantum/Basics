// private
Cvar::Cvar() {
	cvars[name] = this;

	SetFlags( CVAR_NONE );
	modified = false;
}