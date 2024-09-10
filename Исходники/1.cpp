class argument{
	public:
	int i;
}


void L1(vector<argument> P12){
	int sum = 0;
	for (int k = 0; k < P12.length(); k++) {
		sum += P12[k].i;
	}
}