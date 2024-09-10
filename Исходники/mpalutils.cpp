/**
 * Destructor
 */
RMRes::~RMRes() {
    if (_h != NULL) {
        globalUnlock(_h);
        globalFree(_h);
    }
}