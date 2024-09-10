void push(int value)
{
	array[stacksize]= value;
	stacksize = stacksize + 1;
	if(stacksize > SIZE)
	{
		printerror("Stack Overflow");
	}
}