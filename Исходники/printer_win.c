static void printer_win_close_printjob(rdpPrintJob* printjob)
{
    rdpWinPrintJob* win_printjob = (rdpWinPrintJob*)printjob;

    DEBUG_WINPR("");

    if ( ! EndPagePrinter( ((rdpWinPrinter*)printjob->printer)->hPrinter ) )
        DEBUG_WINPR("EndPagePrinter failed");;
    if ( ! ClosePrinter( ((rdpWinPrinter*)printjob->printer)->hPrinter ) )
        DEBUG_WINPR("ClosePrinter failed");;

    ((rdpWinPrinter*)printjob->printer)->printjob = NULL;
    free(win_printjob) ;
}