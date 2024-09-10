bool moveIsDP(Move move) {
	assert(moveIsValid(move));
	int toRank=sqRank(moveGetToSqRaw(move));
	int fromRank=sqRank(moveGetFromSq(move));
	return (moveGetToPieceType(move)==PieceTypePawn && abs(toRank-fromRank)==2);
}