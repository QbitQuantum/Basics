sar_bool sar_lookPathPos_c(sarNode_p currNode, const char * checkStr, long startPos, long currPos, long len, sar_bool negative) {
	sar_bool matched = SAR_FALSE;

	int callPos = 0;
    while(currNode->callFunc[callPos] != (SV*)NULL) {
    	matched = SAR_TRUE;
    	sar_runCallFunc_c(currNode->callFunc[callPos], startPos, currPos);
        ++callPos;
    }

    if (currPos >= len) {
    	return matched;
    }

    char checkChar = checkStr[currPos];

    sarNode_p plusNode = currNode->plusNode;
    if (plusNode != (sarNode_p)NULL) {
    	if (negative) {
        	int pathCharNum = 0;
        	for (pathCharNum=0; pathCharNum < plusNode->charNumber; ++pathCharNum) {
        		if (checkChar != plusNode->sarPathChars[pathCharNum]) {
    				sarNode_p nextPlusNode = plusNode->sarNodes[pathCharNum];
    				sar_bool plusNodesMatched = sar_matchPlusNode_c(nextPlusNode, checkStr, startPos, currPos, len, SAR_CHAR, negative);
    				matched = matched || plusNodesMatched;
        		}
        	}

	    	if (plusNode->digitNode != (sarNode_p)NULL) {
	    		if (! isDIGIT(checkChar)) {
	        		sarNode_p nextPlusNode = plusNode->digitNode;
	        		sar_bool plusNodesMatched = sar_matchPlusNode_c(nextPlusNode, checkStr, startPos, currPos, len, SAR_DIGIT, negative);
	        		matched = matched || plusNodesMatched;
	    		}
	    	}

    	}
    	else {
    		int existListPlusNodePos = sar_searchChar_c(plusNode->sarPathChars, plusNode->charNumber, checkChar);
			if (existListPlusNodePos >= 0) {
				sarNode_p nextPlusNode = plusNode->sarNodes[existListPlusNodePos];
				sar_bool plusNodesMatched = sar_matchPlusNode_c(nextPlusNode, checkStr, startPos, currPos, len, SAR_CHAR, negative);
				matched = matched || plusNodesMatched;
			}

	    	if (plusNode->dotNode != (sarNode_p)NULL) {
	       		sarNode_p nextPlusNode = plusNode->dotNode;
	       		sar_bool plusNodesMatched = sar_matchPlusNode_c(nextPlusNode, checkStr, startPos, currPos, len, SAR_DOT, negative);
	       		matched = matched || plusNodesMatched;
	    	}
	    	if (plusNode->digitNode != (sarNode_p)NULL) {
	    		if (isDIGIT(checkChar)) {
	        		sarNode_p nextPlusNode = plusNode->digitNode;
	        		sar_bool plusNodesMatched = sar_matchPlusNode_c(nextPlusNode, checkStr, startPos, currPos, len, SAR_DIGIT, negative);
	        		matched = matched || plusNodesMatched;
	    		}
	    	}
	    	if (plusNode->alphaNumNode != (sarNode_p)NULL) {
	    		if (isALNUM(checkChar)) {
	        		sarNode_p nextPlusNode = plusNode->alphaNumNode;
	        		sar_bool plusNodesMatched = sar_matchPlusNode_c(nextPlusNode, checkStr, startPos, currPos, len, SAR_ALPHA_NUM, negative);
	        		matched = matched || plusNodesMatched;
	    		}
	    	}
	    	if (plusNode->alphaNode != (sarNode_p)NULL) {
	    		if (isALPHA(checkChar)) {
	        		sarNode_p nextPlusNode = plusNode->alphaNode;
	        		sar_bool plusNodesMatched = sar_matchPlusNode_c(nextPlusNode, checkStr, startPos, currPos, len, SAR_ALPHA, negative);
	        		matched = matched || plusNodesMatched;
	    		}
	    	}
	    	if (plusNode->spaceNode != (sarNode_p)NULL) {
	    		if (isSPACE(checkChar)) {
	        		sarNode_p nextPlusNode = plusNode->spaceNode;
	        		sar_bool plusNodesMatched = sar_matchPlusNode_c(nextPlusNode, checkStr, startPos, currPos, len, SAR_SPACE, negative);
	        		matched = matched || plusNodesMatched;
	    		}
	    	}

    	}
    }

    if (negative) {
    	int pathCharNum = 0;
    	for (pathCharNum=0; pathCharNum < currNode->charNumber; ++pathCharNum) {
    		if (checkChar != currNode->sarPathChars[pathCharNum]) {
    			sar_bool nodesMatched = sar_lookPathPos_c(currNode->sarNodes[pathCharNum], checkStr, startPos, currPos + 1, len, SAR_FALSE);
    			matched = matched || nodesMatched;
    		}
    	}

		if (currNode->spaceNode != (sarNode_p)NULL) {
			if (! isSPACE(checkChar)) {
				sar_bool nodesMatched = sar_lookPathPos_c(currNode->spaceNode, checkStr, startPos, currPos + 1, len, SAR_FALSE);
				matched = matched || nodesMatched;
			}
		}
		if (currNode->digitNode != (sarNode_p)NULL) {
			if (! isDIGIT(checkChar)) {
				sar_bool nodesMatched = sar_lookPathPos_c(currNode->digitNode, checkStr, startPos, currPos + 1, len, SAR_FALSE);
				matched = matched || nodesMatched;
			}
		}
		if (currNode->alphaNumNode != (sarNode_p)NULL) {
			if (! isALNUM(checkChar)) {
				sar_bool nodesMatched = sar_lookPathPos_c(currNode->alphaNumNode, checkStr, startPos, currPos + 1, len, SAR_FALSE);
				matched = matched || nodesMatched;
			}
		}
		if (currNode->alphaNode != (sarNode_p)NULL) {
			if (! isALPHA(checkChar)) {
				sar_bool nodesMatched = sar_lookPathPos_c(currNode->alphaNode, checkStr, startPos, currPos + 1, len, SAR_FALSE);
				matched = matched || nodesMatched;
			}
		}

    }
    else {
		int existListNodePos = sar_searchChar_c(currNode->sarPathChars, currNode->charNumber, checkChar);
		if (existListNodePos >= 0) {
			sar_bool nodesMatched = sar_lookPathPos_c(currNode->sarNodes[existListNodePos], checkStr, startPos, currPos + 1, len, SAR_FALSE);
			matched = matched || nodesMatched;
		}

		if (currNode->negativeNode != (sarNode_p)NULL) {
			sar_bool nodesMatched = sar_lookPathPos_c(currNode->negativeNode, checkStr, startPos, currPos, len, SAR_TRUE);
			matched = matched || nodesMatched;
		}

		if (currNode->dotNode != (sarNode_p)NULL) {
			sar_bool nodesMatched = sar_lookPathPos_c(currNode->dotNode, checkStr, startPos, currPos + 1, len, SAR_FALSE);
			matched = matched || nodesMatched;
		}
		if (currNode->spaceNode != (sarNode_p)NULL) {
			if (isSPACE(checkChar)) {
				sar_bool nodesMatched = sar_lookPathPos_c(currNode->spaceNode, checkStr, startPos, currPos + 1, len, SAR_FALSE);
				matched = matched || nodesMatched;
			}
		}
		if (currNode->digitNode != (sarNode_p)NULL) {
			if (isDIGIT(checkChar)) {
				sar_bool nodesMatched = sar_lookPathPos_c(currNode->digitNode, checkStr, startPos, currPos + 1, len, SAR_FALSE);
				matched = matched || nodesMatched;
			}
		}
		if (currNode->alphaNumNode != (sarNode_p)NULL) {
			if (isALNUM(checkChar)) {
				sar_bool nodesMatched = sar_lookPathPos_c(currNode->alphaNumNode, checkStr, startPos, currPos + 1, len, SAR_FALSE);
				matched = matched || nodesMatched;
			}
		}
		if (currNode->alphaNode != (sarNode_p)NULL) {
			if (isALPHA(checkChar)) {
				sar_bool nodesMatched = sar_lookPathPos_c(currNode->alphaNode, checkStr, startPos, currPos + 1, len, SAR_FALSE);
				matched = matched || nodesMatched;
			}
		}

    }

    return matched;
}