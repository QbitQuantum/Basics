void InvertedIndex::indexing(Tokenizer& t, int index){
	unordered_set<string> docs_words;

	/* A file must be indexed entirely, so it is possible to calculate total number of terms in a same file.
		To do so, it is calculate the necessaary space to store this one file and the actual size of index.
		If it is going to be bigger than memory size, dump index first.
	*/
	if ((this->memory_usage) && (((t.size()*INDEX_LINE_SIZE)+this->memory_usage) >= MEMORY_LIMITE)){
		this->memory_dump();
	}

	if (t.size() > 0){
		this->total_docs++;
	}

	// Iterating through tokens
	int word_id = 0;
	while (t.size() > 0){
		string token = t.getToken();

		if (token.size()) {
			this->total_token++;

			docs_words.insert(token);

			// Testing if token is not already in the vocabulary
			auto search = this->vocabulary.find(token);
			if (search == this->vocabulary.end()){

				// Adding to vocabulary hash
				this->vocabulary[token] = this->word_index;

				// Saving group of vocabulary info
				Vocabulary item;
				item.word = token;
				item.id = this->word_index;
				item.file_pos = 0;		// Unknown right now
				item.total_docs = 0;	// Unknown right now
				item.idf = -1;			// Unknown right now

				this->vocabulary_order.push_back(item);

				// Updating word index in the vocabulary
				this->word_index++;
			}

			// Testing if token is not already in the index
			auto search2 = this->inverted_index.find(token);

			// Testing if token had already been seen in document index
			if (search2 != this->inverted_index.end() &&					// Testing if token is in index
				this->inverted_index[token].size() > 0 &&
				this->inverted_index[token].back().file_index == index) {
					this->inverted_index[token].back().position.push_back(word_id);
			}
			else {
				FileList list;
				list.file_index = index;
				list.position.push_back(word_id);

				this->inverted_index[token].push_back(list);
			}

			this->memory_usage+=INDEX_LINE_SIZE;

			word_id++;

			if (this->memory_usage >= MEMORY_LIMITE){
				this->memory_dump();
			}
		}
	}

	// Updating n_i
	for (string word : docs_words){
		this->vocabulary_order[this->vocabulary[word]].total_docs++;
	}
}