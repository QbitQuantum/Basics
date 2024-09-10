static void fe_mt_tsx_unlock_x86rtm(fe_mt_tsx *tsx) {
    if(_xtest()) {
        _xend();
        return;
    }
    fe_mt_tsx_unlock_fallback(tsx);
}