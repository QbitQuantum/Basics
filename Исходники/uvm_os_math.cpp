extern "C" void uvm_os_wrap_libmath_cosl(CDataStack& dataStack)
{
	long double x=dataStack.pop().getReal();
	long double result=cosl(x);

	dataStack.push(result);
}