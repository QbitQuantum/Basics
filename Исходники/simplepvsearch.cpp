// principal variation search
int SimplePVSearch::pvSearch(Board& board, SearchInfo& si) {
	if (stop(si)) {
		return 0;
	}
	if (si.ply>maxPlySearched) {
		maxPlySearched=si.ply;
	}
	if (si.depth<=0) {
		si.update(0,PV_NODE);
		return qSearch(board, si);
	}
	if	(board.isDraw() || si.ply >= maxSearchPly-1) {
		return drawScore;
	}
	const int oldAlpha = si.alpha;
	int score = -maxScore;
	int currentScore = -maxScore;
	bool okToPrune=false;
	si.alpha = std::max(-maxScore+si.ply, si.alpha);
	si.beta = std::min(maxScore-(si.ply+1), si.beta);
	if (si.alpha>=si.beta) {
		return si.alpha;
	}
	TranspositionTable::HashData hashData;
	MoveIterator::Move hashMove;
	const Key key = si.partialSearch?board.getPartialSearchKey():board.getKey();
	// tt retrieve & prunning
	bool hashOk = agent->hashGet(okToPrune, key, hashData, si.ply, si.depth);
	if (hashOk) {
		hashMove = hashData.move();
		if (okToPrune) {
			return hashData.value();
		}
	}
	const bool isKingAttacked = board.isInCheck();
	bool isLazyEval=false;
	if (!isKingAttacked) {
		if (hashOk && (hashData.flag() & TranspositionTable::NODE_EVAL)) {
			currentScore = hashData.evalValue();
		} else {
			currentScore = evaluator.evaluate(board,si.alpha,si.beta);
			isLazyEval = evaluator.isLazyEval();
		}
	}
	//iid
	if (si.depth > allowIIDAtPV &&	hashMove.none()) {
		SearchInfo newSi(false,emptyMove,si.alpha,si.beta,si.depth-2,si.ply,PV_NODE,si.splitPoint);
		score = pvSearch(board,newSi);
		hashOk = agent->hashGet(key, hashData, si.ply);
		if (hashOk) {
			hashMove = hashData.move();
		}
	}
	MoveIterator moves = MoveIterator();
	MoveIterator::Move bestMove=emptyMove;
	MoveIterator::Move move;
	int moveCounter=0;
	int bestScore=-maxScore;
	bool nmMateScore=false;
	while (true) {
		move = selectMove<false>(board, moves, hashMove, si.ply, si.depth);
		if (move.none()) {
			break;
		}
		if (si.partialSearch && move == si.move) {
			continue;
		}
		const bool isHashMove = move.type==MoveIterator::TT_MOVE;
		int extension=0;
		if (isKingAttacked) {
			extension++;
		} else if (isHashMove && si.depth > sePVDepth && hashOk && !hashMove.none()
				&& !si.partialSearch && hashData.depth() >= si.depth-3 &&
				(hashData.flag() & TranspositionTable::LOWER)) {
			if (abs(hashData.value()) < winningScore) {
				const int seValue = hashData.value() - seMargin;
				SearchInfo seSi(false, hashMove, true, seValue-1, seValue, si.depth/2,si.ply,
						si.nodeType, si.splitPoint);
				const int partialScore = zwSearch(board,seSi);
				if (partialScore < seValue) {
					extension++;
				}
			}
		}
		MoveBackup backup;
		board.doMove(move,backup);
		moveCounter++;
		const bool givingCheck = board.setInCheck(board.getSideToMove());
		const bool passedPawnPush = isPawnPush(board,move.to);
		const bool pawnOn7thRank = move.promotionPiece!=EMPTY;
		int newDepth=si.depth-1+extension;
		SearchInfo newSi(true,move,-si.beta,-si.alpha,newDepth,si.ply+1,PV_NODE,si.splitPoint);
		if (moveCounter==1 || isHashMove) {
			newSi.update(newDepth,PV_NODE,-si.beta,-si.alpha,move);
			score = -pvSearch(board, newSi);
		} else {
			int reduction=0;
			if (extension==0 && !isKingAttacked && !givingCheck && !passedPawnPush && !pawnOn7thRank &&
					si.depth>lmrDepthThreshold && move.type == MoveIterator::NON_CAPTURE &&
					killer[si.ply][0] != move && killer[si.ply][1] != move) {
				reduction=getReduction(true, si.depth, moveCounter);
				if (agent->getHistory(board.getPiece(move.from), move.to) <= 0) {
					reduction++;
				}
			}
			newSi.update(newDepth-reduction,CUT_NODE,-si.beta,-si.alpha,move);
			score = -zwSearch(board, newSi);
			if (score > si.alpha && score < si.beta) {
				if (reduction>0) {
					bool research=true;
					if (reduction>2) {
						newSi.update(newDepth-1,CUT_NODE,-si.beta,-si.alpha,move);
						score = -zwSearch(board, newSi);
						research=(score >= si.beta);
					}
					if (research) {
						newSi.update(newDepth,CUT_NODE,-si.beta,-si.alpha,move);
						score = -zwSearch(board, newSi);
					}
				}
				if (score > si.alpha && score < si.beta) {
					newSi.update(newDepth,PV_NODE,-si.beta,-si.alpha,move);
					score = -pvSearch(board, newSi);
				}
			}
		}
		board.undoMove(backup);
		if (stop(si)) {
			return 0;
		}
		nodes++;
		if (score>=si.beta) {
			bestScore=score;
			bestMove=move;
			break;
		}
		if (score>bestScore) {
			bestScore=score;
			if(score>si.alpha ) {
				si.alpha = score;
				bestMove=move;
			}
		}
		if (!stop(si) && agent->getThreadNumber()>1 &&
				agent->getFreeThreads()>0 && si.depth>minSplitDepth) {
			if (agent->spawnThreads(board, &si, getThreadId(), &moves, &move, &hashMove,
					&bestScore, &si.alpha, &currentScore, &moveCounter, &nmMateScore)) {
				if (bestScore>=si.beta) {
					break;
				}
			}
		}
	}
	if (!moveCounter) {
		return si.partialSearch?oldAlpha:isKingAttacked?-maxScore+si.ply:drawScore;
	}
	TranspositionTable::NodeFlag flag;
	if (bestScore>=si.beta) {
		flag = currentScore!=-maxScore && !isLazyEval?
				TranspositionTable::LOWER_EVAL:TranspositionTable::LOWER ;
		agent->updateHistory(board,bestMove,si.depth);
		updateKillers(board,bestMove,si.ply);
	} else if (bestScore>oldAlpha) {
		flag = currentScore!=-maxScore && !isLazyEval?
				TranspositionTable::EXACT_EVAL:TranspositionTable::EXACT;
	} else {
		flag = currentScore!=-maxScore && !isLazyEval?
				TranspositionTable::UPPER_EVAL:TranspositionTable::UPPER;
		bestMove=emptyMove;
	}
	agent->hashPut(key,bestScore,currentScore,si.depth,si.ply,flag,bestMove);
	return bestScore;
}