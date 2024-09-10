int main(void)
{
	unsigned status;
	if ((status = _xbegin()) == 0) { 
		TXN_ASSERT_ONLY(!foo);
	} else { 
		txn_assert_abort_hook(status);
	}	
	f2();
	return 0;
}