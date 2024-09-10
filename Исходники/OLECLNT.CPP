void TOleDocWindow::RegisterClientDoc() {
	// Tip for using OleRegisterClientDoc:
	// if the lpszDoc parameter passed to
	// OleRegisterClientDoc is not valid, (lpszPatnName in this case),
	// one can get an OLE_ERROR_ADDRESS error, and the ClientDoc
	// handle will not be valid.

	ret = OleRegisterClientDoc(
			GetApplication()->Name,
			lpszDocName,
			0,
			&lhClientDoc );
	check( ret );
}