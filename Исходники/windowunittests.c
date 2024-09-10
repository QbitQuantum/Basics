int main(){
	int i;
	for(i = 10; i < 30; i++){
		insertIntoCWindow(i,0,10,1000);
	}
	
	printWindow();

	printf("\n\n (expected to fail: addeding pkts 30 31\n");
	insertIntoCWindow(30,0,10,1000);
	insertIntoCWindow(31,0,10,1000);
	
	printWindow();
	
	printf("\n\n removing from window pkts 10 11 12\n");
	removeFromCWindow(10);
	removeFromCWindow(11);
	removeFromCWindow(12);
	printWindow();
	//this should not move windowStartOfPacketBlock 
	printf("\n\n removing from window pkts 14 15\n");
	removeFromCWindow(14);
	removeFromCWindow(15);
	printWindow();
	//this should move windowStartOfPacketBlock
	printf("\n\n removing from window pkts 13\n");
	removeFromCWindow(13);
	printWindow();

	printf("\n\n (expected to success: addeding pkts 30 31\n");
	insertIntoCWindow(30,0,10,1000);
	insertIntoCWindow(31,0,10,1000);
	printWindow();

	printf("\n\n (expected to success: addeding pkts 32 33 34 35\n");
	insertIntoCWindow(32,0,10,1000);
	insertIntoCWindow(33,0,10,1000);
	insertIntoCWindow(34,0,10,1000);
	insertIntoCWindow(35,0,10,1000);
	printWindow();
	


}