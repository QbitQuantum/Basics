void TurnstileGate::Violation()
{
	setState(violation);
	printf_s("Violation!\n\n");
}