/* SImage::applyTranslation
 * Applies a palette translation to the image
 *******************************************************************/
bool SImage::applyTranslation(string tr, Palette8bit* pal)
{
	// Some hardcoded translations from ZDoom
	if (!tr.CmpNoCase("\"doom0\""))			tr = "\"112:127=96:111\"";
	else if (!tr.CmpNoCase("\"doom1\""))	tr = "\"112:127=64:79\"";
	else if (!tr.CmpNoCase("\"doom2\""))	tr = "\"112:127=32:47\"";
	else if (!tr.CmpNoCase("\"doom3\""))	tr = "\"112:127=88:103\"";
	else if (!tr.CmpNoCase("\"doom4\""))	tr = "\"112:127=56:71\"";
	else if (!tr.CmpNoCase("\"doom5\""))	tr = "\"112:127=176:191\"";
	else if (!tr.CmpNoCase("\"doom6\""))	tr = "\"112:127=192:207\"";
	else if (!tr.CmpNoCase("\"heretic0\""))	tr = "\"225:240=114:129\"";
	else if (!tr.CmpNoCase("\"heretic1\""))	tr = "\"225:240=145:160\"";
	else if (!tr.CmpNoCase("\"heretic2\""))	tr = "\"225:240=190:205\"";
	else if (!tr.CmpNoCase("\"heretic3\""))	tr = "\"225:240=67:82\"";
	else if (!tr.CmpNoCase("\"heretic4\""))	tr = "\"225:240=9:24\"";
	else if (!tr.CmpNoCase("\"heretic5\""))	tr = "\"225:240=74:89\"";
	else if (!tr.CmpNoCase("\"heretic6\""))	tr = "\"225:240=150:165\"";
	else if (!tr.CmpNoCase("\"heretic7\""))	tr = "\"225:240=192:207\"";
	else if (!tr.CmpNoCase("\"heretic8\""))	tr = "\"225:240=95:110\"";
	else if (!tr.CmpNoCase("\"strife0\""))	tr = "\"32:63=0:31\", \"128:143=64:79\", \"241:246=224:229\", \"247:251=241:245\"";
	else if (!tr.CmpNoCase("\"strife1\""))	tr = "\"32:63=0:31\", \"128:143=176:191\"";
	else if (!tr.CmpNoCase("\"strife2\""))	tr = "\"32:47=208:223\", \"48:63=208:223\", \"128:143=16:31\"";
	else if (!tr.CmpNoCase("\"strife3\""))	tr = "\"32:47=208:223\", \"48:63=208:223\", \"128:143=48:63\"";
	else if (!tr.CmpNoCase("\"strife4\""))	tr = "\"32:63=0:31\", \"80:95=128:143\", \"128:143=80:95\", \"192:223=160:191\"";
	else if (!tr.CmpNoCase("\"strife5\""))	tr = "\"32:63=0:31\", \"80:95=16:31\", \"128:143=96:111\", \"192:223=32:63\"";
	else if (!tr.CmpNoCase("\"strife6\""))	tr = "\"32:63=0:31\", \"80:95=64:79\", \"128:143=144:159\", \"192=1\", \"193:223=1:31\"";
	// Some more from Eternity
	else if (!tr.CmpNoCase("\"tomato\""))	tr = "\"112:113=171:171\", \"114:114=172:172\", \"115:122=173:187\", \"123:124=188:189\", \"125:126=45:47\", \"127:127=1:1\"";
	else if (!tr.CmpNoCase("\"dirt\""))		tr = "\"112:117=128:133\", \"118:120=135:137\", \"121:123=139:143\", \"124:125=237:239\", \"126:127=1:2\"";
	else if (!tr.CmpNoCase("\"blue\""))		tr = "\"112:121=197:206\", \"122:127=240:245";
	else if (!tr.CmpNoCase("\"gold\""))		tr = "\"112:113=160:160\", \"114:119=161:166\", \"120:123=236:239\", \"124:125=1:2\", \"126:127=7:8\"";
	else if (!tr.CmpNoCase("\"sea\""))		tr = "\"112:112=91:91\", \"113:114=94:95\", \"115:122=152:159\", \"123:126=9:12\", \"127:127=8:8\"";
	else if (!tr.CmpNoCase("\"black\""))	tr = "\"112:112=101:101\", \"113:121=103:111\", \"122:125=5:8\", \"126:127=0:0\"";
	else if (!tr.CmpNoCase("\"purple\""))	tr = "\"112:113=4:4\", \"114:115=170:170\", \"116:125=250:254\", \"126:127=46:46\"";
	else if (!tr.CmpNoCase("\"vomit\""))	tr = "\"112:119=209:216\", \"120:121=218:220\", \"122:124=69:75\", \"125:127=237:239\"";
	else if (!tr.CmpNoCase("\"pink\""))		tr = "\"112:113=16:17\", \"114:117=19:25\", \"118:119=27:28\", \"120:124=30:38\", \"125:126=41:43\", \"127:127=46:46\"";
	else if (!tr.CmpNoCase("\"cream\""))	tr = "\"112:112=4:4\", \"113:118=48:63\", \"119:119=65:65\", \"120:124=68:76\", \"125:126=77:79\", \"127:127=1:1\"";
	else if (!tr.CmpNoCase("\"white\""))	tr = "\"112:112=4:4\", \"113:115=80:82\", \"116:117=84:86\", \"118:120=89:93\", \"121:127=96:108\"";

	Translation trans;
	trans.clear();
	Tokenizer tz;
	tz.openString(tr);
	string token = tz.getToken();
	while (!token.IsEmpty())
	{
		trans.parse(token);
		tz.getToken();
		token = tz.getToken();
	}
	return applyTranslation(&trans, pal);
}