/*=============================================================================
	Purpose: To shuffle the cards in the Deck into some random order.
=============================================================================*/
void Deck::Shuffle()
{
	srand(static_cast<int>(time(0)));

	for(int i = 0; i < MAX_NUMBER_OF_CARDS; i++)
	{
		int RandomNumber = rand() % MAX_NUMBER_OF_CARDS;

		Card Temp = m_Deck[i];
		m_Deck[i] = m_Deck[RandomNumber];
		m_Deck[RandomNumber] = Temp;
	}
	m_Current_Card = 0;
}