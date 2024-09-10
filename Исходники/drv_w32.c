/* 这个函数的功能是将一串以空格分隔的命令行参数转换为标准的数组参数 */
void GOL_callmain0()
{
	int argc = 0, i;
	//GetCommandLineA是libmingw中的一个函数，获取当前进程的命令参数缓冲区指针
	UCHAR *p = GetCommandLineA(), *q, *q0, **argv;
	//因此有必要将命令拷贝到程序的空间里面来
	q = q0 = GOL_sysmalloc(GO_strlen(p) + 1);
	do {
		while ((*q++ = *p++) > ' ');
		argc++;		//遇到空格表示一个参数结束，因此argc加1
		p--;		//由于p是后增式，所以现在的p已经指向空格下一个字符了，所以要向前移动一个
		*(q - 1) = '\0';	//将参数放到数组中时参数以\0分隔
		while ('\0' < *p && *p <= ' ')	//跳过无效字符
			p++;
	} while (*p);						//处理所有的参数

	/* 生成标准的argv参数 */
	argv = GOL_sysmalloc((argc + 1) * sizeof (char *));
	argv[0] = q = q0;
	i = 1;
	/* 将argv和每个参数对应起来。 */
	while (i < argc) {
		while (*q++);
		argv[i++] = q;
	}
	argv[i] = NULL;

	/* 标准方式调用传到下一个函数 */
	GOL_callmain(argc, argv);
}