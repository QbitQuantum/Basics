void Ave::start(Context &context) {
    using std::ceil;

    geoSegment = &context.getSegment(Constants::SEGMENT_GEO);
    sourceSegment = &context.getSegment(Constants::SEGMENT_SYN_COLLOCATED);

    getAuxdataProvider(context, Constants::AUX_ID_SYCP).getUByte("ave_square", averagingFactor);

    const Grid &sourceGrid = sourceSegment->getGrid();
    //const size_t sizeL = sourceGrid.getSizeL() / averagingFactor;
    const size_t sizeM = ceil(sourceGrid.getSizeM() / double(averagingFactor));
    const size_t sizeK = sourceGrid.getSizeK();
    const size_t maxL = ceil((sourceGrid.getMaxL() - sourceGrid.getMinL() + 1) / double(averagingFactor)) - 1;
    targetSegment = &context.addSwathSegment(Constants::SEGMENT_SYN_AVERAGED, maxL + 1, sizeM, sizeK, 0, maxL);

    addVariables(context);
}