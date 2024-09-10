Block * SimulatedDisk::readBlock(Block::number n, Block::flushInterval i) {
    FILE * discoFofinho = fopen(fileName, "rb");
    fseek(discoFofinho, n * blockSize, SEEK_SET);

    unsigned char * data = new unsigned char[blockSize];

    fread(data, 1, blockSize, discoFofinho);
    fclose(discoFofinho);

    return Storage::constructBlock(data, blockSize, n, i);
}