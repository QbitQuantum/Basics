Pokemon* Pokemon::GenerateEgg(Pokemon* mother, Pokemon* father)
{
	u16 motherItem = mother->Decrypt(HeldItem);
	//u16 fatherItem = PokemonDecrypter(father, HeldItem);
	u16 species = mother->Decrypt(Species);
	if (pokemonBaseData[species].eggGroup1 == EGG_GROUP_DITTO && pokemonBaseData[species].eggGroup2 == EGG_GROUP_DITTO)
	{
		species = father->Decrypt(Species);
	}
	species = FindBabySpeciesInner(species);
	if (species == Manaphy)
	{
		species = Phione;
	}
	for (int i = 0; i < 3; i++)
	{
		if (species == alternativeSpeciesChecks[i][0])
		{
			species = alternativeSpeciesChecks[i][Maths::GetDelimitedRandom32BitValue(2)];
			break;
		}
	}
	for (int i = 0; i < 9; i++)
	{
		if (species == incenseItemEggs[i].foundSpecies)
		{
			if (motherItem != incenseItemEggs[i].itemID && motherItem != incenseItemEggs[i].itemID)
			{
				species = incenseItemEggs[i].alternativeSpecies;
			}
			break;
		}
	}
	Pokemon* egg = new Pokemon(0, species);
	egg->Encrypt(IsEgg, true);
	egg->Encrypt(Friendship, pokemonBaseData[species].hatchSteps);
	// Calculate Egg Moves and award where necessary
	return egg;
}