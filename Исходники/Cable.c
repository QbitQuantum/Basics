static void
reverse(Cable *cable) {
	SWAP(cable->c1, cable->c2);
	SWAP(cable->x1, cable->x2);
	SWAP(cable->y1, cable->y2);
}