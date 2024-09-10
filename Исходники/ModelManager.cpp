/*
=================
idRenderModelManagerLocal::FindSkeletalMeshes
=================
*/
void idRenderModelManagerLocal::FindSkeletalMeshes( idList<idStr> &skeletalMeshes ) {
	const idDecl *decl;

	skeletalMeshes.Clear();

	for(int i = 0; i < declManager->GetNumDecls( DECL_MODELDEF ); i++)
	{
		decl = declManager->DeclByIndex( DECL_MODELDEF, i, false );

		// This probley isn't the best way to do this, just check to see if the decl def has the skeletal model extension.
		char *text = (char *)_alloca( decl->GetTextLength() + 1 );
		decl->GetText( text );
		if(!strstr(text, ".md5mesh"))
		{
			_resetstkoflw();
			continue;
		}

		_resetstkoflw();

		skeletalMeshes.Append( decl->GetName() );
	}
}