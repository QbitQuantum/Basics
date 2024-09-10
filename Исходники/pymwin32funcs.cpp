BOOL pymImmSetCompositionWindow(HIMC hIMC, COMPOSITIONFORM *lpCompForm) {
	PyMFC_PROLOGUE(pymFormatMessage);
	{
		PyMFCLeavePython lp;
		return ImmSetCompositionWindow(hIMC, lpCompForm);
	}
	PyMFC_EPILOGUE(0);
}