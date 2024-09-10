void OverlayAnalysis::PostDrawMultiGraph(GraphName graphName, TMultiGraph *pMultiGraph) const
{
    if(NULL == pMultiGraph)
        return;

    // base customize
    pMultiGraph->GetXaxis()->SetTitle("Distance between showers [cm]");
    pMultiGraph->GetXaxis()->SetLabelFont(42);
    pMultiGraph->GetXaxis()->SetTitleSize(0.05);
    pMultiGraph->GetXaxis()->SetTitleOffset(1.);
    pMultiGraph->GetXaxis()->SetTitleFont(42);
    pMultiGraph->GetXaxis()->SetRangeUser(std::max(static_cast<int>(m_startDistance) - 5, 0), m_endDistance + 5);

    pMultiGraph->GetYaxis()->SetTitle("");
    pMultiGraph->GetYaxis()->SetLabelFont(42);
    pMultiGraph->GetYaxis()->SetTitleSize(0.045);
    pMultiGraph->GetYaxis()->SetTitleOffset(1.3);
    pMultiGraph->GetYaxis()->SetTitleFont(42);
    pMultiGraph->GetYaxis()->SetLabelSize(0.035);

    TPaveText *pt = new TPaveText(0.3, 0.2, 0.93, 0.3, "tbNDC");
    pt->SetTextSize(0.05);
    pt->SetTextColor(kGray+2);
    pt->SetFillColor(0);
    pt->SetLineWidth(0);
    pt->SetBorderSize(0);
    pt->AddText("CALICE SDHCAL");
    pt->SetTextFont(62);
    pt->Draw();

    // plot per plot customize
    switch(graphName)
    {
    case N_PFOS:
        pMultiGraph->GetYaxis()->SetTitle("<N_{pfos}>");
        pMultiGraph->GetYaxis()->SetRangeUser(1, 3);
        break;
    case NEUTRAL_PURITY:
        pMultiGraph->GetYaxis()->SetTitle("#rho_{neutral}");
        pMultiGraph->GetYaxis()->SetRangeUser(0, 1);
        break;
    case NEUTRAL_EFFICIENCY:
        pMultiGraph->GetYaxis()->SetTitle("#varepsilon_{neutral}");
        pMultiGraph->GetYaxis()->SetRangeUser(0, 1);
        break;
    case NEUTRAL_RECOVER_PROBA:
        pMultiGraph->GetYaxis()->SetTitle("P_{n>0}");
        pMultiGraph->GetYaxis()->SetRangeUser(0, 1);
        break;
    case NEUTRAL_ENERGY_DIFFERENCE_EFFICIENT:
        pMultiGraph->GetYaxis()->SetTitle("<E_{n,rec} - E_{n,meas}>, n>0");
        pMultiGraph->GetYaxis()->SetRangeUser(-5, 5);
        break;
    }
}