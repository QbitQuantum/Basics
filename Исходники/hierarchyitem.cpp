HierarchyItem::HierarchyItem(LibraryInterface* handler,
							 HierarchyItem* parent, 
							 const VLNV& vlnv,
							 KactusAttribute::Implementation implementation,
							 const QString& viewName):
QObject(parent),
component_(),
busDef_(),
absDef_(),
comDef_(),
apiDef_(),
design_(),
handler_(handler),
childItems_(),
parentItem_(parent),
isValid_(true),
isDuplicate_(false),
type_(HierarchyItem::ROOT),
instanceCount_(),
viewName_() {

	Q_ASSERT_X(handler, "HierarchyItem constructor",
		"Null LibraryInterface pointer given as parameter");
	Q_ASSERT_X(parent, "HierarchyItem constructor",
		"Null parent pointer given as parameter");

	connect(this, SIGNAL(errorMessage(const QString&)),
		parent, SIGNAL(errorMessage(const QString&)), Qt::UniqueConnection);
	connect(this, SIGNAL(noticeMessage(const QString&)),
		parent, SIGNAL(noticeMessage(const QString&)), Qt::UniqueConnection);

	Q_ASSERT(handler->contains(vlnv));

	if (handler_->getDocumentType(vlnv) == VLNV::COMPONENT) {
		parseComponent(vlnv);
	}
	else if (handler_->getDocumentType(vlnv) == VLNV::BUSDEFINITION) {
		parseBusDefinition(vlnv);
	}
	else if (handler_->getDocumentType(vlnv) == VLNV::ABSTRACTIONDEFINITION) {
		parseAbsDefinition(vlnv);
	}
    else if (handler_->getDocumentType(vlnv) == VLNV::COMDEFINITION) {
        parseComDefinition(vlnv);
    }
    else if (handler_->getDocumentType(vlnv) == VLNV::APIDEFINITION) {
        parseApiDefinition(vlnv);
    }
	else if (handler_->getDocumentType(vlnv) == VLNV::DESIGN) {
		parseDesign(vlnv, implementation, viewName);
	}
	else {
		emit errorMessage(tr("VLNV %1:%2:%3:%4 was not for supported item").arg(
			vlnv.getVendor()).arg(
			vlnv.getLibrary()).arg(
			vlnv.getName()).arg(
			vlnv.getVersion()));
		isValid_ = false;
		return;
	}
}