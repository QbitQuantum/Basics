Status DurableViewCatalogImpl::iterate(OperationContext* opCtx, Callback callback) {
    dassert(opCtx->lockState()->isDbLockedForMode(_db->name(), MODE_IS) ||
            opCtx->lockState()->isDbLockedForMode(_db->name(), MODE_IX));
    Collection* systemViews = _db->getCollection(opCtx, _db->getSystemViewsName());
    if (!systemViews)
        return Status::OK();

    Lock::CollectionLock lk(opCtx->lockState(), _db->getSystemViewsName(), MODE_IS);
    auto cursor = systemViews->getCursor(opCtx);
    while (auto record = cursor->next()) {
        RecordData& data = record->data;

        // Check the document is valid BSON, with only the expected fields.
        // Use the latest BSON validation version. Existing view definitions are allowed to contain
        // decimal data even if decimal is disabled.
        fassert(40224, validateBSON(data.data(), data.size(), BSONVersion::kLatest));
        BSONObj viewDef = data.toBson();

        // Check read definitions for correct structure, and refuse reading past invalid
        // definitions. Ignore any further view definitions.
        bool valid = true;
        for (const BSONElement& e : viewDef) {
            std::string name(e.fieldName());
            valid &= name == "_id" || name == "viewOn" || name == "pipeline" || name == "collation";
        }

        const auto viewName = viewDef["_id"].str();
        const auto viewNameIsValid = NamespaceString::validCollectionComponent(viewName) &&
            NamespaceString::validDBName(nsToDatabaseSubstring(viewName));
        valid &= viewNameIsValid;

        // Only perform validation via NamespaceString if the collection name has been determined to
        // be valid. If not valid then the NamespaceString constructor will uassert.
        if (viewNameIsValid) {
            NamespaceString viewNss(viewName);
            valid &= viewNss.isValid() && viewNss.db() == _db->name();
        }

        valid &= NamespaceString::validCollectionName(viewDef["viewOn"].str());

        const bool hasPipeline = viewDef.hasField("pipeline");
        valid &= hasPipeline;
        if (hasPipeline) {
            valid &= viewDef["pipeline"].type() == mongo::Array;
        }

        valid &=
            (!viewDef.hasField("collation") || viewDef["collation"].type() == BSONType::Object);

        if (!valid) {
            return {ErrorCodes::InvalidViewDefinition,
                    str::stream() << "found invalid view definition " << viewDef["_id"]
                                  << " while reading '"
                                  << _db->getSystemViewsName()
                                  << "'"};
        }

        Status callbackStatus = callback(viewDef);
        if (!callbackStatus.isOK()) {
            return callbackStatus;
        }
    }
    return Status::OK();
}