/*
 * Destroy an interface.
 */
static void DestroyInterface(ILDocInterface *interface)
{
	if(interface->name)
	{
		ILFree(interface->name);
	}
}