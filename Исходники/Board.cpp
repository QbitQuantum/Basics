/*
* @method
*   void Board::possibleStates(vector<Board> states)
*     - populates a vector<Board> with all possible neighbors of the board's current state
*   Author: Mark Sands
*   Date modified: 2-1-11
*/
void Board::possibleStates(std::vector<Board>& states)
{
    states.clear();

    u_int32 maxJumps = 4;

    /** One Tile Moves **/

    if ( validMoveToPosition(MOVES[NORTH], NORTH) ) {
        maxJumps--;
        Board temp = swap(emptySlotIndex, emptySlotIndex.movePositionTo(MOVES[NORTH]));
        if ( !hash.isThere(temp.chargrid) ) {
            std::auto_ptr<Board> node(new Board(*this));
            temp.parent_ = node.release();
            // heuristic
            temp.distance(emptySlotIndex);
            temp.numberOfWrongTokens();
            hash.insertEntry(temp.chargrid);
            states.push_back(temp);
        }
    }

    if ( maxJumps == 0 ) return;
    if ( validMoveToPosition(MOVES[EAST], EAST) ) {
        maxJumps--;
        Board temp = swap(emptySlotIndex, emptySlotIndex.movePositionTo(MOVES[EAST]));
        if ( !hash.isThere(temp.chargrid) ) {
            std::auto_ptr<Board> node(new Board(*this));
            temp.parent_ = node.release();
            // heuristic
            temp.distance(emptySlotIndex);
            temp.numberOfWrongTokens();
            hash.insertEntry(temp.chargrid);
            states.push_back(temp);
        }
    }

    if ( maxJumps == 0 ) return;
    if ( validMoveToPosition(MOVES[SOUTH], SOUTH) ) {
        maxJumps--;
        Board temp = swap(emptySlotIndex, emptySlotIndex.movePositionTo(MOVES[SOUTH]));
        if ( !hash.isThere(temp.chargrid) ) {
            std::auto_ptr<Board> node(new Board(*this));
            temp.parent_ = node.release();
            // heuristic
            temp.distance(emptySlotIndex);
            temp.numberOfWrongTokens();
            hash.insertEntry(temp.chargrid);
            states.push_back(temp);
        }
    }

    if ( maxJumps == 0 ) return;
    if ( validMoveToPosition(MOVES[WEST], WEST) ) {
        maxJumps--;
        Board temp = swap(emptySlotIndex, emptySlotIndex.movePositionTo(MOVES[WEST]));
        if ( !hash.isThere(temp.chargrid) ) {
            std::auto_ptr<Board> node(new Board(*this));
            temp.parent_ = node.release();
            // heuristic
            temp.distance(emptySlotIndex);
            temp.numberOfWrongTokens();
            hash.insertEntry(temp.chargrid);
            states.push_back(temp);
        }
    }

    /** Two Tile Moves **/

    if ( maxJumps == 0 ) return;
    if ( validJumpToPosition(JUMPS[NORTH], NORTH) ) {
        maxJumps--;
        Board temp = swap(emptySlotIndex, emptySlotIndex.movePositionTo(JUMPS[NORTH]));
        if ( !hash.isThere(temp.chargrid) ) {
            std::auto_ptr<Board> node(new Board(*this));
            temp.parent_ = node.release();
            // heuristic
            temp.distance(emptySlotIndex);
            temp.numberOfWrongTokens();
            hash.insertEntry(temp.chargrid);
            states.push_back(temp);
        }
    }

    if ( maxJumps == 0 ) return;
    if ( validJumpToPosition(JUMPS[EAST], EAST) ) {
        maxJumps--;
        Board temp = swap(emptySlotIndex, emptySlotIndex.movePositionTo(JUMPS[EAST]));
        if ( !hash.isThere(temp.chargrid) ) {
            std::auto_ptr<Board> node(new Board(*this));
            temp.parent_ = node.release();
            // heuristic
            temp.distance(emptySlotIndex);
            temp.numberOfWrongTokens();
            hash.insertEntry(temp.chargrid);
            states.push_back(temp);
        }
    }

    if ( maxJumps == 0 ) return;
    if ( validJumpToPosition(JUMPS[SOUTH], SOUTH) ) {
        maxJumps--;
        Board temp = swap(emptySlotIndex, emptySlotIndex.movePositionTo(JUMPS[SOUTH]));
        if ( !hash.isThere(temp.chargrid) ) {
            std::auto_ptr<Board> node(new Board(*this));
            temp.parent_ = node.release();
            // heuristic
            temp.distance(emptySlotIndex);
            temp.numberOfWrongTokens();
            hash.insertEntry(temp.chargrid);
            states.push_back(temp);
        }
    }

    if ( maxJumps == 0 ) return;
    if ( validJumpToPosition(JUMPS[WEST], WEST) ) {
        maxJumps--;
        Board temp = swap(emptySlotIndex, emptySlotIndex.movePositionTo(JUMPS[WEST]));
        if ( !hash.isThere(temp.chargrid) ) {
            std::auto_ptr<Board> node(new Board(*this));
            temp.parent_ = node.release();
            // heuristic
            temp.distance(emptySlotIndex);
            temp.numberOfWrongTokens();
            hash.insertEntry(temp.chargrid);
            states.push_back(temp);
        }
    }

}