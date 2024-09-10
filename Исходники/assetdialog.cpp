void AssetDialog::create()
{
	Database::current()->beginTransaction( "Create/Edit Asset" );

	QString name = mAssetNameEdit->text();
	if( name.isEmpty() ){
		ResinError::nameEmpty(this, "Asset Name");
		return;
	}

	AssetTemplate at = mAssetTemplateCombo->assetTemplate();

	Element e;
	if( mAsset.isRecord() ) {
		e = mAsset;

 	} else {
		if( mParent.project().isRecord() && Asset::recordByProjectAndName( mParent.project(), name ).isRecord() ){
			ResinError::nameTaken(this, "Asset Name");
			return;
		}

		AssetType assetType = AssetType::recordByName( mTypeCombo->currentText() );

		if( at.isRecord() && mAssetTemplatesEnabled && mCreateAssetTemplates ) {
			RecordList rl;
			e = Element::createFromTemplate( at, rl );
			ElementList el( rl );
			el.setProjects( mParent.project() );
			el.commit();
		} else {
			e = assetType.construct();
		}
		
		e.setProject( mParent.project() );
		e.setParent( mParent );
		e.setElementStatus( ElementStatus::recordByName( "New" ) );
		mCreated += e;
	}

	if( mAssetTemplatesEnabled )
		e.setAssetTemplate( at );

	{
		QVariant v(QVariant::Bool);
		Qt::CheckState cs = mAllowTimeSheetsCheck->checkState();
		if( cs != Qt::PartiallyChecked )
			v = QVariant( cs == Qt::Checked );
		e.setValue( "allowTime", v );
	}

	bool ipc = ( e.isRecord() && e.name() != name );
	e.setName( name );

	if( mPathTemplatesEnabled && e.pathTemplate() != mPathTemplateCombo->pathTemplate() ) {
		ipc = true;
		e.setPathTemplate( mPathTemplateCombo->pathTemplate() );
	}

	if( ipc )
		Element::invalidatePathCache();

	e.commit();

	Database::current()->commitTransaction();
}