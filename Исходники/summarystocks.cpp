wxString mmReportSummaryStocks::getHTMLText()
{
    RefreshData();
    mmHTMLBuilder hb;
    hb.init();
    hb.addDivContainer();
    hb.addHeader(2, m_title);
    hb.addDateNow();
    hb.addLineBreak();

    hb.addDivRow();
    hb.addDivCol17_67();

    for (const auto& acct : m_stocks)
    {
        const Model_Account::Data* account = Model_Account::instance().get(acct.id);
        const Model_Currency::Data* currency = Model_Account::currency(account);
        hb.addHeader(3, acct.name);

        hb.startTable();
        display_header(hb);

        hb.startTbody();
        for (const auto& entry : acct.data)
        {
            hb.startTableRow();
            hb.addTableCell(entry.name);
            hb.addTableCell(entry.symbol);
            hb.addTableCellDate(entry.date);
            hb.addTableCell(Model_Account::toString(entry.qty, account, floor(entry.qty) ? 0 : 4), true);
            hb.addCurrencyCell(entry.purchase, currency, 4);
            hb.addCurrencyCell(entry.current, currency, 4);
            hb.addCurrencyCell(entry.commission, currency, 4);
            hb.addCurrencyCell(entry.gainloss, currency);
            hb.addCurrencyCell(entry.value, currency);
            hb.endTableRow();
        }
        hb.endTbody();

        hb.startTfoot();
        hb.startTotalTableRow();
        hb.addTableCell(_("Total:"));
        hb.addEmptyTableCell(6);
        hb.addCurrencyCell(acct.gainloss, currency);
        hb.addCurrencyCell(acct.total, currency);
        hb.endTableRow();
        hb.endTfoot();
        hb.endTable();
    }

    hb.addDivCol17_67();
    hb.addHeader(3, _("Grand Total:"));
    hb.startTable();

    hb.startThead();
    hb.startTableRow();
    hb.addTableHeaderCell(_("Gain/Loss"), true);
    hb.addTableHeaderCell(_("Current Value"), true);
    hb.endTableRow();
    hb.endThead();

    hb.startTfoot();
    hb.startTotalTableRow();
    hb.addCurrencyCell(m_gain_loss_sum_total);
    hb.addCurrencyCell(m_stock_balance);
    hb.endTableRow();
    hb.endTfoot();
    hb.endTable();
    hb.endDiv();

    hb.endDiv();
    hb.endDiv();

    hb.endDiv();
    hb.end();

    return hb.getHTMLText();
}