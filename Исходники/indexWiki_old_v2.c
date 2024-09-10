/**
 * filters, transforms, and indexes file using ngrams to the index
 * 
 * file name - name of file to process
 * wikiindex - the judy arrays to store the index of the wiki in
 */
void indexWiki(char* inFileName, Pvoid_t *wikiIndex, int* articleCount) {
	
	//-------------------- initialization --------------------//
	bool articleIndex[lastNgram] = {0}; // boolean array of what trigrams are in an article
	struct stemmer * currentStemmer = create_stemmer();
	
	// file for writing the titles to
	FILE* titleFile = NULL;
	if (writeFiles) {
		titleFile = fopen("title_file", "w");
		if (NULL == titleFile) {
			fprintf(stderr, "Error open title file: %m\n");
			exit(1);
		}
	}
	
	// initializes the libxml library
	LIBXML_TEST_VERSION
	xmlTextReaderPtr wikiReader; //the reader for the document
	wikiReader = xmlReaderForFile(inFileName, NULL, XML_PARSE_RECOVER+XML_PARSE_NOWARNING+XML_PARSE_NOERROR+XML_PARSE_HUGE);
	if (NULL == wikiReader) {
		//fprintf(stderr, "%s %s\n", "Failed to open ", wikiFileName);
		fprintf(stderr, "Error opening XML wiki: %m\n");
		exit(1);
	}

	// for progress bar
	int percent = 0;
	long fileSize = getFileSize(inFileName);
	
	// initialization for currentArticle and its componens 
	article currentArticle;	
	currentArticle.title = g_string_sized_new(256);
	currentArticle.body  = g_string_sized_new(786432); //768*1024

	//-------------------- index the wiki --------------------//
	optionalPrint ("%s", "Adding collection to index.\n");
	optionalPrint ("%d", (int)(fileSize / 1048576));
	optionalPrint (" MB in file\n");
	displayProgressBar (xmlTextReaderByteConsumed(wikiReader), fileSize, &percent);
	 
	//prime the loop
	currentArticle.title->len = 0;
	currentArticle.body->len  = 0;
	xmlTextReaderRead(wikiReader);// at a <page> tag, drop in
	xmlTextReaderRead(wikiReader);// at a <page> tag, drop in
	 
	// reads from xml file until file is finished, adds articles to index, and writes tittles to file
	// processes one article per iteration
	while (getArticle (wikiReader, &currentArticle)) {
		currentArticle.articleNumber = *articleCount;
		*articleCount = *articleCount + 1;
		// filter / transform text
		removeMarkup(currentArticle.body);
		stemText(currentArticle.body, currentStemmer); //ngramming.h
		// index the text
		indexText(currentArticle.body, articleIndex); //ngramming.h
		addToIndex(articleIndex, wikiIndex, currentArticle.articleNumber);
		//adds titles to title file
		if (writeFiles) {fprintf(titleFile, "%s\n", currentArticle.title->str);}
		//re-prime the loop
		currentArticle.title->len = 0;
		currentArticle.body->len  = 0;
		displayProgressBar (xmlTextReaderByteConsumed(wikiReader), fileSize, &percent);
	}
	optionalPrint ("\n%s", "Finished indexing. \n");
	optionalPrint ("%lu", (long)(xmlTextReaderByteConsumed(wikiReader)/1048576));
	optionalPrint ("MB consumed\n");
	
	
	optionalPrint ("%d %s %d %s", *articleCount, "articles found", (int) currentArticle.body->allocated_len, "length allocated for article body\n");
	// clean up of structures needed to process wiki
	if (writeFiles) {fclose (titleFile);}
	free_stemmer(currentStemmer);
	xmlFreeTextReader(wikiReader);
	xmlCleanupParser();
	//g_string_free(currentArticle.title, TRUE);
	//g_string_free(currentArticle.body, TRUE); //malloc fail if this is uncommented ?!
}