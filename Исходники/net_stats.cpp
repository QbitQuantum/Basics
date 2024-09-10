void DAILY_XFER_HISTORY::write_scheduler_request(MIOFILE& mf, int ndays) {
    double up, down;
    totals(ndays, up, down);
    mf.printf(
        "<daily_xfer_history>\n"
        "   <ndays>%d</ndays>\n"
        "   <up>%f</up>\n"
        "   <down>%f</down>\n"
        "</daily_xfer_history>\n",
        ndays, up, down
    );
}