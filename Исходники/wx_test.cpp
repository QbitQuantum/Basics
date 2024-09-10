TWxTestResult WxTest(const TVector<double>& baseline,
                     const TVector<double>& test) {
    TVector<double> diffs;

    for (ui32 i = 0; i < baseline.size(); i++) {
        const double i1 = baseline[i];
        const double i2 = test[i];
        const double diff = i1 - i2;
        if (diff != 0) {
            diffs.push_back(diff);
        }
    }

    if (diffs.size() < 2) {
        TWxTestResult result;
        result.PValue = 0.5;
        result.WMinus = result.WPlus = 0;
        return result;
    }

    Sort(diffs.begin(), diffs.end(), [&](double x, double y) {
        return Abs(x) < Abs(y);
    });

    double w_plus = 0;
    double w_minus = 0;
    double n = diffs.size();


    for (int i = 0; i < n; ++i) {
        double sum = 0;
        double weight = 0;
        int j = i;
        double signPlus = 0;
        double signMinus = 0;

        for (j = i; j < n && diffs[j] == diffs[i]; ++j) {
            sum += (j + 1);
            ++weight;
            signPlus += diffs[i] >= 0;
            signMinus += diffs[i] < 0;
        }

        const double meanRank = sum / weight;
        w_plus += signPlus * meanRank;
        w_minus += signMinus * meanRank;

        i = j - 1;
    }

    TWxTestResult result;
    result.WPlus = w_plus;
    result.WMinus = w_minus;

    const double w = result.WPlus - result.WMinus;
    if (n > 16) {
        double z = w / sqrt(n * (n + 1) * (2 * n + 1) * 1.0 / 6);
        result.PValue = 2 * (1.0 - NormalCDF(Abs(z)));
    } else {
        result.PValue = 2 * CalcLevelOfSignificanceWXMPSR(Abs(w), (int) n);
    }
    result.PValue = 1.0 - result.PValue;
    return result;
}