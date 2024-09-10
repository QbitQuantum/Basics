int UUIDCompare(UUID const &A, UUID const &B) {
    return UUIDCompare(*((Flatten_UUID*)&A), *((Flatten_UUID*)&B));
}