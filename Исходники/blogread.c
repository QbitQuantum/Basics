int
printBlogArticle(struct Blog *blog, int n)
{
	struct BlogHeader *blh;
	char filePath[80];
	int i, s, t;
	if (n < 0 || n >= blog->nIndex)
		return -1;
	blh = &blog->index[n];
	setBlogPost(filePath, blog->userid, blh->fileTime);
	printf("<h2 class=posttitle>");
	printf("%s", nohtml(blh->title));
	printf("</h2>");
	printf("<small>%s 发表于 %s</small>", blog->config->useridUTF8,
	       Ctime(blh->fileTime));

	printf("<div class=postcontent>");
	showfile(filePath);
	printf("</div>");

	printf("<div class=postfoot>");
	s = blh->subject;
	printf("栏目：%s", nohtml(blog->subject[s].title));
	printf(" | Tags：");
	for (i = 0; i < MAXTAG; ++i) {
		t = blh->tag[i];
		if (t < 0 || t >= blog->nTag)
			continue;
		if (! *blog->tag[t].title)
			continue;
		printf("%s ", nohtml(blog->tag[t].title));
	}
	printf(" | 评论(%d)", blh->nComment);
	if (!strcmp(currentuser->userid, blog->userid))
		printf(" | <a href=blogpost?T=%d>编辑</a>", blh->fileTime);
	printf("</div>");
	return 0;
}