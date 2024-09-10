// 鼠标移动事件(点击鼠标任何键)的处理函数
gboolean motion_event_callback(GtkWidget *widget, GdkEventMotion *event, gpointer data)
{
	// 获得移动鼠标的坐标值
	gint x = event->x;
	gint seek_sec = 0;
	char cmd[32] = "seek ";
	char buf[8] = {0};
	MPLAYER *pm = (MPLAYER*)data;

	if(pm->playflag == playing) pm->playflag = stop;

	seek_sec = x * song.end_time/400;          //毫秒
	seek_sec = (seek_sec - song.cur_time)/1000;//秒
	
	printf("seek_sec = %d\n",seek_sec);
	
	gcvt(seek_sec,5,buf);
	strcat(cmd, buf);
	strcat(cmd,"\n");
	printf("cmd = %s\n",cmd);
	send_cmd(cmd,pm);

	pm->playflag == playing;
	//gint j = event->y;
	//printf("motion_x = %d, motion_y = %d\n", i, j);
	return TRUE;
}