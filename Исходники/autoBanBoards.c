int
genfiles()
{
	FILE *fp;
	if ((fp = fopen("bbstmpfs/dynamic/banAlert.www.new", "w")) == NULL)
		return -1;
	fprintf(fp, "<b>版面文章超限报警</b><br>"
		"<font class=red>!!!</font> 版面文章将要超限, 版面将在 5 小时内被禁止发文.<br>"
		"<font class=red><b>!!!</b></font> 版面文章超限, 版面已经被禁止发文.<br>"
		"<br><br>普通版面"
		"<li><u>3 天前的文章总数</u>上限 3000, "
		"<li><u>5 小时前的文章总数</u>上限 4000, "
		"<li><u>所有文章总数</u>不得超过 4000 + 500."
		"<br>版面文章数有特殊规定者"
		"<li><u>3 天前的文章总数</u>上限若为 x,"
		"<li><u>5 小时前的文章总数</u>上限 x + x/3,"
		"<li><u>所有文章总数</u>不得超过 x + x/3 + 500.");
	fprintf(fp, "<br><br>上次检查时间：%s<br>", Ctime(time(NULL)));
	fclose(fp);
	rename("bbstmpfs/dynamic/banAlert.www.new",
	       "bbstmpfs/dynamic/banAlert.www");
	return 0;
}