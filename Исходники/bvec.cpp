void BitVector::rleANDnon(BitVector& bv) {
    // decompress
    // run nonANDnon
    decompress();
    nonANDnon(bv);
}