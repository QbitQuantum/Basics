bool solvePuzzle(Grid<MarbleType>& board, int marblesLeft, Set<uint32_t>& exploredBoards,
                 Vector<Move>& moveHistory){
    /* TODO: COMPLETE THIS */
    if (exploredBoards.size()%10000 == 0){
               cout << "Boards evaluated: " << exploredBoards.size()
                    << "\tDepth: " << moveHistory.size() << endl;
               cout.flush();
    }
    if(marblesLeft == 1)
        return true;
    if(exploredBoards.contains(compressMarbleBoard(board)))
        return false;
    exploredBoards.add(compressMarbleBoard(board));
    Vector<Move> moves = findPossibleMoves(board);
    for(int i=0; i<moves.size(); ++i){
         Move move = moves[i];
         makeMove(move, board);
         moveHistory.add(move);
         if(solvePuzzle(board, marblesLeft-1,exploredBoards, moveHistory))
         {
             return true;
         }
         else{
             undoMove(move, board);
             moveHistory.remove(moveHistory.size()-1);
         }
    }
    return false;
}