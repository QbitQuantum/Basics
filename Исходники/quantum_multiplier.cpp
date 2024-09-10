Complex * Gates::reverse_kronecker(Complex * kron, int kron_size){
	/*ENTANGLEMENT MIGHT NOT NEED TO BE IMPLEMENTED
		//TODO: CHECK IF KRON IS ENTANGLED
		if (entangler.is_gateout_entangled(kron)){
			//ENTANGLE
			std::cout << "Entangled" << std::endl;
		}
		//TODO: IF IT IS -> ADD THIS KRON TO THE ENTANGLEMENT LIST

		//TODO: UPDATE ALL ENTANGLEMENTS
	*/
	int reversed_kron_size = (log(kron_size) / log(2)) * 2;
	Complex * reversed_kronecker = new Complex[reversed_kron_size+2];
	for (int i = 0; i < reversed_kron_size;i++) reversed_kronecker[i] = Complex(0, 0);

	for (int i = 0; i<kron_size; i++)
		if (kron[i].re == 1){
			int toBinSize = log(kron_size) / log(2);
			char *toBin = new char[toBinSize];
			toBin = utils.long2binstr(i, toBinSize);
			_strrev(toBin);
			int index_rev_kro = 0; //USE ITS OWN INDEX BECAUSE J IS THE INDEX OF TOBIN AN TOBIN HAS TO GO REVERSED
			for (int j = 0; j < toBinSize; j++){
				if (toBin[j] == '1') reversed_kronecker[index_rev_kro+1] = Complex(1, 0);
				else reversed_kronecker[index_rev_kro] = Complex(1, 0); 
				index_rev_kro +=2;
			}
			delete [] toBin;
			break;
		}
	
	return reversed_kronecker;
}