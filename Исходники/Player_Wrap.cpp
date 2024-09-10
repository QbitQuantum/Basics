void sync_data_to_game(const FunctionCallbackInfo<Value>& args) {
	if (args.Length() != 2) {
			LOG_ERROR("sync_data_to_game args error, length: %d\n", args.Length());
			return;
		}

		Master_Player *player = unwrap_master_player(args.Holder());
		if (!player) {
			return;
		}

		int msg_id = args[0]->Int32Value(args.GetIsolate()->GetCurrentContext()).FromMaybe(0);
		Block_Buffer *buf = unwrap_buffer(args[1]->ToObject(args.GetIsolate()->GetCurrentContext()).ToLocalChecked());
		player->sync_data_to_game(msg_id, buf);
}