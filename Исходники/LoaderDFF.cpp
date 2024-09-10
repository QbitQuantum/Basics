void LoaderDFF::readMaterialList(GeometryPtr &geom, const RWBStream &stream) {
    auto listStream = stream.getInnerStream();

    auto listStructID = listStream.getNextChunk();
    if (listStructID != CHUNK_STRUCT) {
        throw DFFLoaderException("MaterialList missing struct chunk");
    }

    unsigned int numMaterials = *(std::uint32_t *)listStream.getCursor();

    geom->materials.reserve(numMaterials);

    RWBStream::ChunkID chunkID;
    while ((chunkID = listStream.getNextChunk())) {
        switch (chunkID) {
            case CHUNK_MATERIAL:
                readMaterial(geom, listStream);
                break;
            default:
                break;
        }
    }
}