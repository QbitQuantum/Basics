std::string EQEmuConfig::GetByName(const std::string &var_name) const
{
	if (var_name == "ShortName") {
		return (ShortName);
	}
	if (var_name == "LongName") {
		return (LongName);
	}
	if (var_name == "WorldAddress") {
		return (WorldAddress);
	}
	if (var_name == "LoginHost") {
		return (LoginHost);
	}
	if (var_name == "LoginAccount") {
		return (LoginAccount);
	}
	if (var_name == "LoginPassword") {
		return (LoginPassword);
	}
	if (var_name == "LoginPort") {
		return (itoa(LoginPort));
	}
	if (var_name == "Locked") {
		return (Locked ? "true" : "false");
	}
	if (var_name == "WorldTCPPort") {
		return (itoa(WorldTCPPort));
	}
	if (var_name == "WorldIP") {
		return (WorldIP);
	}
	if (var_name == "TelnetEnabled") {
		return (TelnetEnabled ? "true" : "false");
	}
	if (var_name == "WorldHTTPPort") {
		return (itoa(WorldHTTPPort));
	}
	if (var_name == "WorldHTTPMimeFile") {
		return (WorldHTTPMimeFile);
	}
	if (var_name == "WorldHTTPEnabled") {
		return (WorldHTTPEnabled ? "true" : "false");
	}
	if (var_name == "ChatHost") {
		return (ChatHost);
	}
	if (var_name == "ChatPort") {
		return (itoa(ChatPort));
	}
	if (var_name == "MailHost") {
		return (MailHost);
	}
	if (var_name == "MailPort") {
		return (itoa(MailPort));
	}
	if (var_name == "DatabaseHost") {
		return (DatabaseHost);
	}
	if (var_name == "DatabaseUsername") {
		return (DatabaseUsername);
	}
	if (var_name == "DatabasePassword") {
		return (DatabasePassword);
	}
	if (var_name == "DatabaseDB") {
		return (DatabaseDB);
	}
	if (var_name == "DatabasePort") {
		return (itoa(DatabasePort));
	}
	if (var_name == "QSDatabaseHost") {
		return (QSDatabaseHost);
	}
	if (var_name == "QSDatabaseUsername") {
		return (QSDatabaseUsername);
	}
	if (var_name == "QSDatabasePassword") {
		return (QSDatabasePassword);
	}
	if (var_name == "QSDatabaseDB") {
		return (QSDatabaseDB);
	}
	if (var_name == "QSDatabasePort") {
		return (itoa(QSDatabasePort));
	}
	if (var_name == "SpellsFile") {
		return (SpellsFile);
	}
	if (var_name == "OpCodesFile") {
		return (OpCodesFile);
	}
	if (var_name == "MapDir") {
		return (MapDir);
	}
	if (var_name == "QuestDir") {
		return (QuestDir);
	}
	if (var_name == "PluginDir") {
		return (PluginDir);
	}
	if (var_name == "LogPrefix") {
		return (LogPrefix);
	}
	if (var_name == "LogSuffix") {
		return (LogSuffix);
	}
	if (var_name == "ZoneExe") {
		return (ZoneExe);
	}
	if (var_name == "ZonePortLow") {
		return (itoa(ZonePortLow));
	}
	if (var_name == "ZonePortHigh") {
		return (itoa(ZonePortHigh));
	}
	if (var_name == "DefaultStatus") {
		return (itoa(DefaultStatus));
	}
//	if(var_name == "DynamicCount")
//		return(itoa(DynamicCount));
	return ("");
}