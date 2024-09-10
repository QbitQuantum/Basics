bool HCVTreatment_TwoDrug::treatment_update(RandomBin& rb, int age, HCVTreatmentStatus& hcv_treatment_status, HCVStatus& hcvstatus, HCVRiskStatus& hcvriskstatus,
        bool male, bool white, double tx_mort_rate)
{
    if (hcvstatus.treatment == HCVStatus::ONGOING && hcvstatus.fibrosis >= HCVStatus::F0 && hcvstatus.fibrosis <= HCVStatus::F4) {

        if (hcv_treatment_status.week == 0) {
            // avg'd so everyone gets charged even though everyone does not get side effects
            hcvcea->record_event(age, cost_Tx_sideeffects, 0);
        }

        if ( rb.rand(RandomBin::Treatment) < ( 1-exp(-1*tx_mort_rate) ) ) {
            hcvstatus.treatment = HCVStatus::FAIL;
            return true;
        }

        if (hcvstatus.genotype == HCVStatus::G1) {
            if (hcv_treatment_status.week >= 48) {
                hcvstatus.treatment = HCVStatus::FAIL;
                hcv_treatment_status.week = 0;
            } else {
                process_G1(rb, age, hcv_treatment_status, hcvstatus, hcvriskstatus, male, white);
                hcv_treatment_status.week++;
            }
        } else if (hcvstatus.genotype == HCVStatus::G2) {
            if (hcv_treatment_status.week >= 24) {
                hcvstatus.treatment = HCVStatus::FAIL;
                hcv_treatment_status.week = 0;
            } else {
                process_G2(rb, age, hcv_treatment_status, hcvstatus, hcvriskstatus, male, white);
                hcv_treatment_status.week++;
            }
        } else if (hcvstatus.genotype == HCVStatus::G3) {
            if (hcv_treatment_status.week >= 24) {
                hcvstatus.treatment = HCVStatus::FAIL;
                hcv_treatment_status.week = 0;
            } else {
                process_G3(rb, age, hcv_treatment_status, hcvstatus, hcvriskstatus, male, white);
                hcv_treatment_status.week++;
            }
        }

    } else {
        if (hcvstatus.treatment == HCVStatus::ONGOING && hcvstatus.fibrosis >= HCVStatus::F4) {
            hcvstatus.treatment = HCVStatus::FAIL;
            hcv_treatment_status.week = 0;
        }
    }
    return false;
}