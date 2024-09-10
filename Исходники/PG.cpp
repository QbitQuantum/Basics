//GOST basic Simple Step
void Crypt_Step(Data *DATA, uint8_t *Table, uint32_t Key, bool Last){
	typedef  union
	{
		uint32_t full;
		uint8_t parts[NODES / 2];
	} Data_Part_sum;

	Data_Part_sum S;
	
//N1=Lo(DATA); N2=Hi(DATA)
	_ADD32((*DATA).half[N1], Key, S.full);//S=(N1+X)mod2^32

	for (uint8_t m = 0; m<(NODES / 2); m++){
		S.parts[m] = *(Table + (S.parts[m] & 0x0F));
		Table += MAX_NODE_VALUE;//next line in table
	}

	S.full = (*DATA).half[N2] ^ _lrotl(S.full, 11);//S=Rl(11,S); rol S,11 //S XOR N2

	if (Last){
		(*DATA).half[N2] = S.full; //N2=S
	}else{
		(*DATA).half[N2] = (*DATA).half[N1];//N2=N1
		(*DATA).half[N1] = S.full;//N1=S
	}
}