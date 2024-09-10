bool Dictionary::deleteTranslation(String& word) {
	Translation *translation = new Translation();
	Translation *current = this->translation;
	Translation *previous = NULL;
	Translation *next = NULL;

	// Hack! We don't know if the word is english or finnish so we set it to both
	translation->insertFinnishWord(word);
	translation->insertEnglishWord(word);

	while (current != NULL) {

		if (strcmp(translation->getEnglishLowerCase(), current->getEnglishLowerCase()) == 0 
			|| strcmp(translation->getFinnishLowerCase(), current->getFinnishLowerCase()) == 0 ) {
				next = current->getNext();
				previous = current->getPrevious();

				if (current->hasPrevious()) {
					previous->setNext(next);
				}

				if (current->hasNext()) {
					next->setPrevious(previous);
				}

				// Special case: word is the only element in the linked list
				if (!current->hasPrevious() && !current->hasNext()) {
					this->translation = NULL;
				} else if (!current->hasPrevious()) {
					// Special case: word is the first in the linked list
					this->translation = next;
				}else if (!current->hasNext()) {
					// Special case: word is the last in the linked list
					previous->setNext(NULL);
				}

				delete current;

				resetTranslationBrowsing();
				return true;
		}
		current = current->getNext();
	}

	cout << "Word " << word <<  " not found" << endl;
	return false;
}