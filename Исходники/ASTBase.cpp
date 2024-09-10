void ASTBase::panic(const char *msg)
{
	/* MR23 */ printMessage(stderr,"ASTBase panic: %s\n", msg);
	exit(PCCTS_EXIT_FAILURE);
}