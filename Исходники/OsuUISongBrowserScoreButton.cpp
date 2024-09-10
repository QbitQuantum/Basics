UString OsuUISongBrowserScoreButton::getModsString(int mods)
{
	UString modsString;

	if (mods & OsuReplay::Mods::NoFail)
		modsString.append("NF,");
	if (mods & OsuReplay::Mods::Easy)
		modsString.append("EZ,");
	if (mods & OsuReplay::Mods::TouchDevice)
		modsString.append("Touch,");
	if (mods & OsuReplay::Mods::Hidden)
		modsString.append("HD,");
	if (mods & OsuReplay::Mods::HardRock)
		modsString.append("HR,");
	if (mods & OsuReplay::Mods::SuddenDeath)
		modsString.append("SD,");
	if (mods & OsuReplay::Mods::DoubleTime)
		modsString.append("DT,");
	if (mods & OsuReplay::Mods::Relax)
		modsString.append("Relax,");
	if (mods & OsuReplay::Mods::HalfTime)
		modsString.append("HT,");
	if (mods & OsuReplay::Mods::Nightcore)
		modsString.append("NC,");
	if (mods & OsuReplay::Mods::Flashlight)
		modsString.append("FL,");
	if (mods & OsuReplay::Mods::Autoplay)
		modsString.append("AT,");
	if (mods & OsuReplay::Mods::SpunOut)
		modsString.append("SO,");
	if (mods & OsuReplay::Mods::Relax2)
		modsString.append("AP,");
	if (mods & OsuReplay::Mods::Perfect)
		modsString.append("PF,");
	if (mods & OsuReplay::Mods::ScoreV2)
		modsString.append("v2,");
	if (mods & OsuReplay::Mods::Target)
		modsString.append("Target,");
	if (mods & OsuReplay::Mods::Nightmare)
		modsString.append("NM,");

	if (modsString.length() > 0)
		modsString = modsString.substr(0, modsString.length()-1);

	return modsString;
}