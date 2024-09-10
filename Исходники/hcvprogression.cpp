bool HCVProgression::progress(RandomBin& rb, int age, bool male, bool white, bool lowrisk, HCVStatus& hcvstatus)
{
	hcvcea->record_state(age, hcvstatus);

	if (hcvstatus.infected != HCVStatus::INFECTED || hcvstatus.treatment == HCVStatus::SUCCESS) {
		return false;
	}

	if (hcvstatus.fibrosis == HCVStatus::F0) {
		if ( rb.rand(RandomBin::Progression) <= 1-exp(-1*ProgressionData.rate_remission) ) {
			hcvstatus.fibrosis = HCVStatus::NOFIB;
			hcvstatus.infected = HCVStatus::PREVINFECTED;
			hcvstatus.genotype = HCVStatus::GNONE;
			hcvstatus.treatment = HCVStatus::NOTX;
			hcvstatus.progressor = HCVStatus::PNONE;
			return false;
		}
	}

	if (hcvstatus.progressor == HCVStatus::PROGRESSOR) {
		if (hcvstatus.fibrosis < HCVStatus::F4) {
			int colidx = (male==0)*1;
			double rate = FibrosisProgressionTable.getValue(age, colidx);
			double prob = 1-exp(-1*rate);
			if (rb.rand(RandomBin::Progression) <= prob) {
				if (hcvstatus.fibrosis == HCVStatus::F0) {
					hcvstatus.fibrosis = HCVStatus::F1;
				} else if (hcvstatus.fibrosis == HCVStatus::F1) {
					hcvstatus.fibrosis = HCVStatus::F2;
				} else if (hcvstatus.fibrosis == HCVStatus::F2) {
					hcvstatus.fibrosis = HCVStatus::F3;
				} else if (hcvstatus.fibrosis == HCVStatus::F3) {	
					hcvstatus.fibrosis = HCVStatus::F4;
				}
			}
			return false;
		} else if (hcvstatus.fibrosis == HCVStatus::F4) {
			if ( rb.rand(RandomBin::Progression) <= 1-exp(-1*(ProgressionData.rate_F4_DC + ProgressionData.rate_F4DC_HCC)) ) {
				if ( rb.rand(RandomBin::Progression) < (ProgressionData.rate_F4_DC / (ProgressionData.rate_F4_DC + ProgressionData.rate_F4DC_HCC)) ) {
					hcvstatus.fibrosis = HCVStatus::DC;
				} else {
					hcvstatus.fibrosis = HCVStatus::HCC;
					hcvstatus.HCCtime = 0;
				}
			}
			return false;
		} else if (hcvstatus.fibrosis == HCVStatus::DC) {
			double rate_LT = 0.0;
			if ( age < (ProgressionData.limit_maxLTage_yrs*52) ) {
				rate_LT = ProgressionData.rate_DC_LT;
			}
			
			if ( rb.rand(RandomBin::Progression) <= 1-exp(-1*(ProgressionData.rate_F4DC_HCC + rate_LT)) ) {
				if ( rb.rand(RandomBin::Progression) < (rate_LT / (rate_LT + ProgressionData.rate_F4DC_HCC)) ) {
					hcvstatus.fibrosis = HCVStatus::LIVER_TRANSPLANT;
					hcvstatus.LTtime = 0;
					if ( rb.rand(RandomBin::Progression) <= 1-exp(-1*ProgressionData.rate_mort_LT) ) {
						return true;
					}
				} else {
					hcvstatus.fibrosis = HCVStatus::HCC;
					hcvstatus.HCCtime = 0;
				}
			}
			return false;
		} else if (hcvstatus.fibrosis == HCVStatus::HCC) {
			hcvstatus.HCCtime++;		
			if ( age < (ProgressionData.limit_maxLTage_yrs*52) ) {
				if ( rb.rand(RandomBin::Progression) <= 1-exp(-1*ProgressionData.rate_HCC_LT) ) {
					hcvstatus.fibrosis = HCVStatus::LIVER_TRANSPLANT;
					hcvstatus.LTtime = 0;
					if ( rb.rand(RandomBin::Progression) <= 1-exp(-1*ProgressionData.rate_mort_LT) ) {
						return true;
					}
				}
			}
			return false;
		} else if (hcvstatus.fibrosis == HCVStatus::LIVER_TRANSPLANT) {
			hcvstatus.LTtime++;
		}
	}
	return false;
}