void CDialogSound::OnBtnEdit()
{
	const idDecl *decl = declManager->FindDeclWithoutParsing( DECL_SOUND, strShader, false );

	if ( decl ) {
		DialogDeclEditor *declEditor;

		declEditor = new DialogDeclEditor;
		declEditor->Create( IDD_DIALOG_DECLEDITOR, GetParent() );
		declEditor->LoadDecl( const_cast<idDecl *>( decl ) );
		declEditor->ShowWindow( SW_SHOW );
		declEditor->SetFocus();
	}
}