static void PVDDoOpen(AOperator *asop, int result)
{
	HeartMsg *sm = container_of(asop, HeartMsg, timer);
	if ((result < 0) || (pvd == NULL)) {
		HeartMsgFree(sm, result);
		return;
	}

	if (sm->object == rt) {
		AOption opt;
		aoption_init(&opt, NULL);

		strcpy_s(opt.name, "version");
		_ltoa_s(login_data.byDVRType, opt.value, 10);
		sm->object->setopt(sm->object, &opt);

		strcpy_s(opt.name, "session_id");
		_ltoa_s(userid, opt.value, 10);
		sm->object->setopt(sm->object, &opt);
	}

	amsg_init(&sm->msg, AMsgType_Option, (char*)sm->option, 0);
	sm->msg.done = &PVDOpenDone;

	result = sm->object->open(sm->object, &sm->msg);
	if (result != 0)
		PVDOpenDone(&sm->msg, result);
}