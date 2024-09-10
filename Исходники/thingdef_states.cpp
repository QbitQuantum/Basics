//==========================================================================
//
// ParseStates
// parses a state block
//
//==========================================================================
int ParseStates(FActorInfo * actor, AActor * defaults, Baggage &bag)
{
	FString statestring;
	intptr_t count = 0;
	FState state;
	FState * laststate = NULL;
	intptr_t lastlabel = -1;
	int minrequiredstate = -1;

	SC_MustGetStringName ("{");
	SC_SetEscape(false);	// disable escape sequences in the state parser
	while (!SC_CheckString ("}") && !sc_End)
	{
		memset(&state,0,sizeof(state));
		statestring = ParseStateString();
		if (!statestring.CompareNoCase("GOTO"))
		{
do_goto:	
			statestring = ParseStateString();
			if (SC_CheckString ("+"))
			{
				SC_MustGetNumber ();
				statestring += '+';
				statestring += sc_String;
			}
			// copy the text - this must be resolved later!
			if (laststate != NULL)
			{ // Following a state definition: Modify it.
				laststate->NextState = (FState*)copystring(statestring);	
			}
			else if (lastlabel >= 0)
			{ // Following a label: Retarget it.
				RetargetStates (count+1, statestring);
			}
			else
			{
				SC_ScriptError("GOTO before first state");
			}
		}
		else if (!statestring.CompareNoCase("STOP"))
		{
do_stop:
			if (laststate!=NULL)
			{
				laststate->NextState=(FState*)-1;
			}
			else if (lastlabel >=0)
			{
				RetargetStates (count+1, NULL);
			}
			else
			{
				SC_ScriptError("STOP before first state");
				continue;
			}
		}
		else if (!statestring.CompareNoCase("WAIT") || !statestring.CompareNoCase("FAIL"))
		{
			if (!laststate) 
			{
				SC_ScriptError("%s before first state", sc_String);
				continue;
			}
			laststate->NextState=(FState*)-2;
		}
		else if (!statestring.CompareNoCase("LOOP"))
		{
			if (!laststate) 
			{
				SC_ScriptError("LOOP before first state");
				continue;
			}
			laststate->NextState=(FState*)(lastlabel+1);
		}
		else
		{
			const char * statestrp;

			SC_MustGetString();
			if (SC_Compare (":"))
			{
				laststate = NULL;
				do
				{
					lastlabel = count;
					AddState(statestring, (FState *) (count+1));
					statestring = ParseStateString();
					if (!statestring.CompareNoCase("GOTO"))
					{
						goto do_goto;
					}
					else if (!statestring.CompareNoCase("STOP"))
					{
						goto do_stop;
					}
					SC_MustGetString ();
				} while (SC_Compare (":"));
//				continue;
			}

			SC_UnGet ();

			if (statestring.Len() != 4)
			{
				SC_ScriptError ("Sprite names must be exactly 4 characters\n");
			}

			memcpy(state.sprite.name, statestring, 4);
			state.Misc1=state.Misc2=0;
			state.ParameterIndex=0;
			SC_MustGetString();
			statestring = (sc_String+1);
			statestrp = statestring;
			state.Frame=(*sc_String&223)-'A';
			if ((*sc_String&223)<'A' || (*sc_String&223)>']')
			{
				SC_ScriptError ("Frames must be A-Z, [, \\, or ]");
				state.Frame=0;
			}

			SC_MustGetNumber();
			sc_Number++;
			state.Tics=sc_Number&255;
			state.Misc1=(sc_Number>>8)&255;
			if (state.Misc1) state.Frame|=SF_BIGTIC;

			while (SC_GetString() && !sc_Crossed)
			{
				if (SC_Compare("BRIGHT")) 
				{
					state.Frame|=SF_FULLBRIGHT;
					continue;
				}
				if (SC_Compare("OFFSET"))
				{
					if (state.Frame&SF_BIGTIC)
					{
						SC_ScriptError("You cannot use OFFSET with a state duration larger than 254!");
					}
					// specify a weapon offset
					SC_MustGetStringName("(");
					SC_MustGetNumber();
					state.Misc1=sc_Number;
					SC_MustGetStringName (",");
					SC_MustGetNumber();
					state.Misc2=sc_Number;
					SC_MustGetStringName(")");
					continue;
				}

				// Make the action name lowercase to satisfy the gperf hashers
				strlwr (sc_String);

				int minreq=count;
				if (DoActionSpecials(state, !statestring.IsEmpty(), &minreq, bag))
				{
					if (minreq>minrequiredstate) minrequiredstate=minreq;
					goto endofstate;
				}

				PSymbol *sym = bag.Info->Class->Symbols.FindSymbol (FName(sc_String, true), true);
				if (sym != NULL && sym->SymbolType == SYM_ActionFunction)
				{
					PSymbolActionFunction *afd = static_cast<PSymbolActionFunction *>(sym);
					state.Action = afd->Function;
					if (!afd->Arguments.IsEmpty())
					{
						const char *params = afd->Arguments.GetChars();
						int numparams = (int)afd->Arguments.Len();
				
						int v;

						if (!islower(*params))
						{
							SC_MustGetStringName("(");
						}
						else
						{
							if (!SC_CheckString("(")) goto endofstate;
						}
						
						int paramindex = PrepareStateParameters(&state, numparams);
						int paramstart = paramindex;
						bool varargs = params[numparams - 1] == '+';

						if (varargs)
						{
							StateParameters[paramindex++] = 0;
						}

						while (*params)
						{
							switch(*params)
							{
							case 'I':
							case 'i':		// Integer
								SC_MustGetNumber();
								v=sc_Number;
								break;

							case 'F':
							case 'f':		// Fixed point
								SC_MustGetFloat();
								v=fixed_t(sc_Float*FRACUNIT);
								break;


							case 'S':
							case 's':		// Sound name
								SC_MustGetString();
								v=S_FindSound(sc_String);
								break;

							case 'M':
							case 'm':		// Actor name
							case 'T':
							case 't':		// String
								SC_SetEscape(true);
								SC_MustGetString();
								SC_SetEscape(false);
								v = (int)(sc_String[0] ? FName(sc_String) : NAME_None);
								break;

							case 'L':
							case 'l':		// Jump label

								if (SC_CheckNumber())
								{
									if (strlen(statestring)>0)
									{
										SC_ScriptError("You cannot use A_Jump commands with a jump index on multistate definitions\n");
									}

									v=sc_Number;
									if (v<1)
									{
										SC_ScriptError("Negative jump offsets are not allowed");
									}

									{
										int minreq=count+v;
										if (minreq>minrequiredstate) minrequiredstate=minreq;
									}
								}
								else
								{
									if (JumpParameters.Size()==0) JumpParameters.Push(NAME_None);

									v = -(int)JumpParameters.Size();
									// This forces quotation marks around the state name.
									SC_MustGetToken(TK_StringConst);
									FString statestring = sc_String; // ParseStateString();
									const PClass *stype=NULL;
									int scope = statestring.IndexOf("::");
									if (scope >= 0)
									{
										FName scopename = FName(statestring, scope, false);
										if (scopename == NAME_Super)
										{
											// Super refers to the direct superclass
											scopename = actor->Class->ParentClass->TypeName;
										}
										JumpParameters.Push(scopename);
										statestring = statestring.Right(statestring.Len()-scope-2);

										stype = PClass::FindClass (scopename);
										if (stype == NULL)
										{
											SC_ScriptError ("%s is an unknown class.", scopename.GetChars());
										}
										if (!stype->IsDescendantOf (RUNTIME_CLASS(AActor)))
										{
											SC_ScriptError ("%s is not an actor class, so it has no states.", stype->TypeName.GetChars());
										}
										if (!stype->IsAncestorOf (actor->Class))
										{
											SC_ScriptError ("%s is not derived from %s so cannot access its states.",
												actor->Class->TypeName.GetChars(), stype->TypeName.GetChars());
										}
									}
									else
									{
										// No class name is stored. This allows 'virtual' jumps to
										// labels in subclasses.
										// It also means that the validity of the given state cannot
										// be checked here.
										JumpParameters.Push(NAME_None);
									}
									TArray<FName> names;
									MakeStateNameList(statestring, &names);

									if (stype != NULL)
									{
										if (!stype->ActorInfo->FindState(names.Size(), &names[0]))
										{
											SC_ScriptError("Jump to unknown state '%s' in class '%s'",
												statestring.GetChars(), stype->TypeName.GetChars());
										}
									}
									JumpParameters.Push((ENamedName)names.Size());
									for(unsigned i=0;i<names.Size();i++)
									{
										JumpParameters.Push(names[i]);
									}
									// No offsets here. The point of jumping to labels is to avoid such things!
								}

								break;

							case 'C':
							case 'c':		// Color
								SC_MustGetString ();
								if (SC_Compare("none"))
								{
									v = -1;
								}
								else
								{
									int c = V_GetColor (NULL, sc_String);
									// 0 needs to be the default so we have to mark the color.
									v = MAKEARGB(1, RPART(c), GPART(c), BPART(c));
								}
								break;

							case 'X':
							case 'x':
								v = ParseExpression (false, bag.Info->Class);
								break;

							case 'Y':
							case 'y':
								v = ParseExpression (true, bag.Info->Class);
								break;

							default:
								assert(false);
								v = -1;
								break;
							}
							StateParameters[paramindex++] = v;
							params++;
							if (varargs)
							{
								StateParameters[paramstart]++;
							}
							if (*params)
							{
								if (*params == '+')
								{
									if (SC_CheckString(")"))
									{
										goto endofstate;
									}
									params--;
									v = 0;
									StateParameters.Push(v);
								}
								else if ((islower(*params) || *params=='!') && SC_CheckString(")"))
								{
									goto endofstate;
								}
								SC_MustGetStringName (",");
							}
						}
						SC_MustGetStringName(")");
					}
					else 
					{
						SC_MustGetString();
						if (SC_Compare("("))
						{
							SC_ScriptError("You cannot pass parameters to '%s'\n",sc_String);
						}
						SC_UnGet();
					}
					goto endofstate;
				}
				SC_ScriptError("Invalid state parameter %s\n", sc_String);
			}
			SC_UnGet();
endofstate:
			StateArray.Push(state);
			while (*statestrp)
			{
				int frame=((*statestrp++)&223)-'A';

				if (frame<0 || frame>28)
				{
					SC_ScriptError ("Frames must be A-Z, [, \\, or ]");
					frame=0;
				}

				state.Frame=(state.Frame&(SF_FULLBRIGHT|SF_BIGTIC))|frame;
				StateArray.Push(state);
				count++;
			}
			laststate=&StateArray[count];
			count++;
		}
	}
	if (count<=minrequiredstate)
	{
		SC_ScriptError("A_Jump offset out of range in %s", actor->Class->TypeName.GetChars());
	}
	SC_SetEscape(true);	// re-enable escape sequences
	return count;
}