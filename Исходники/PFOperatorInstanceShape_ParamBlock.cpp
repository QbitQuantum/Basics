void PFOperatorInstanceShapeDlgProc::UpdateParticleShapeDlg( HWND hWnd, const Tab<Mesh*>& meshList )
{
	int numVerts, numFaces, numShapes;

	numShapes = meshList.Count();
	numVerts = numFaces = 0;
	if (numShapes > 0) {
		for (int i = 0; i < numShapes; i++) {
			numVerts += meshList[i]->getNumVerts();
			numFaces += meshList[i]->getNumFaces();
		}
		numVerts /= numShapes;
		numFaces /= numShapes;
	}
	
	TSTR buf;
	buf.printf(_T("%d"), numVerts);
	SetDlgItemText( hWnd, IDC_VERTICES, buf );
	buf.printf(_T("%d"), numFaces);
	SetDlgItemText( hWnd, IDC_FACES, buf );
	buf.printf(_T("%d"), numShapes);
	SetDlgItemText( hWnd, IDC_SHAPES, buf );
}