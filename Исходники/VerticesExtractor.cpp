void VerticesExtractor::process(int*m_mode_send_vertices_sequence_id,
				ArrayOfReads*m_myReads,
				bool*m_reverseComplementVertex,
				int rank,
				StaticVector*m_outbox,
				bool*m_mode_send_vertices,
				int wordSize,
				int size,
				RingAllocator*m_outboxAllocator,
				int*m_mode
				){
	if(this->m_outbox==NULL){
		m_rank=rank;
		this->m_mode=m_mode;
		this->m_outbox=m_outbox;
		this->m_outboxAllocator=m_outboxAllocator;
	}
	#ifdef ASSERT
	assert(m_pendingMessages>=0);
	#endif
	if(m_pendingMessages!=0){
		return;
	}

	if(m_finished){
		return;
	}

	if(*m_mode_send_vertices_sequence_id%100000==0 &&m_mode_send_vertices_sequence_id_position==0
	&&*m_mode_send_vertices_sequence_id<(int)m_myReads->size()){
		string reverse="";
		if(*m_reverseComplementVertex==true){
			reverse="(reverse complement) ";
		}
		printf("Rank %i is computing vertices & edges %s[%i/%i]\n",rank,reverse.c_str(),(int)*m_mode_send_vertices_sequence_id+1,(int)m_myReads->size());
		fflush(stdout);
	}

	if(*m_mode_send_vertices_sequence_id>(int)m_myReads->size()-1){
		// flush data
		flushAll(m_outboxAllocator,m_outbox,rank);
		if(m_pendingMessages==0){
			#ifdef ASSERT
			assert(m_bufferedData.isEmpty());
			assert(m_bufferedDataForIngoingEdges.isEmpty());
			assert(m_bufferedDataForOutgoingEdges.isEmpty());
			#endif

			Message aMessage(NULL,0, MASTER_RANK, RAY_MPI_TAG_VERTICES_DISTRIBUTED,rank);
			m_outbox->push_back(aMessage);
			m_finished=true;
			printf("Rank %i is computing vertices & edges [%i/%i] (completed)\n",rank,(int)*m_mode_send_vertices_sequence_id,(int)m_myReads->size());
			fflush(stdout);
			m_bufferedData.showStatistics(m_parameters->getRank());
			m_bufferedDataForIngoingEdges.showStatistics(m_parameters->getRank());
			m_bufferedDataForOutgoingEdges.showStatistics(m_parameters->getRank());
		}
	}else{
		if(m_mode_send_vertices_sequence_id_position==0){
			(*m_myReads)[(*m_mode_send_vertices_sequence_id)]->getSeq(m_readSequence,m_parameters->getColorSpaceMode(),false);
		
			//cout<<"DEBUG Read="<<*m_mode_send_vertices_sequence_id<<" color="<<m_parameters->getColorSpaceMode()<<" Seq= "<<m_readSequence<<endl;
		}
		int len=strlen(m_readSequence);

		if(len<wordSize){
			m_hasPreviousVertex=false;
			(*m_mode_send_vertices_sequence_id)++;
			(m_mode_send_vertices_sequence_id_position)=0;
			return;
		}

		char memory[1000];
		int lll=len-wordSize+1;
		
		#ifdef ASSERT
		assert(m_readSequence!=NULL);
		#endif

		int p=(m_mode_send_vertices_sequence_id_position);
		memcpy(memory,m_readSequence+p,wordSize);
		memory[wordSize]='\0';
		if(isValidDNA(memory)){
			Kmer a=wordId(memory);

			int rankToFlush=0;

			rankToFlush=m_parameters->_vertexRank(&a);
			for(int i=0;i<KMER_U64_ARRAY_SIZE;i++){
				m_bufferedData.addAt(rankToFlush,a.getU64(i));
			}

			if(m_bufferedData.flush(rankToFlush,KMER_U64_ARRAY_SIZE,RAY_MPI_TAG_VERTICES_DATA,m_outboxAllocator,m_outbox,rank,false)){
				m_pendingMessages++;
			}

			if(m_hasPreviousVertex){
				// outgoing edge
				int outgoingRank=m_parameters->_vertexRank(&m_previousVertex);
				for(int i=0;i<KMER_U64_ARRAY_SIZE;i++){
					m_bufferedDataForOutgoingEdges.addAt(outgoingRank,m_previousVertex.getU64(i));
				}
				for(int i=0;i<KMER_U64_ARRAY_SIZE;i++){
					m_bufferedDataForOutgoingEdges.addAt(outgoingRank,a.getU64(i));
				}

				if(m_bufferedDataForOutgoingEdges.needsFlushing(outgoingRank,2*KMER_U64_ARRAY_SIZE)){
					if(m_bufferedData.flush(outgoingRank,KMER_U64_ARRAY_SIZE,RAY_MPI_TAG_VERTICES_DATA,m_outboxAllocator,m_outbox,rank,true)){
						m_pendingMessages++;
					}
				}

				if(m_bufferedDataForOutgoingEdges.flush(outgoingRank,2*KMER_U64_ARRAY_SIZE,RAY_MPI_TAG_OUT_EDGES_DATA,m_outboxAllocator,m_outbox,rank,false)){
					m_pendingMessages++;
				}

				// ingoing edge
				int ingoingRank=m_parameters->_vertexRank(&a);
				for(int i=0;i<KMER_U64_ARRAY_SIZE;i++){
					m_bufferedDataForIngoingEdges.addAt(ingoingRank,m_previousVertex.getU64(i));
				}
				for(int i=0;i<KMER_U64_ARRAY_SIZE;i++){
					m_bufferedDataForIngoingEdges.addAt(ingoingRank,a.getU64(i));
				}

				if(m_bufferedDataForIngoingEdges.needsFlushing(ingoingRank,2*KMER_U64_ARRAY_SIZE)){
					if(m_bufferedData.flush(ingoingRank,KMER_U64_ARRAY_SIZE,RAY_MPI_TAG_VERTICES_DATA,m_outboxAllocator,m_outbox,rank,true)){
						m_pendingMessages++;
					}
				}

				if(m_bufferedDataForIngoingEdges.flush(ingoingRank,2*KMER_U64_ARRAY_SIZE,RAY_MPI_TAG_IN_EDGES_DATA,m_outboxAllocator,m_outbox,rank,false)){
					m_pendingMessages++;
				}
			}

			// reverse complement
			Kmer b=complementVertex(&a,wordSize,m_parameters->getColorSpaceMode());

			rankToFlush=m_parameters->_vertexRank(&b);
			for(int i=0;i<KMER_U64_ARRAY_SIZE;i++){
				m_bufferedData.addAt(rankToFlush,b.getU64(i));
			}

			if(m_bufferedData.flush(rankToFlush,KMER_U64_ARRAY_SIZE,RAY_MPI_TAG_VERTICES_DATA,m_outboxAllocator,m_outbox,rank,false)){
				m_pendingMessages++;
			}

			if(m_hasPreviousVertex){
				// outgoing edge
				int outgoingRank=m_parameters->_vertexRank(&b);
				for(int i=0;i<KMER_U64_ARRAY_SIZE;i++){
					m_bufferedDataForOutgoingEdges.addAt(outgoingRank,b.getU64(i));
				}
				for(int i=0;i<KMER_U64_ARRAY_SIZE;i++){
					m_bufferedDataForOutgoingEdges.addAt(outgoingRank,m_previousVertexRC.getU64(i));
				}

				if(m_bufferedDataForOutgoingEdges.needsFlushing(outgoingRank,2*KMER_U64_ARRAY_SIZE)){
					if(m_bufferedData.flush(outgoingRank,1*KMER_U64_ARRAY_SIZE,RAY_MPI_TAG_VERTICES_DATA,m_outboxAllocator,m_outbox,rank,true)){
						m_pendingMessages++;
					}
				}

				if(m_bufferedDataForOutgoingEdges.flush(outgoingRank,2*KMER_U64_ARRAY_SIZE,RAY_MPI_TAG_OUT_EDGES_DATA,m_outboxAllocator,m_outbox,rank,false)){
					m_pendingMessages++;
				}

				// ingoing edge
				int ingoingRank=m_parameters->_vertexRank(&m_previousVertexRC);
				for(int i=0;i<KMER_U64_ARRAY_SIZE;i++){
					m_bufferedDataForIngoingEdges.addAt(ingoingRank,b.getU64(i));
				}
				for(int i=0;i<KMER_U64_ARRAY_SIZE;i++){
					m_bufferedDataForIngoingEdges.addAt(ingoingRank,m_previousVertexRC.getU64(i));
				}

				if(m_bufferedDataForIngoingEdges.needsFlushing(ingoingRank,2*KMER_U64_ARRAY_SIZE)){
					if(m_bufferedData.flush(ingoingRank,1*KMER_U64_ARRAY_SIZE,RAY_MPI_TAG_VERTICES_DATA,m_outboxAllocator,m_outbox,rank,true)){
						m_pendingMessages++;
					}
				}

				if(m_bufferedDataForIngoingEdges.flush(ingoingRank,2*KMER_U64_ARRAY_SIZE,RAY_MPI_TAG_IN_EDGES_DATA,m_outboxAllocator,m_outbox,rank,false)){
					m_pendingMessages++;
				}
			}

			// there is a previous vertex.
			m_hasPreviousVertex=true;
			m_previousVertex=a;
			m_previousVertexRC=b;
		}else{
			m_hasPreviousVertex=false;
		}

		(m_mode_send_vertices_sequence_id_position++);
		if((m_mode_send_vertices_sequence_id_position)==lll){
			m_hasPreviousVertex=false;
			(*m_mode_send_vertices_sequence_id)++;
			(m_mode_send_vertices_sequence_id_position)=0;
		}
	}
}