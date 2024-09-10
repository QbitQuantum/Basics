__fastcall TScreenSnapper::~TScreenSnapper()
{
	ChangeClipboardChain(Handle,NextHandle); // Unregister from clipboard chain
}