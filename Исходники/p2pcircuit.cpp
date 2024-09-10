///=================================================================================
// creates the binary circuit that consits of only gate infomation
// input: the number of items of each server,	
//        the number of servers,
//        the number of bits for each item "value" (for multiparty computation)
// output: void
BOOL CP2PCircuit::Create(int nParties, const vector<int>& vParams)
{
	int num_servers = nParties - 1;
	
	int num_items  = vParams[0];
	int input_range = vParams[1];

	if( vParams.size() < 2 )
	{
		cout << "Error! This circuit needs two parameters: #items and input_range." << endl;
		return FALSE;
	}

	int tot_items;		// # of items of all servers
	int num_vbits;		// # of bits to represent each value	
	int num_bits;		// # of bits to identify [0, num_items]
	int num_gates;		// # of gates required to create the circuit
	int num_layers;		// # of layers for the tournament
	int num_andgates;	// # of AND gates
	int num_mux_val;	// # of MUX circuit for values
	int num_mux_idx;	// # of MUX circuit for indexes
	int num_cmp;		// # of comparison (circuit)
	int num_in;			// # of IN gates
	int num_out;		// # of OUT gates
	int num_vs_bottom;	// # of gates for each vs at the bottom of tournament 
	int num_vs_middle;	// # of gates for each vs between the bottom and top of the tournament
	int num_vs_top;		// # of gates for each vs at top of the tournament
	//vector<int> outputs = vector<int>();	// final outputs that will be given to OUT gates
	
	tot_items = num_items * num_servers;

	// collects necessary info first
	num_bits = GetNumBits(tot_items);
	num_vbits = input_range >= 0? GetNumBits(input_range) : num_bits;
	//num_vbits = -1;
	
	num_layers = (int)ceil(Log2(tot_items));
	//num_andgates = tot_items * num_bits;
	num_andgates = tot_items * num_vbits;
	num_cmp = tot_items - 1;
	num_mux_val = num_cmp - 1;
	num_mux_idx = num_cmp;
	//num_in = 2+ tot_items*num_bits + tot_items;
	num_in = 2+ tot_items*num_vbits + tot_items;
	num_out = num_bits;
	//num_gates = num_andgates + (num_mux_val+num_mux_idx)*MUX_GATES*num_bits 
	//	+ num_cmp*CMP_GATES*num_bits + num_in +num_out;
	num_gates = num_andgates + num_mux_val*MUX_GATES*num_vbits
		+ num_mux_idx*MUX_GATES*num_bits + num_cmp*CMP_GATES*num_vbits + num_in +num_out;
	//num_gates = GetNumGates(tot_items, num_bits);

	//num_vs_bottom = num_bits*2 + CMP_GATES*num_bits + 2*MUX_GATES*num_bits;
	num_vs_bottom = num_vbits*2 + CMP_GATES*num_vbits + MUX_GATES*(num_bits+num_vbits);
	//num_vs_middle = num_vs_bottom - 2*num_bits;
	num_vs_middle = num_vs_bottom - 2*num_vbits;
	num_vs_top = num_vs_middle - MUX_GATES*num_bits;
	num_vs_top = num_vs_middle - MUX_GATES*num_vbits;

	// circuit initialization
	cout << " Total # of gates:" << num_gates << endl;
	cout << " Total # of gates for bottom vs:" << num_vs_bottom << endl;
	cout << " Total # of gates for middle vs:" << num_vs_middle << endl;
	cout << " Total # of gates for top vs:" << num_vs_top << endl;
	cout << " Total # of IN gates:" << num_in << endl;

	m_nNumGates = num_gates;
	//m_nNumBits = num_bits;
	m_nNumItems = num_items; 
	//m_nNumVBits = input_range >= 0 ? GetNumBits(input_range) : num_bits;
	m_nNumServers = num_servers;
	m_nNumXORs = 0;
	m_vNumVBits.resize(nParties,num_vbits);
	m_vNumVBits[nParties-1] = 1;

	m_pGates = new GATE[num_gates];  
	if (m_pGates == NULL){
		puts("CP2PCircuit::Create(const int): memory error");
		exit(-1);
	}
	for (int i=0;i<num_gates;i++){
		(m_pGates+i)->left = -1;
		(m_pGates+i)->right = -1;
		(m_pGates+i)->p_num = 0;
	}
	 

	// starts creating the circuit	
	int id = 0;				// gate id
	int is_left = 1;		// left - 1, right - 0	
	int is_final = 0;		// final comparison: yes - 1, no - 0
	int is_bottompair = 0;	// indicates whether the comparison is a pair at the bottom of tournament
	int is_bottomsingle = 0;// indicates whether the comparison is a single at the bottom of tournament
	int is_middle = 0;		// indicates whether the comparison is in the middle of tournament
	int is_alone = 0;		// whether the vs is a pair or single
	int is_moreMUXvalue = 0;// whether the higher layer's vs uses MUX_value
	int num_remainders;		// # of items that remain on the tournament
	int gates_skip;			// # of gates that should be skipped
	int layer_no=0;			// layer number from the bottom of the tournament starting from 0
	int* vs_no;				// # of completed vs from the leftmost (on the current layer) of the tournament starting from 0
	int* layer_waiting;	// # of waitings at each layer
	int* is_left_before;	// whether last vs was left or right
	
	num_remainders = tot_items;
	
	layer_waiting = new int[num_layers+1];
	vs_no = new int[num_layers+1];
	is_left_before = new int[num_layers+1];
	for (int i=0;i<num_layers;i++){
		layer_waiting[i] = 0;
		vs_no[i]=0;
		is_left_before[i] = -1;
	}

	// IN gates for const inputs 0 and 1
	(m_pGates+id)->type = G_XOR;
	(m_pGates+id)->right = 0;
	id++;
	(m_pGates+id)->type = G_XOR;
	(m_pGates+id)->right = 0;
	id++;
	
	// creates gates for server inputs
	int tmp_num_bits;
	if (num_vbits <= 0){
		tmp_num_bits = num_bits;	// for two party computation
	}
	else{
		tmp_num_bits = num_vbits;	// for multiparty computation
	}
	m_serStartGate = id;
	for (int i=0;i<num_servers;i++){
		m_vInputStart.push_back(id);
		for (int j=0;j<num_items;j++){
			for (int k=0;k<tmp_num_bits;k++,id++){
				(m_pGates+id)->type = G_XOR;
				(m_pGates+id)->right = 0;
			}
		}
		m_vInputEnd.push_back(id-1);
	}
	
	// creates gates for client inputs
	m_cliStartGate = id;
	m_vInputStart.push_back(id);
	for(int i=0;i<tot_items;i++,id++){
		(m_pGates+id)->type = G_XOR;
		(m_pGates+id)->right = 0;
	}
	m_vInputEnd.push_back(id-1);

	// creates gates for output of each party
	// servers
	for (int i=0;i<nParties-1;i++){
		// no output for servers
		m_vOutputStart.push_back(0);
		m_vOutputEnd.push_back(-1);
	}

	// output for client
	m_vOutputStart.push_back(num_gates-num_out);
	m_vOutputEnd.push_back(num_gates-1);
	for(int i=0;i<num_out;i++){
		(m_pGates+m_vOutputStart[num_servers]+i)->type = G_XOR;
		(m_pGates+m_vOutputStart[num_servers]+i)->p_num = 0;
		(m_pGates+m_vOutputStart[num_servers]+i)->right = 0;
	}

	// creates gates other than server and client's input gates
	m_othStartGate = id;
	for (int i=0;i<num_cmp;i++){
		if (i== num_cmp-1){
			is_final = 1;	
		}

		int tmp=0;
		int layer_no_tmp=-1;
		// compares with two same layers (bottom layer not included)
		assert(layer_no >= 0);
		if (layer_waiting[layer_no] == 2){
			is_alone = 0;
			//is_left = 1;///////////////////////////////
			if (is_left_before[layer_no] == 1){
				is_left = 0;
				is_left_before[layer_no] = is_left;
			}
			else if (is_left_before[layer_no] == -1){
				is_left = 1;
				is_left_before[layer_no] = is_left;
			}
			else if (is_left_before[layer_no] == 0){
				is_left = IsVSLeft(tot_items,layer_no, vs_no);
				//tmp = tot_items - 2*vs_no[layer_no];
				is_left_before[layer_no] = is_left;
			}
			
			if (is_left){
				if (layer_no >= num_layers-2){
					is_moreMUXvalue = 0;
				}
				else{
					is_moreMUXvalue = 1;
				}
			}
			else {// && num_remainders>0){
				is_moreMUXvalue = 0;
				for (int j=layer_no+1;j<num_layers-1;j++){

					#ifdef _DEBUG
					assert(j >= 0);
					#endif
					
					if (layer_waiting[j] == 1){
						is_moreMUXvalue = 1;
						break;
					}
				}
			}
			
			if (is_left){
				gates_skip = GetGatesSkip(tot_items, num_vbits, layer_no, num_vs_bottom, num_vs_middle, vs_no);
			}

			id = CreateCMP(id, is_final, num_bits, num_vbits);
			if (!is_final){
				id = CreateMUXValue(id, is_final, num_bits, num_vbits,is_left, gates_skip,is_moreMUXvalue);
			}
			id = CreateMUXIndex(id, is_final, num_bits, num_vbits, is_left, layer_no, gates_skip,is_moreMUXvalue, vs_no, is_alone, nParties);
			
			vs_no[layer_no]++;
			layer_waiting[layer_no]=0;
			
			#ifdef _DEBUG
			assert( layer_no >= 0);
			#endif
			
			layer_no++;
			layer_waiting[layer_no]++;

			#ifdef _DEBUG
			assert( layer_no <= num_layers);
			#endif
			
		}
		// compares with different layers (bottom layer not included)
		else if (num_remainders == 0){
			is_alone= 0;
			is_left = 0;

			for (int j=layer_no+1;j<num_layers;j++){

				#ifdef _DEBUG
				assert( j >= 0 );
				#endif
			
				if (layer_waiting[j] == 1){
					layer_waiting[j] = 0;
					vs_no[j]++;
					layer_no_tmp = j+1;
					break;
				}
			}
			if (layer_no_tmp == -1){
				puts("CP2PCircuit::Create(const int): layer_no_tmp is -1");		
				exit(-1);
			}

			//if (layer_no_tmp == num_layers-1){	// higher layer (one above) is the top layer
			//	is_moreMUXvalue=0;
			//}
			//else{
			//	is_moreMUXvalue=1;
			//}
			
			is_moreMUXvalue = 0;
			for (int j=layer_no_tmp;j<num_layers-1;j++){

				#ifdef _DEBUG
				assert( j >= 0 );
				#endif
		

				if (layer_waiting[j] == 1){
					is_moreMUXvalue = 1;
					break;
				}
			}

			id = CreateCMP(id, is_final, num_bits, num_vbits);
			if (!is_final){
				id = CreateMUXValue(id, is_final, num_bits, num_vbits,is_left, gates_skip,is_moreMUXvalue);
			}
			id = CreateMUXIndex(id, is_final, num_bits, num_vbits, is_left, layer_no, gates_skip,is_moreMUXvalue, vs_no, is_alone, nParties);
			
			layer_waiting[layer_no]=0;

			#ifdef _DEBUG
			assert( layer_no >= 0 && layer_no < num_layers);
			#endif
		

			layer_no = layer_no_tmp;
			layer_waiting[layer_no]++;

			//#ifdef _DEBUG
			//assert( layer_no >= 0 && layer_no < num_layers);
			//#endif
		
		}
		// compares with different layers (only one layer is bottom)
		else if (num_remainders == 1){
			layer_no = 0;
			is_alone = 1;
			is_left = 0;
			
			for (int j=layer_no+1;j<num_layers;j++){

				#ifdef _DEBUG
				assert( j >= 0 );  
				#endif
		
				if (layer_waiting[j] == 1){
					layer_waiting[j] = 0;
					vs_no[j]++;
					layer_no_tmp = j+1;
					break;
				}
			}
			if (layer_no_tmp == -1){
				puts("CP2PCircuit::Create(const int): layer_no_tmp is -1");		
				exit(-1);
			}
			/*
			if (layer_no_tmp == num_layers){	// higher layer (one above) is the top layer
				is_moreMUXvalue=0;
			}
			else{
				is_moreMUXvalue=1;
			}
			*/
			is_moreMUXvalue = 0;
			for (int j=layer_no_tmp;j<num_layers-1;j++){

				#ifdef _DEBUG
				assert( j >= 0 );  
				#endif
		
				if (layer_waiting[j] == 1){
					is_moreMUXvalue = 1;
					break;
				}
			}
			
			id = CreateANDRight(id, is_final, num_vbits, vs_no, 1);
			id = CreateCMP(id, is_final, num_bits, num_vbits);
			if (!is_final){
				id = CreateMUXValue(id, is_final, num_bits, num_vbits, is_left, gates_skip,is_moreMUXvalue);
			}
			id = CreateMUXIndex(id, is_final, num_bits, num_vbits, is_left, layer_no, gates_skip,is_moreMUXvalue, vs_no, is_alone, nParties);

			layer_no = layer_no_tmp;
			layer_waiting[layer_no]++;
			num_remainders--;

			#ifdef _DEBUG
			assert( layer_no >= 0 && layer_no < num_layers);
			#endif
		
		}
		// compares with two bottom layers
		else if (num_remainders >= 2){
			layer_no = 0;
			is_alone = 0;
			if (is_left_before[layer_no] == 1){
				is_left = 0;
				is_left_before[layer_no] = is_left;
			}
			else if (is_left_before[layer_no] == -1){
				is_left = 1;
				is_left_before[layer_no] = is_left;
			}
			else if (is_left_before[layer_no] == 0){
				is_left = IsVSLeft(tot_items,layer_no, vs_no);
				//tmp = tot_items - 2*vs_no[layer_no];
				is_left_before[layer_no] = is_left;
			}
			
			if (num_layers<=2){
				is_moreMUXvalue = 0;
			}
			else if(is_left){
				is_moreMUXvalue = 1;
			}
			else {
				is_moreMUXvalue = 0;
				for (int j=layer_no+1;j<num_layers-1;j++){

					#ifdef _DEBUG
					assert( j >= 0 );
					#endif
		
					if (layer_waiting[j] == 1){
						is_moreMUXvalue = 1;
						break;
					}
				}
			}
			if (is_left){						
				gates_skip = GetGatesSkip(tot_items, num_vbits, layer_no, num_vs_bottom, num_vs_middle, vs_no);
			}
			//id = CreateInputLeft(id, is_final, num_bits);
			//id = CreateInputRight(id, is_final, num_bits);
			id = CreateANDLeft(id, is_final, num_vbits, vs_no);
			id = CreateANDRight(id, is_final, num_vbits, vs_no, 0);
			id = CreateCMP(id, is_final, num_bits, num_vbits);
			if (!is_final){
				id = CreateMUXValue(id, is_final, num_bits, num_vbits, is_left, gates_skip, is_moreMUXvalue);
			}
			id = CreateMUXIndex(id, is_final, num_bits, num_vbits, is_left, layer_no, gates_skip,is_moreMUXvalue, vs_no, is_alone, nParties);
			
			vs_no[layer_no]++;
			layer_no = 1;
			layer_waiting[layer_no]++;
			num_remainders -= 2;

			#ifdef _DEBUG
			assert( layer_no >= 0 && layer_no < num_layers);
			#endif
		
		}
	}

	#ifdef _DEBUG
	cout << "final gate id: " << id-1+num_out << endl;
	#endif

	delete [] layer_waiting;
	delete [] vs_no;
	delete [] is_left_before; 

	m_nNumParties = m_nNumServers + 1;
	m_vInputStart.resize(m_nNumParties);
	m_vInputEnd.resize(m_nNumParties);

	//for(int i=0; i<m_nNumParties; i++)
	//{
	//	m_vInputStart[i] = GetInputStartC(i);
	//	m_vInputEnd[i] = GetInputEndC(i);
	//}

	#ifdef _DEBUG
	cout << "input start gate id1: " << m_vInputStart[0] << endl;
	cout << "input end gate id1: " << m_vInputEnd[0] << endl;
	cout << "input start gate id2: " << m_vInputStart[1] << endl;
	cout << "input end gate id2: " << m_vInputEnd[1] << endl;
	cout << "input start gate id3: " << m_vInputStart[2] << endl;
	cout << "input end gate id3: " << m_vInputEnd[2] << endl;
	cout << "output start gate id1: " << m_vOutputStart[0] << endl;
	cout << "output end gate id1: " << m_vOutputEnd[0] << endl;
	cout << "output start gate id2: " << m_vOutputStart[1] << endl;
	cout << "output end gate id2: " << m_vOutputEnd[1] << endl;
	cout << "output start gate id3: " << m_vOutputStart[2] << endl;
	cout << "output end gate id3: " << m_vOutputEnd[2] << endl;
	#endif

	return TRUE;
}