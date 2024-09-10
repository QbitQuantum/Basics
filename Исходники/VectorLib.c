// Calcule le minimum membre a membre de deux tableaux de Packed Single SSE (= 4 floats) dans un troisieme tableau
// La taille est exprimee en nombre de vecteurs (et pas en nombre de floats)
// Les tableaux doivent etre alignes sur des frontieres de 16 octets
void minimumVecteur_Et_Dans_DeTaille(__m128 *source1, __m128 *source2, __m128 *destination, int taille)
{
	int compteur;
	
	for (compteur = 0; compteur < taille; ++compteur)
		*destination++ = _mm_min_ps(*source1++, *source2++);
}