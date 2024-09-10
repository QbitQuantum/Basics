Value ApiEvents::CheckResultAPIHandler(const MessageOrigin& origin, const Dictionary::Ptr& params)
{
	if (!origin.FromClient->GetEndpoint())
		return Empty;

	if (!params)
		return Empty;

	CheckResult::Ptr cr = make_shared<CheckResult>();

	Dictionary::Ptr vcr = params->Get("cr");
	Array::Ptr vperf = vcr->Get("performance_data");
	vcr->Remove("performance_data");

	Deserialize(cr, params->Get("cr"), true);

	Array::Ptr rperf = make_shared<Array>();

	ObjectLock olock(vperf);
	BOOST_FOREACH(const Value& vp, vperf) {
		Value p;

		if (vp.IsObjectType<Dictionary>()) {
			PerfdataValue::Ptr val = make_shared<PerfdataValue>();
			Deserialize(val, vp, true);
			rperf->Add(val);
		} else
			rperf->Add(vp);
	}