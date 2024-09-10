/* Update the state of the REGISTRY.tcl component according to the
 * Extension and TclTk features. REGISTRY.tcl must be installed
 * if both features are installed, and must be absent otherwise.
 */
UINT __declspec(dllexport) __stdcall UpdateEditIDLE(MSIHANDLE hInstall)
{
	INSTALLSTATE ext_old, ext_new, tcl_old, tcl_new, reg_new;
	UINT result;

	result = MsiGetFeatureStateA(hInstall, "Extensions", &ext_old, &ext_new);
	if (result != ERROR_SUCCESS)
		return result;
	result = MsiGetFeatureStateA(hInstall, "TclTk", &tcl_old, &tcl_new);
	if (result != ERROR_SUCCESS)
		return result;

	/* If the current state is Absent, and the user did not select
	   the feature in the UI, Installer apparently sets the "selected"
	   state to unknown. Update it to the current value, then. */
	if (ext_new == INSTALLSTATE_UNKNOWN)
		ext_new = ext_old;
	if (tcl_new == INSTALLSTATE_UNKNOWN)
		tcl_new = tcl_old;

	// XXX consider current state of REGISTRY.tcl?
	if (((tcl_new == INSTALLSTATE_LOCAL) ||
		 (tcl_new == INSTALLSTATE_SOURCE) ||
		 (tcl_new == INSTALLSTATE_DEFAULT)) &&
		((ext_new == INSTALLSTATE_LOCAL) ||
		 (ext_new == INSTALLSTATE_SOURCE) ||
		 (ext_new == INSTALLSTATE_DEFAULT))) {
		reg_new = INSTALLSTATE_SOURCE;
	} else { 
		reg_new = INSTALLSTATE_ABSENT;
	}
	result = MsiSetComponentStateA(hInstall, "REGISTRY.tcl", reg_new);
	return result;
}