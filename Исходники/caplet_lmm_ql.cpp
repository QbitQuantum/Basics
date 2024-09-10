double caplet_lmm(const Date& todaysDate_,
	const Date& settlementDate_,
	const Date& maturity_,
	Rate spot_,
	Rate strike,
	Rate Numeraire, //zero-coupon bond
	//Volatility volatility

	double correl,
	double a,
	double b,
	double c,
	double d
	)

{

	//SavedSettings backup;

	const Size size = 10;

	#if defined(QL_USE_INDEXED_COUPON)
		const Real tolerance = 1e-5;
	#else
		const Real tolerance = 1e-12;
	#endif

	boost::shared_ptr<IborIndex> index = makeIndex();

	boost::shared_ptr<LiborForwardModelProcess> process(new LiborForwardModelProcess(size, index));

	// set-up pricing engine
	const boost::shared_ptr<OptionletVolatilityStructure> capVolCurve = makeCapVolCurve(Settings::instance().evaluationDate());

	Array variances = LfmHullWhiteParameterization(process, capVolCurve).covariance(0.0).diagonal();

	boost::shared_ptr<LmVolatilityModel> volaModel(new LmFixedVolatilityModel(Sqrt(variances),process->fixingTimes()));

	boost::shared_ptr<LmCorrelationModel> corrModel(new LmExponentialCorrelationModel(size, correl));

	boost::shared_ptr<AffineModel> model(new LiborForwardModel(process, volaModel, corrModel));

	const Handle<YieldTermStructure> termStructure = process->index()->forwardingTermStructure();

	boost::shared_ptr<AnalyticCapFloorEngine> engine1(new AnalyticCapFloorEngine(model, termStructure));

	boost::shared_ptr<Cap> cap1(new Cap(process->cashFlows(),std::vector<Rate>(size, strike)));

	cap1->setPricingEngine(engine1);

	return cap1->NPV();

}