void 	FASTCALL FWriteBanks(int type, FILE *f)
{
	BANK *bank=banks;
	while(bank) {
        if(bank->type==type) {
        	FWrite(bank->buffer,bank->maxsize,f);
        }
        bank = bank->next;
    }
}