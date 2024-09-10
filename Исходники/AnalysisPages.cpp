	void CAnalysisHowPage::SetComputationKind(short kind)
	{
		ASSERT(kind >= 0 && kind < CAnalysisComputation::NB_KIND);
		CheckRadioButton(IDC_STATISTIC, IDC_EVENT, IDC_STATISTIC + kind);
	}