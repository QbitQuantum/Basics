int deviceConnectDisplayGetBufferChange() {
    if (MEMCMP((void *) vvadp.data.bufcomp, (void *) qdcgaGetTextMemAddr, qdcgaVarRagenSize)) {
        MEMCPY((void *) vvadp.data.bufcomp, (void *) qdcgaGetTextMemAddr, qdcgaVarRagenSize);
        return True;
    } else {
        return False;
    }
}