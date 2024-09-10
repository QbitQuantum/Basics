void f(void* arg)
{
	PutChar('5');
	Arg *param = (Arg*) arg;
	PutChar(param->a);
	PutChar('6');
	param->wait = 0;
	PutChar('7');
	UserThreadExit(0);
}