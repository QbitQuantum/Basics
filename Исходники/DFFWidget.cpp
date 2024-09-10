void DFFWidget::reloadHighLevelFile()
{
	setCurrentGeometry(NULL);

	if (frameModel)
		delete frameModel;
	if (geomModel)
		delete geomModel;
	if (mesh)
		delete mesh;

	DFFLoader dff;

	File file = dfile->getFile();

	try {
		mesh = dff.loadMesh(file);
		setEnabled(true);
	} catch (DFFException ex) {
		System::getInstance()->log(LogEntry::error(QString(tr("Error opening the DFF file: %1"))
				.arg(ex.getMessage().get()), &ex));
		mesh = NULL;
		setEnabled(false);
		//ui.hlWidget->setEnabled(false);
		//ui.tabWidget->setTabEnabled(ui.tabWidget->indexOf(ui.hlWidget), false);
	}

	// Load the frame tree
	frameModel = new DFFFrameItemModel(mesh);
	ui.frameTree->setModel(frameModel);

	connect(ui.frameTree->selectionModel(), SIGNAL(currentChanged(const QModelIndex&, const QModelIndex&)),
			this, SLOT(frameSelected(const QModelIndex&, const QModelIndex&)));

	System* sys = System::getInstance();

	DFFMesh::GeometryIterator git;

	if (mesh) {
		geomModel = new DFFGeometryItemModel(mesh);
		ui.geometryTree->setModel(geomModel);

		renderWidget->displayMesh(mesh);

		connect(ui.geometryTree->selectionModel(), SIGNAL(currentChanged(const QModelIndex&, const QModelIndex&)),
				this, SLOT(geometryTreeItemSelected(const QModelIndex&, const QModelIndex&)));

		connect(geomModel, SIGNAL(geometryDisplayStateChanged(DFFGeometry*, bool)), this,
				SLOT(geometryDisplayStateChanged(DFFGeometry*, bool)));
		connect(geomModel, SIGNAL(geometryPartDisplayStateChanged(DFFGeometryPart*, bool)), this,
				SLOT(geometryPartDisplayStateChanged(DFFGeometryPart*, bool)));

		// Search for the mesh texture
		char* meshName = new char[file.getPath().getFileName().length() + 1];
		strtolower(meshName, file.getPath().getFileName().get());
		meshName[strlen(meshName)-4] = '\0';

		SystemQuery query("FindMeshTextures");
		query["meshName"] = meshName;

		QList<SystemQueryResult> results = sys->sendSystemQuery(query);

		QStringList texes;

		for (unsigned int i = 0 ; i < results.size() ; i++) {
			SystemQueryResult res = results[i];
			QStringList subTexes = res["textures"].toStringList();

			texes.append(subTexes);
		}

		for (QStringList::iterator it = texes.begin() ; it != texes.end() ; it++) {
			QString tex = *it;
			ui.texSourceBox->addItem(tex, false);
		}

		if (texes.size() > 0)
			texSrcChanged(0);

		delete[] meshName;
	}
}