//------------------------------------------------------------------------------
int Tree::Parse (const char *TreeDescr)
{
	enum {stGETNAME, stGETINTERNODE, stNEXTMOVE,
		stFINISHCHILDREN, stQUIT, stACCEPTED} state;
	
	stack< NodePtr, vector<NodePtr> > stk;
	NodePtr		q;
	Parser		p ((char *)TreeDescr);
	tokentype	token;
	float 		f;
	
	// Initialise tree variables
	Root 		= NULL;
	Leaves 		= 0;
	Internals 	= 0;
	Error 		= 0;
	
	// Create first node
	CurNode		= NewNode();
	Root		= CurNode;
	
	// Initialise FSA that reads tree
	state = stGETNAME;
	//std::cout<<endl<<"400 Current token is "<<p.GetTokenAsCstr()<<endl; //added by BCO
	token = p.NextToken ();
	while ((state != stQUIT) && (state != stACCEPTED))
	{
		switch (state)
		{
			
			case stGETNAME:
				switch (token)
				{
					case SPACE:
					case TAB:
					case NEWLINE:
						//std::cout<<endl<<"413 Current token is "<<p.GetTokenAsCstr()<<endl; //added by BCO
						token = p.NextToken ();
						break;
					case STRING:
						// to do: handle translation
						Leaves++;
						CurNode->SetLeaf (true);
						CurNode->SetLeafNumber (Leaves);
						CurNode->SetWeight (1);
						//std::cout<<endl<<"425 Current token is "<<p.GetTokenAsCstr()<<endl; //added by BCO
						CurNode->SetLabel (p.GetToken());
						CurNode->SetDegree (0);
						//CurNode->SetModelCategory(vector<double>(1,1.0)); //Added by BCO
						//std::cout<<endl<<"425 Current token is "<<p.GetTokenAsCstr()<<endl; //added by BCO
						token = p.NextToken ();
						state = stGETINTERNODE;
						break;
					case NUMBER:
						// to do: handle translation
						Leaves++;
						CurNode->SetLeaf (true);
						CurNode->SetLeafNumber (Leaves);
						CurNode->SetWeight (1);
						CurNode->SetLabel (p.GetToken());
						CurNode->SetDegree (0);
						//  CurNode->SetModelCategory(vector<double>(1,1.0)); //Added by BCO
						
						//std::cout<<endl<<"439 Current token is "<<p.GetTokenAsCstr()<<endl; //added by BCO
						token = p.NextToken ();
						state = stGETINTERNODE;
						break;
					case LPAR:
						state = stNEXTMOVE;
						break;
					case ENDOFSTRING:
						Error = errENDOFSTRING;
						state = stQUIT;
						break;
					default:
						Error = errSYNTAX;
						std::cerr<<"Had error in Parse() in TreeLib.cpp line 447"; //added by BCO
						state = stQUIT;
						break;
				}
				break;
				
			case stGETINTERNODE:
				switch (token)
				{
					case SPACE:
					case TAB:
					case NEWLINE:
						//std::cout<<endl<<"464 Current token is "<<p.GetTokenAsCstr()<<endl; //added by BCO
						token = p.NextToken ();
						break;
					case COLON:
					case COMMA:
					case RPAR:
						state = stNEXTMOVE;
						break;
					case ENDOFSTRING:
						Error = errENDOFSTRING;
						state = stQUIT;
						break;
					default:
						Error = errSYNTAX;
						std::cerr<<"Had error in Parse() in TreeLib.cpp line 472"; //added by BCO
						state = stQUIT;
						break;
				}
				break;
				
			case stNEXTMOVE:
				switch (token)
				{
					case COLON: //BCO, have it here deal separately with the next token being a number (use default behavior of treating it as a brlen) and having it a left curly bracket, indicating that simmap output is following.
								//std::cout<<endl<<"488 Current token is "<<p.GetTokenAsCstr()<<endl; //added by BCO
						token = p.NextToken ();
						char matchchar;
						matchchar=p.GetTokenAsCstr()[0];
						if (matchchar=='{') { //added by BCO
							
							//  wrote everything in this if statement
							//Note that the simmap parser only deals with "morphological" data -- states should be integers, in other words. //BCO
							//State order goes from rootmost end of the branch to the tipmost end //BCO
							//StateTimes[i] is amount of time in StateOrder[i] //BCO
							vector<double> modelvector(maxModelCategoryStates,0.0); //maxModelCategoryStates is in TreeLib.h
							vector<int> stateordervector; //Added by BCO
							vector<double> statetimesvector; //Added by BCO
							double totaledgelength=0;
							char internalmatchchar;
							internalmatchchar=p.GetTokenAsCstr()[0];
							while (internalmatchchar!='}') {
								//std::cout<<endl<<"502 Current token is "<<p.GetTokenAsCstr()<<endl; //added by BCO
								token=p.NextToken();
								char colonmatchchar;
								colonmatchchar=p.GetTokenAsCstr()[0];
								if (colonmatchchar==':') {
									//std::cout<<endl<<"506 Current token is "<<p.GetTokenAsCstr()<<endl; //added by BCO
									token=p.NextToken(); //Get rid of colon
									
								}
								int state=atoi(p.GetTokenAsCstr());
								if (state>=maxModelCategoryStates) {
									Error=errTOOMANYMODELCATS;
									break;
								}
								//std::cout<<endl<<"515 Current token is "<<p.GetTokenAsCstr()<<endl; //added by BCO
								token=p.NextToken(); //get rid of comma
													 //std::cout<<endl<<"517 Current token is "<<p.GetTokenAsCstr()<<endl; //added by BCO
								token=p.NextToken(); //This should have the branch length spent in the above state
								double brleninstate = atof (p.GetTokenAsCstr());
								modelvector[state]+=brleninstate;
								stateordervector.push_back(state);
								statetimesvector.push_back(brleninstate);
								totaledgelength+=brleninstate;
								//std::cout<<endl<<"523 Current token is "<<p.GetTokenAsCstr()<<endl; //added by BCO								
								token=p.NextToken();  //take in next token
								internalmatchchar=p.GetTokenAsCstr()[0];
							}
							CurNode->SetEdgeLength (totaledgelength);
							CurNode->SetModelCategory(modelvector); //Added by BCO
							CurNode->SetStateOrder(stateordervector); //Added by BCO
							CurNode->SetStateTimes(statetimesvector); //Added by BCO
							EdgeLengths = true;
							//std::cout<<endl<<"527 Current token is "<<p.GetTokenAsCstr()<<endl; //added by BCO
							token = p.NextToken ();
							break;
						} //BCO
							else { //BCO. Will work when not dealing with a simmap tree.
								f = atof (p.GetTokenAsCstr());
								CurNode->SetEdgeLength (f);
								CurNode->SetModelCategory(vector<double>(1,f)); //Added by BCO
								CurNode->SetStateOrder(vector<int>(1,0)); //Added by BCO
								CurNode->SetStateTimes(vector<double>(1,f)); //Added by BCO
								EdgeLengths = true;
								//std::cout<<endl<<"536 Current token is "<<p.GetTokenAsCstr()<<endl; //added by BCO
								token = p.NextToken ();
							} //BCO
							break;
                    case SPACE:
					case TAB:
					case NEWLINE:
						//std::cout<<endl<<"543 Current token is "<<p.GetTokenAsCstr()<<endl; //added by BCO
						token = p.NextToken ();
						break;
						// The next node encountered will be a sibling
						// of Curnode and a descendant of the node on
						// the top of the node stack.
					case COMMA:
						q = NewNode();
						CurNode->SetSibling (q);
						if (stk.empty())
						{
							Error = errMISSINGLPAR;
							state = stQUIT;
						}
							else
							{
								q->SetAnc (stk.top());
								stk.top()->AddWeight (CurNode->GetWeight());
								stk.top()->IncrementDegree ();
								CurNode = q;
								state = stGETNAME;
								//std::cout<<endl<<"564 Current token is "<<p.GetTokenAsCstr()<<endl; //added by BCO
								token = p.NextToken ();
							}
							break;
						// The next node will be a child of CurNode, hence
						// we create the node and push CurNode onto the
						// node stack.
					case LPAR:
						Internals++;
						stk.push (CurNode);
						q = NewNode();
						CurNode->SetChild (q);
						q->SetAnc (CurNode);
						CurNode->IncrementDegree ();
						CurNode = q;
						//std::cout<<endl<<"579 Current token is "<<p.GetTokenAsCstr()<<endl; //added by BCO
						token = p.NextToken ();
						state = stGETNAME;
						break;
						// We've finished ready the descendants of the node
						// at the top of the node stack so pop it off.
					case RPAR:
						if (stk.empty ())
						{
							Error = errUNBALANCED;
							state = stQUIT;
						}
						else
						{
							q = stk.top();
							q->AddWeight (CurNode->GetWeight());
							CurNode = q;
							stk.pop();
							state = stFINISHCHILDREN;
							//std::cout<<endl<<"598 Current token is "<<p.GetTokenAsCstr()<<endl; //added by BCO
							token = p.NextToken ();
						}
						break;
						// We should have finished the tree
					case SEMICOLON:
						if (stk.empty())
						{
							state = stACCEPTED;
						}
						else
						{
							Error = errSTACKNOTEMPTY;
							state = stQUIT;
						}
						break;
					case ENDOFSTRING:
						Error = errENDOFSTRING;
						state = stQUIT;
						break;
					default:
						Error = errSYNTAX;
						std::cerr<<"Had error in Parse() in TreeLib.cpp line 597"; //added by BCO
						state = stQUIT;
						break;
				}
				break;
				
			case stFINISHCHILDREN:
				switch (token)
				{
					case STRING:
					case NUMBER:
						// internal label
						InternalLabels = true;
						CurNode->SetLabel (p.GetToken());
						//std::cout<<endl<<"634 Current token is "<<p.GetTokenAsCstr()<<endl; //added by BCO
						token = p.NextToken ();
						break;
					case COLON: //BCO, have it here deal separately with the next token being a number (use default behavior of treating it as a brlen) and having it a left curly bracket, indicating that simmap output is following.
								//std::cout<<endl<<"640 Current token is "<<p.GetTokenAsCstr()<<endl; //added by BCO
						token = p.NextToken ();
						char matchchar;
						matchchar=p.GetTokenAsCstr()[0];
						if (matchchar=='{') { //added by BCO
							
							//BCO wrote everything in this if statement
							//Note that the simmap parser only deals with discrete data -- states should be integers, in other words. //BCO
							
							vector<double> modelvector(maxModelCategoryStates,0.0); //maxModelCategoryStates is in TreeLib.h
							vector<int> stateordervector; //added by BCO
							vector<double> statetimesvector; //added by BCO
							double totaledgelength=0;
							char internalmatchchar;
							internalmatchchar=p.GetTokenAsCstr()[0];
							while (internalmatchchar!='}') {
								//std::cout<<endl<<"654 Current token is "<<p.GetTokenAsCstr()<<endl; //added by BCO
								token=p.NextToken();
								char colonmatchchar;
								colonmatchchar=p.GetTokenAsCstr()[0];
								if (colonmatchchar==':') {
									//std::cout<<endl<<"659 Current token is "<<p.GetTokenAsCstr()<<endl; //added by BCO
									token=p.NextToken(); //Get rid of colon
									
								}
								int state=atoi(p.GetTokenAsCstr());
								if (state>=maxModelCategoryStates) {
									Error=errTOOMANYMODELCATS;
									break;
								}
								//std::cout<<endl<<"668 Current token is "<<p.GetTokenAsCstr()<<endl; //added by BCO
								token=p.NextToken(); //get rid of comma
													 //std::cout<<endl<<"670 Current token is "<<p.GetTokenAsCstr()<<endl; //added by BCO
								token=p.NextToken(); //This should have the branch length spent in the above state
								double brleninstate = atof (p.GetTokenAsCstr());
								modelvector[state]+=brleninstate;
								stateordervector.push_back(state);
								statetimesvector.push_back(brleninstate);
								totaledgelength+=brleninstate;
								//std::cout<<endl<<"675 Current token is "<<p.GetTokenAsCstr()<<endl; //added by BCO								
								token=p.NextToken();  //take in next token
								internalmatchchar=p.GetTokenAsCstr()[0];
							}
							CurNode->SetEdgeLength (totaledgelength);
							CurNode->SetModelCategory(modelvector); //Added by BCO
							CurNode->SetStateOrder(stateordervector); //Added by BCO
								CurNode->SetStateTimes(statetimesvector); //Added by BCO
							EdgeLengths = true;
							//std::cout<<endl<<"682 Current token is "<<p.GetTokenAsCstr()<<endl; //added by BCO
							token = p.NextToken ();
							break;
						} //BCO
							else { //BCO. Will work when not dealing with a simmap tree.
								f = atof (p.GetTokenAsCstr());
								CurNode->SetEdgeLength (f);
								CurNode->SetModelCategory(vector<double>(1,f)); //Added by BCO
								CurNode->SetStateOrder(vector<int>(1,0)); //Added by BCO
								CurNode->SetStateTimes(vector<double>(1,f)); //Added by BCO
								EdgeLengths = true;
								//std::cout<<endl<<"691 Current token is "<<p.GetTokenAsCstr()<<endl; //added by BCO
								token = p.NextToken ();
							} //BCO
							break;
					case SPACE:
					case TAB:
					case NEWLINE:
						//std::cout<<endl<<"653 Current token is "<<p.GetTokenAsCstr()<<endl; //added by BCO
						token = p.NextToken ();
						break;
						
						// We've completed traversing the descendants of the
						// node at the top of the stack, so pop it off.
					case RPAR:
						if (stk.empty())
						{
							Error = errUNBALANCED;
							state = stQUIT;
						}
						else
						{
							q = stk.top();
							q->AddWeight (CurNode->GetWeight());
							CurNode = q;
							stk.pop();
							//std::cout<<endl<<"671 Current token is "<<p.GetTokenAsCstr()<<endl; //added by BCO
							token = p.NextToken ();
						}
						break;
						
						// The node at the top of the stack still has some
						// descendants.
					case COMMA:
						q = NewNode();
						CurNode->SetSibling (q);
						if (stk.empty())
						{
							Error = errMISSINGLPAR;
							state = stQUIT;
						}
							else
							{
								q->SetAnc (stk.top());
								stk.top()->AddWeight (CurNode->GetWeight());
								stk.top()->IncrementDegree ();
								CurNode = q;
								state = stGETNAME;
								//std::cout<<endl<<"693 Current token is "<<p.GetTokenAsCstr()<<endl; //added by BCO
								token = p.NextToken ();
							}
							break;
					case SEMICOLON:
						state = stNEXTMOVE;
						break;
					default:
						if (stk.empty())
						{
							Error = errSEMICOLON;
						}
						else
						{
							Error = errSYNTAX;
							std::cerr<<"Had error in Parse() in TreeLib.cpp line 679"; //added by BCO
						}
						state = stQUIT;
						break;
				}
				break;
		}
	}
	// Handle errors
	if (state == stQUIT)
	{
		// Clean up to go here
		return (p.GetPos());
	}
	else
	{
		Root->SetWeight(Leaves);
		getPathLengths(Root); //added by BCO
		return (0);
	}
}