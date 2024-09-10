const std::pair<URI, prop_id_t>& 
StoreClient::getParent(class_id_t child_class,
                       const URI& child) {
    Region* r = store->getRegion(child_class);
    return r->getParent(child_class, child);
}