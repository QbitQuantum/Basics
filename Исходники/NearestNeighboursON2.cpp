void NearestNeighboursON2::getNearestNeighbours(
        const Scan &queryScan,
        unsigned int queryToReferenceMapping[][2],
        double nearestDistances[]) {

    const Scan &refScan = *(this->refScan);
    const unsigned int queryScanSize = queryScan.size(), refScanSize = refScan.size();

    for(unsigned int i = 0; i < queryScanSize; i++) {
        TopValues<2> tv;

        for(unsigned int j = 0; j < refScanSize; j++) {
            double dist =
                    square(refScan[j].getX() - queryScan[i].getX()) +
                    square(refScan[j].getY() - queryScan[i].getY());
            tv.add(dist, j);
        }

        queryToReferenceMapping[i][0] = tv.index(0);
        queryToReferenceMapping[i][1] = tv.index(1);
        nearestDistances[i] = tv.value(0);
    }
}