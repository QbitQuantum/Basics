void get_master_player_by_cid(const FunctionCallbackInfo<Value>& args) {
	if (args.Length() != 2) {
		LOG_ERROR("get_master_player_by_cid args error, length: %d\n", args.Length());
		args.GetReturnValue().SetNull();
		return;
	}

	int gate_cid = args[0]->Int32Value(args.GetIsolate()->GetCurrentContext()).FromMaybe(0);
	int player_cid = args[1]->Int32Value(args.GetIsolate()->GetCurrentContext()).FromMaybe(0);
	Master_Player *player = MASTER_MANAGER->find_gate_cid_master_player(gate_cid * 10000 + player_cid);
	if (player) {
		args.GetReturnValue().Set(wrap_master_player(args.GetIsolate(), player));
	} else {
		//设置对象为空
		args.GetReturnValue().SetNull();
		MASTER_MANAGER->close_client(gate_cid, player_cid, ERROR_CLIENT_PARAM);
	}
}