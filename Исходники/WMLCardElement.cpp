WMLCardElement* WMLCardElement::determineActiveCard(Document* doc)
{
    WMLPageState* pageState = wmlPageStateForDocument(doc);
    if (!pageState)
        return 0;

    RefPtr<NodeList> nodeList = doc->getElementsByTagName("card");
    if (!nodeList)
        return 0;

    unsigned length = nodeList->length();
    if (length < 1)
        return 0;

    // Figure out the new target card
    String cardName = doc->url().fragmentIdentifier();

    WMLCardElement* activeCard = findNamedCardInDocument(doc, cardName);
    if (activeCard) {
        // Hide all cards - except the destination card - in document
        for (unsigned i = 0; i < length; ++i) {
            WMLCardElement* card = static_cast<WMLCardElement*>(nodeList->item(i));

            if (card == activeCard)
                card->showCard();
            else
                card->hideCard();
        }
    } else {
        // If the target URL didn't contain a fragment identifier, activeCard
        // is 0, and has to be set to the first card element in the deck.
        activeCard = static_cast<WMLCardElement*>(nodeList->item(0));
        activeCard->showCard();
    }

    // Assure destination card is visible
    ASSERT(activeCard->isVisible());
    ASSERT(activeCard->attached());
    ASSERT(activeCard->renderer());

    // Update the document title
    doc->setTitle(activeCard->title());
#if ENABLE(WMLSCRIPT)
    static_cast<WMLDocument*>(doc)->setActiveCardId(activeCard->getIDAttribute()) ;
#endif

    // SAMSUNG_WML_FIXES+
    // Set the active activeCard in the Document object
    static_cast<WMLDocument*>(doc)->setActiveCard(activeCard);

    // Set the active activeCard in the WMLPageState object
    //pageState->setActiveCard(activeCard);
    // SAMSUNG_WML_FIXES-
    return activeCard;
}