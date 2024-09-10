int
CondorQ::fetchQueueFromHostAndProcessV2(const char *host,
					const char *constraint,
					StringList &attrs,
					condor_q_process_func process_func,
					void * process_func_data,
					int connect_timeout,
					CondorError *errstack)
{
	classad::ClassAdParser parser;
	classad::ExprTree *expr = NULL;
	parser.ParseExpression(constraint, expr);
	if (!expr) return Q_INVALID_REQUIREMENTS;

	classad::ExprList *projList = new classad::ExprList();
	if (!projList) return Q_INTERNAL_ERROR;
	attrs.rewind();
	const char *attr;
	while ((attr = attrs.next())) {
		classad::Value value; value.SetStringValue(attr);
		classad::ExprTree *entry = classad::Literal::MakeLiteral(value);
		if (!entry) return Q_INTERNAL_ERROR;
		projList->push_back(entry);
	}
	classad::ClassAd ad;
	ad.Insert(ATTR_REQUIREMENTS, expr);
	classad::ExprTree *projTree = static_cast<classad::ExprTree*>(projList);
	ad.Insert(ATTR_PROJECTION, projTree);

	DCSchedd schedd(host);
	Sock* sock;
	if (!(sock = schedd.startCommand(QUERY_JOB_ADS, Stream::reli_sock, connect_timeout, errstack))) return Q_SCHEDD_COMMUNICATION_ERROR;

	classad_shared_ptr<Sock> sock_sentry(sock);

	if (!putClassAd(sock, ad) || !sock->end_of_message()) return Q_SCHEDD_COMMUNICATION_ERROR;
	dprintf(D_FULLDEBUG, "Sent classad to schedd\n");

	do {
		classad_shared_ptr<compat_classad::ClassAd> ad(new ClassAd());
		if (!getClassAd(sock, *ad.get())) return Q_SCHEDD_COMMUNICATION_ERROR;
		if (!sock->end_of_message()) return Q_SCHEDD_COMMUNICATION_ERROR;
		dprintf(D_FULLDEBUG, "Got classad from schedd.\n");
		long long intVal;
		if (ad->EvaluateAttrInt(ATTR_OWNER, intVal) && (intVal == 0))
		{ // Last ad.
			sock->close();
			dprintf(D_FULLDEBUG, "Ad was last one from schedd.\n");
			std::string errorMsg;
			if (ad->EvaluateAttrInt(ATTR_ERROR_CODE, intVal) && intVal && ad->EvaluateAttrString(ATTR_ERROR_STRING, errorMsg))
			{
				if (errstack) errstack->push("TOOL", intVal, errorMsg.c_str());
				return Q_REMOTE_ERROR;
			}
			break;
		}
		(*process_func) (process_func_data, ad);
	} while (true);

	return 0;
}