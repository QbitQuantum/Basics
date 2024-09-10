int main(){
	atexit(fa);//只注册fa()，只有在exit()时才调用;
	printf("begin\n");
	exit(0);//参数是退出码，可以用来记录退出情况；
	_Exit(0);//立即结束，不掉用fa；
	printf("end\n");	
	return 0;
}