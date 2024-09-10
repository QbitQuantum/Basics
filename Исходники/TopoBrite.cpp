	void TopoBrite::Read(const char* fileName)
	{
		// Open file
		FILE* file = NULL;
		if(FILE_OPEN(file, fileName, "r")) throw ExceptionIo(__FILE__, __LINE__, "TopoBrite::Read : cannot open file %s.", fileName);

		// Read header
	#ifdef _MSC_VER
		if(fscanf_s(file, "Topology: ( %u Nodes, %u Edges )\n", &this->numNodes, &this->numEdges) != 2)
			throw ExceptionIo(__FILE__, __LINE__, "TopoBrite::Read : cannot read topology line.");
		if(fscanf_s(file, "Model (%u - %s  ",
			&this->model,
			this->modelName,
			32) != 2)
			throw ExceptionIo(__FILE__, __LINE__, "TopoBrite::Read : cannot read model line.");
	#else
		if(fscanf(file, "Topology: ( %u Nodes, %u Edges )\n", &this->numNodes, &this->numEdges) != 2)
			throw ExceptionIo(__FILE__, __LINE__, "TopoBrite::Read : cannot read model line.");
		if(fscanf(file, "Model (%u - %s  ",
			&this->model,
			this->modelName) != 2)
			throw ExceptionIo(__FILE__, __LINE__, "TopoBrite::Read : cannot read model line.");
	#endif

		uint numNodes;

		double bwMin;
		double bwMax;

		switch(model)
		{
		case TOPO_BRITE_MODEL_WAXMAN:
	#ifdef _MSC_VER
			if(fscanf_s(file, "%u %u %u %u %u %lf %lf %u %u %lf %lf \n\n",
				&numNodes,
				&this->hs,
				&this->ls,
				&this->nodePlacement,
				&this->nodeLinks,
				&this->alpha,
				&this->beta,
				&this->growthType,
				&this->bwDist,
				&bwMin,
				&bwMax) != 11) throw ExceptionIo(__FILE__, __LINE__, "TopoBrite::Read : cannot read topology line.");
	#else
			if(fscanf(file, "%u %u %u %u %u %lf %lf %u %u %lf %lf \n\n",
				&numNodes,
				&this->hs,
				&this->ls,
				&this->nodePlacement,
				&this->nodeLinks,
				&this->alpha,
				&this->beta,
				&this->growthType,
				&this->bwDist,
				&bwMin,
				&bwMax) != 11) throw ExceptionIo(__FILE__, __LINE__, "TopoBrite::Read : cannot read topology line.");
	#endif
			break;
		default: throw ExceptionUnsupported(__FILE__, __LINE__, "TopoBrite::Read : model %u not supported.", model);
		}
		assert(this->numNodes == numNodes);

		this->bwMax = (__bitrate)ceil(bwMax);
		this->bwMin = (__bitrate)ceil(bwMin);

		// Read nodes
	#ifdef _MSC_VER
		if(fscanf_s(file, "Nodes: ( %u )\n", &numNodes) != 1) throw ExceptionIo(__FILE__, __LINE__, "TopoBrite::Read : cannot read nodes line.");
	#else
		if(fscanf(file, "Nodes: ( %u )\n", &numNodes) != 1) throw ExceptionIo(__FILE__, __LINE__, "TopoBrite::Read : cannot read nodes line.");
	#endif
		assert(this->numNodes == numNodes);

		this->nodes = alloc TopoBriteNode*[this->numNodes];
		assert(this->nodes);

		uint id;
		uint xpos;
		uint ypos;
		uint inDegree;
		uint outDegree;
		int as;
		char type[16];

		for(uint index = 0; index < this->numNodes; index++)
		{
	#ifdef _MSC_VER
			if(fscanf_s(file, "%u %u %u %u %u %d %s\n", &id, &xpos, &ypos, &inDegree, &outDegree, &as, type, 16) != 7) throw ExceptionIo(__FILE__, __LINE__, "TopoBrite::Read : cannot read node line.");
	#else
			if(fscanf(file, "%u %u %u %u %u %d %s\n", &id, &xpos, &ypos, &inDegree, &outDegree, &as, type) != 7) throw ExceptionIo(__FILE__, __LINE__, "TopoBrite::Read : cannot read node line.");
	#endif
			assert(id == index);
			assert(inDegree == outDegree);

			this->nodes[index] = alloc TopoBriteNode(
				index,
				xpos,
				ypos,
				inDegree
				);
			assert(this->nodes[index]);
		}

		// Read edges
		uint numEdges;
	#ifdef _MSC_VER
		if(fscanf_s(file, "\n\nEdges: ( %u )\n", &numEdges) != 1) throw ExceptionIo(__FILE__, __LINE__, "TopoBrite::Read : cannot read edges line.");
	#else
		if(fscanf(file, "\n\nEdges: ( %u )\n", &numEdges) != 1) throw ExceptionIo(__FILE__, __LINE__, "TopoBrite::Read : cannot read edges line.");
	#endif
		assert(this->numEdges == numEdges);

		this->edges = alloc TopoBriteEdge*[this->numEdges];
		assert(this->edges);

		uint from;
		uint to;
		double length;
		double delay;
		double bw;
		int asFrom;
		int asTo;
		char val;

		for(uint index = 0; index < this->numEdges; index++)
		{
	#ifdef _MSC_VER
			if(fscanf_s(file, "%u %u %u %lf %lf %lf %d %d %s %c\n", &id, &from, &to, &length, &delay, &bw, &asFrom, &asTo, type, 16, &val) != 10)
				throw ExceptionIo(__FILE__, __LINE__, "TopoBrite::Read : cannot read edge line.");
	#else
			if(fscanf(file, "%u %u %u %lf %lf %lf %d %d %s %c\n", &id, &from, &to, &length, &delay, &bw, &asFrom, &asTo, type, &val) != 10)
				throw ExceptionIo(__FILE__, __LINE__, "TopoBrite::Read : cannot read edge line.");
	#endif
			assert(id == index);

			if(bw > this->bwMax) bw = (double)this->bwMax;
			if(bw < this->bwMin) bw = (double)this->bwMin;

			// Set the edge for the nodes
			uint entryFrom = this->nodes[from]->SetEdge(index);
			uint entryTo = this->nodes[to]->SetEdge(index);

			// Create the edge
			this->edges[index] = alloc TopoBriteEdge(index, from, to, entryFrom, entryTo, length, delay / 1000, (__bitrate)ceil(bw));
		}

		// Close file
		fclose(file);
	}