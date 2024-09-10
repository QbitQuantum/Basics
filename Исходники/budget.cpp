wxString mmReportBudget::AdjustYearValues(int& day, int& month, long year, wxString yearStr)
{
    if ((yearStr.length() < 5)) {
        if (mmIniOptions::instance().budgetFinancialYears_) {
            GetFinancialYearValues(day, month);
            yearStr = wxString::Format(_("Financial Year: %s - %i"), yearStr, (year + 1));
        } else
            yearStr = wxString::Format(_("Year: %s"), yearStr);
    } else {
        yearStr = wxString::Format(_("Month: %s"), yearStr);
    }

    return yearStr;
}