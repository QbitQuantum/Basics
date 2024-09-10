void CreditCard::GenerateCreditCardNumber() {
	for(int i = 0; i < 15; i++) {
		CreditCardNumber += IntToChar(rand() % 10);	
	}
}