void ModelsimGenerator::parseFiles( QSharedPointer<Component> component, const QString& viewName ) {

	Q_ASSERT_X(component, "ModelsimGenerator::parseFiles",
		"Null component-pointer given as parameter");

	// inform user that component is being processed
	emit noticeMessage(tr("Processing view %1 of component %2:%3:%4:%5").arg(
		viewName).arg(
		component->getVlnv()->getVendor()).arg(
		component->getVlnv()->getLibrary()).arg(
		component->getVlnv()->getName()).arg(
		component->getVlnv()->getVersion()));

	// pointer to the named view under given component
	View* view = component->findView(viewName);

	// if view was not found
	if (!view) {

		// if component does not contain any views
		if (component->viewCount() == 0) {
			emit noticeMessage(tr("Component %1 didn't contain any views, "
				"adding all found RTL-files from component file sets.").arg(
				component->getVlnv()->getName()));

			parseBlindFileSet(component);
			viewName_ = viewName;
			return;
		}

		// component did contain views but not the specified view
		else {
			emit errorMessage(tr("View %1 not found within component %2").arg(
				viewName).arg(component->getVlnv()->getName()));
			return;
		}
	}

	// if the view was found but was not hierarchical
	if (view && !view->isHierarchical()) {

		// ask which file sets are included in the view
		QStringList fileSets = view->getFileSetRefs();

		// parse the file sets from the component and add them to the list of files
		parseFileSets(component, fileSets);
	}

	// view was found and was hierarchical
	else if (view && view->isHierarchical()) {

		VLNV designVLNV;
		QSharedPointer<Design> design;

		VLNV desConfVLNV;
		QSharedPointer<DesignConfiguration> designConf;

		VLNV vlnv = view->getHierarchyRef();

		// if the specified vlnv is not found within library
		if (!handler_->contains(vlnv)) {
			emit errorMessage(tr("Hierarchy reference %1:%2:%3:%4 referenced "
				"within view %5 in component %6 was not found in the library."
				" Stopping generation.").arg(
				vlnv.getVendor()).arg(
				vlnv.getLibrary()).arg(
				vlnv.getName()).arg(
				vlnv.getVersion()).arg(
				viewName).arg(
				component->getVlnv()->getName()));
			return;
		}

		// get the real type of the referenced document
		vlnv.setType(handler_->getDocumentType(vlnv));

		// if component contained reference to a design configuration
		if (vlnv.getType() == VLNV::DESIGNCONFIGURATION) {
			
			// parse the design configuration
			desConfVLNV = vlnv;
			QSharedPointer<LibraryComponent> libComp = handler_->getModel(desConfVLNV);
			designConf = libComp.staticCast<DesignConfiguration>();
			
			// find the referenced design
			designVLNV = designConf->getDesignRef();
		}

		// if component contained direct reference to a design 
		else if (vlnv.getType() == VLNV::DESIGN) {
			designVLNV = vlnv;
		}
		// if item was some other type
		else {
			emit errorMessage(tr("Item %1:%2:%3:%4 was not neither design or "
				"design configuration, stopping generation.").arg(
				vlnv.getVendor()).arg(
				vlnv.getLibrary()).arg(
				vlnv.getName()).arg(
				vlnv.getVersion()));
			return;
		}

		// if design does not exist
		if (!handler_->contains(designVLNV)) {
			emit errorMessage(tr("Design %1:%2:%3:%4 referenced within "
				"design configuration %5 was not found within library. "
				"Stopping generation.").arg(
				designVLNV.getVendor()).arg(
				designVLNV.getLibrary()).arg(
				designVLNV.getName()).arg(
				designVLNV.getVersion()).arg(
				desConfVLNV.getName()));
			return;
		}

		// parse the design
		QSharedPointer<LibraryComponent> libComp = handler_->getModel(designVLNV);
		design = libComp.staticCast<Design>();

		// read the design and it's component instances
		readDesign(design, designConf);

		// if this view contains a reference to a view that contains component's
		// top level implementation
		QString topLevelView = view->getTopLevelView();
		if (!topLevelView.isEmpty()) {
			parseFiles(component, topLevelView);
		}
	}
	viewName_ = viewName;
	sourceXml_ = handler_->getPath(*component->getVlnv());
}