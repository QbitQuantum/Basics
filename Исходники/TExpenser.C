void TExpenser::drawIncomeTab() {

    // create the income tab
    fIncomeTab = fTab->AddTab("Income");
    fIncomeTab -> SetLayoutManager(new TGHorizontalLayout(fIncomeTab));

    // create table interface
    const unsigned ncolumns =  3;
    TGExpenserTableInterface * income_table = new TGExpenserTableInterface(ncolumns);
    TString columns[ncolumns]={"amount", "description", "date"};
    income_table -> setColumnNames(columns);

    fIncomeXMLParser->selectMainNode();
    fIncomeXMLParser->selectNode("entry");
    vector<expense> incomes;
    while (fIncomeXMLParser->getCurrentNode() != 0) {
        XMLNodePointer_t current_node = fIncomeXMLParser->getCurrentNode();

        fIncomeXMLParser -> selectNode("date");
        TString year = fIncomeXMLParser -> getNodeContent("year");
        TString month = fIncomeXMLParser -> getNodeContent("month");
        fIncomeXMLParser -> setCurrentNode(current_node);

        if (month.Atoi()<10) month="0"+month;

        expense in;
        in.amount = fIncomeXMLParser -> getNodeContent("amount");
        in.description = fIncomeXMLParser -> getNodeContent("description");
        in.date = year+month;
        in.dateForCell = month+"/"+year;
        incomes.push_back(in);

        fIncomeXMLParser->selectNextNode("entry");
    }

    sort(incomes.begin(), incomes.end(), compare);

    for (unsigned i=0; i<incomes.size(); i++) {
        income_table -> addCell (i, incomes[i].amount);
        income_table -> addCell (i, incomes[i].description);
        income_table -> addCell (i, incomes[i].dateForCell);
    }
    unsigned entries = incomes.size();

    // Create the table
    TGTable * fInTable = new TGTable(fIncomeTab, 999, income_table, NROWSTABLE, income_table->GetNColumns());
    fIncomeTab -> AddFrame(fInTable, new TGLayoutHints(kLHintsCenterY,2,2,2,2));

    /*
    TGVerticalFrame *vframe = new TGVerticalFrame(fIncomeTab, 60, 40);
    fIncomeTab -> AddFrame(vframe, new TGLayoutHints(kLHintsCenterX,2,2,2,2));

    // year selector
    TDatime time;
    TGComboBox * income_tab_year = new TGComboBox(vframe);
    for (unsigned i = FIRST_YEAR; i <= LAST_YEAR; i++) {
        income_tab_year->AddEntry(toStr(i), i+1-FIRST_YEAR);
    }
    income_tab_year->Resize(100, 20);
    income_tab_year->Select(time.GetYear()-FIRST_YEAR+1);
    vframe->AddFrame(income_tab_year, new TGLayoutHints(kLHintsLeft,5,10,5,5));

    TGTextButton * apply_button = new TGTextButton(vframe,"&Apply");
    apply_button -> Connect("Clicked()", "TExpenser", this, "calculate_monthly()");
    vframe -> AddFrame(apply_button, new TGLayoutHints(kLHintsLeft,5,5,3,4));
    */
}