bool is_game_master_mode(const std::string& command_line) {
	if (command_line != "/mode:gm") return false;
	EnvironmentVariable env = EnvironmentVariable();
	const std::string gminfo_filepath = env.get_variable_num("AppData") + "\\Kamioda Games\\wtriugm.ini";
	if (FALSE == PathFileExistsA(gminfo_filepath.c_str())) return false;
	Ini ini(gminfo_filepath);
	return GMInfo(
		get_gm_id(ini),
		ini.getString("GameMaster", "pw", ""),
		GMInfo::MachineInfo(
			env.get_variable_num("ComputerName"),
			env.get_variable_num("UserName"),
			GetUser().search_user_name_to_full_name(env.get_variable_num("UserName"))
		)
	) == gamemaster_list[get_gm_id(ini)];
}