void CPISwapTest::zciisconsistency() {
    CommonVars common;

    ZeroCouponInflationSwap::Type ztype = ZeroCouponInflationSwap::Payer;
    Real  nominal = 1000000.0;
    Date startDate(common.evaluationDate);
    Date endDate(25, November, 2059);
    Calendar cal = UnitedKingdom();
    BusinessDayConvention paymentConvention = ModifiedFollowing;
    DayCounter dummyDC, dc = ActualActual();
    Period observationLag(2,Months);

    Rate quote = 0.03714;
    ZeroCouponInflationSwap zciis(ztype, nominal, startDate, endDate, cal,
                                  paymentConvention, dc, quote, common.ii,
                                  observationLag);

    // simple structure so simple pricing engine - most work done by index
    ext::shared_ptr<DiscountingSwapEngine>
    dse(new DiscountingSwapEngine(common.nominalTS));

    zciis.setPricingEngine(dse);
    QL_REQUIRE(fabs(zciis.NPV())<1e-3,"zciis does not reprice to zero");

    std::vector<Date> oneDate;
    oneDate.push_back(endDate);
    Schedule schOneDate(oneDate, cal, paymentConvention);

    CPISwap::Type stype = CPISwap::Payer;
    Real inflationNominal = nominal;
    Real floatNominal = inflationNominal * std::pow(1.0+quote,50);
    bool subtractInflationNominal = true;
    Real dummySpread=0.0, dummyFixedRate=0.0;
    Natural fixingDays = 0;
    Date baseDate = startDate - observationLag;
    Real baseCPI = common.ii->fixing(baseDate);

    ext::shared_ptr<IborIndex> dummyFloatIndex;

    CPISwap cS(stype, floatNominal, subtractInflationNominal, dummySpread, dummyDC, schOneDate,
               paymentConvention, fixingDays, dummyFloatIndex,
               dummyFixedRate, baseCPI, dummyDC, schOneDate, paymentConvention, observationLag,
               common.ii, CPI::AsIndex, inflationNominal);

    cS.setPricingEngine(dse);
    QL_REQUIRE(fabs(cS.NPV())<1e-3,"CPISwap as ZCIIS does not reprice to zero");

    for (Size i=0; i<2; i++) {
        QL_REQUIRE(fabs(cS.legNPV(i)-zciis.legNPV(i))<1e-3,"zciis leg does not equal CPISwap leg");
    }
    // remove circular refernce
    common.hcpi.linkTo(ext::shared_ptr<ZeroInflationTermStructure>());
}