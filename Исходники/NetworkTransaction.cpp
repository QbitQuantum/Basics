void NetworkTransaction::Write(StringRef ref)
{
	Write(ref.Pointer(), ref.strlen());
}