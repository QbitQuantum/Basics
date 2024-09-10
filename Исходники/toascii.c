int main()
{ 
	//将整形数转换成合法的ASCII码字符

	int a = 217;
	char b;
	printf("before toascii() : a value =%d(%c)\n",a,a);
	b=toascii(a);
	printf("after  toascii() : a value =%d(%c)\n",b,b);
}