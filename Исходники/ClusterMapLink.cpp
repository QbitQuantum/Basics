ClusterMapLink::ClusterMapLink(GUID dest, GUID src) {

    UuidCreate(&UUID_inst);
    UuidCopy(&SourceClusterMapUUID,&src);
    UuidCopy(&DestinationClusterMapUUID,&dest);

}