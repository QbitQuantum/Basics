/*
 *@brief send线程从conf中读入全局设置
 */
int send_load_config()
{
	FILE *fp;						//打开配置文件指针
	int a[4];						//临时存储点分IP的4个部分
	int flag;						//标识IP是否合法
	char s[TEXT_LINE_LEN];	//存储从配置文件中读取的一行数据
	uint32_t i;					//for循环计数
	char c,c1;					//连续从文件的一行中读取的两个字符，用以标识变量、IP、注释行、无用行
	char *eq = NULL;			//字符串中表示"="的指针
	int len = 0;					//读取的字符串长度，如果是一个变量，其标识符的长度要大于0
	uint32_t tmpi = 0;			//临时存储读取的变量数值

	fp = fopen("conf", "rt");
	if (fp == NULL) {
		write_log("Can't open config file \"conf\":%s\n", strerror(errno));
		return -1;
	}

	net_buffer = (char*)malloc(NET_BUFFER_LEN);
	if (net_buffer == NULL) {
		write_log("net_buffer malloc failed!\n");
		return -1;
	}
	encrypt_net_buffer = (char*)malloc(NET_BUFFER_LEN);
	if (encrypt_net_buffer == NULL) {
		write_log("encrypt net_buffer malloc failed!\n");
		return -1;
	}

	while (!feof(fp)) {
		c = fgetc(fp);
		if ((int)c == -1)
			//EOF==-1
			break;
		if (c != '$') {
			while (c != '\n' && !feof(fp))
				c = fgetc(fp);
			continue;
		}
		if ((c1 = fgetc(fp)) != ':') {
			while (c != '\n' && !feof(fp))
				c = fgetc(fp);
			continue;
		}

		if ('$' == c && ':' == c1) {
			flag = 0;
			fgets(s,TEXT_LINE_LEN,fp);
			tmpi = 0;
			len = 0;
			if ((eq = strchr(s, (int)'=')) == NULL)
				continue;
			len = eq - s;
			if (len <= 0)
				continue;

			if (bcmp(s, "data_store_path", len) == 0) {
				len = strchr(eq + 1, (int)'\n') - ( eq + 1 );
				if ((len + 1) >= sizeof(data_store_path))
					continue;
				if (*( eq + 1 ) == '/')	//从根路径开始
					snprintf(data_store_path, len + 1, "%s", eq + 1 );
			}
			else if (bcmp(s, "accept_port", len) == 0) {
				sscanf(eq+1, "%d", &tmpi);
				if (tmpi > 1024 && tmpi < 65536)
					accept_port = tmpi;
			}
			else if (bcmp(s,"des_pass_phrase",len) == 0) {
				len = strchr(eq + 1,'\n') - (eq + 1);
				if ((len + 1) >= sizeof(des_pass_phrase))
					continue;
				snprintf(des_pass_phrase, len + 1, "%s", eq + 1);
			}
			else if (bcmp(s,"stop",len) == 0) {
				len = strchr(eq + 1,'\n') - (eq + 1);
				if ((len + 1) >= sizeof(stop_filename)){
					write_log("bad stop_time!\n");
					return -1;
				}
				snprintf(stop_filename, len + 1, "%s", eq + 1);
				int year,mon,day;
				sscanf(stop_filename, "META-%04d-%02d-%02d", &year, &mon, &day);
				snprintf(stop_folder, sizeof(stop_folder), "%04d-%02d-%02d", year, mon, day);
			}
			else if (bcmp(s, "accept_addr", len) == 0) {
				a[0] = a[1] = a[2] = a[3] = -1;
				sscanf(eq + 1, "%d.%d.%d.%d", &a[0], &a[1], &a[2], &a[3]);
				for (i = 0; i <= 3; i++) {
					if (a[i] > 255 || a[i] < 0) {
						write_log("[Warning]:illegal server ip in file \"conf\" [%s],ignored\n",s);
						flag = 1;	//IP有问题！则跳出并置位错误标记为真
						break;
					}
				}//for
				if (!flag)
					accept_addr = a[0]*256*256*256 + a[1]*256*256 + a[2]*256 + a[3];
			}//server
		}//if $:
	}//while
	fclose(fp);
	return 0;
}