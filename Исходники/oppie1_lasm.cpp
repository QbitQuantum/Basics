//////////
//
// Top level lasm1 assembler
//
//////
	int main(int argc, char* argv[])
	{
		s32					lnI, lnErrors, lnWarnings, lnOrg, numread;
		bool				llMap;
		SEM*				asmFile;
		SBuilder*			map;
		SLine*				line;
		FILE*				lfh;
		SOppie1Instruction*	instr;
		s8					buffer[2048];
		s8					output[2048];


//////////
//
// 		SBsa				bsa;
// 		SOra				ora;
// 		SOrr				orr;
//
// 		memset(&bsa, 0, sizeof(bsa));
// 		memset(&ora, 0, sizeof(ora));
// 		memset(&orr, 0, sizeof(orr));
// 		bsa.ooooo	= 0x1f;
// 		ora.ooo		= 0x7;
// 		orr.oooo	= 0xf;
// 		_asm nop;
//
//////


		//////////
		// Identify ourself
		//////
			printf("LibSF Oppie-1 Assembler v0.02\n");


		//////////
		// Initialize Visual FreePro, Jr. stuff
		///////
			InitializeCriticalSection(&cs_uniqueIdAccess);
			InitializeCriticalSection(&cs_logData);


		//////////
		// lasm1 only takes one parameter, the input filename
		//////
			if (argc < 2 || argc > 3)
			{
				// Display syntax
				printf("Usage:  lasm1 myfile.asm /map\n");

			} else {
				// Allocate our load manager
				asmFile = iSEM_allocate(true);
				if (!asmFile)
				{
					// Internal error
					printf("Internal error allocating load buffer\n");

				} else {
					// Try to physically load it
					if (!iSEM_loadFromDisk(asmFile, argv[1], false, false))
					{
						// Error opening
						printf("Unable to open %s\n", argv[1]);

					} else {
						// Indicate we're in progress
						printf("Assembling %s\n", argv[1]);

						// See if they specified /map
						llMap = (argc == 3 && strlen(argv[2]) == 4 && _memicmp(argv[2], "/map", 4) == 0);

						//////////
						// Parse every line into known components
						//////
							for (line = asmFile->firstLine; line; line = (SLine*)line->ll.next)
								iParseSourceCodeLine(line);


						//////////
						// Compile every line that can be compiled, report any errors
						//////
							for (	line = asmFile->firstLine, lnErrors = 0, lnWarnings = 0;
									line;
									line = (SLine*)line->ll.next	)
							{
								// Compile pass-1
								if (line->compilerInfo->firstComp && line->compilerInfo->firstComp->iCode != _ICODE_COMMENT)
									iCompileSourceCodeLine(asmFile, line, &lnErrors, &lnWarnings, 1);
							}

							// If there were any errors, exit
							if (lnErrors != 0)
								exit_program(-1);


						//////////
						// Assign addresses to everything
						//////
							for (	lnOrg = 0, line = asmFile->firstLine;
									line;
									line = (SLine*)line->ll.next	)
							{
								//////////
								// Based on the type update it
								//////
									instr = (SOppie1Instruction*)line->compilerInfo->extra_info;
									if (instr->isOrg)
									{
										// Update the origin
										lnOrg		= instr->org;

									} else {
										// Store the origin, and increase beyond this instruction's length
										instr->org	= lnOrg;
										lnOrg		+= instr->size;
									}
							}


						//////////
						// Compile every line which has an address that may not have been resolvable before
						//////
							for (	line = asmFile->firstLine, lnErrors = 0, lnWarnings = 0;
									line;
									line = (SLine*)line->ll.next	)
							{
								// Compile pass-2
								iCompileSourceCodeLine(asmFile, line, &lnErrors, &lnWarnings, 2);
							}

							// If there were any errors, exit
							if (lnErrors != 0)
								exit_program(-2);


						//////////
						// When we get here, every line has compiled out.
						// Look for memory locations which will overlay
						//////
							memset(output, 0, sizeof(output));
							memset(buffer, 0, sizeof(buffer));
							for (	line = asmFile->firstLine;
									line;
									line = (SLine*)line->ll.next	)
							{
								//////////
								// Grab the instruction for this line
								//////
									instr = (SOppie1Instruction*)line->compilerInfo->extra_info;
									if (instr->size != 0)
									{
										// There's some content there
										if (instr->isData)
										{
											//////////
											// Store the data
											//////
												for (lnI = 0; lnI < instr->size; lnI++)
												{
													// Increase our test buffer count
													++buffer[instr->org + lnI];
													if (buffer[instr->org + 1] > 1)
													{
														// We've overwritten a prior memory value
														printf("Addresses overlap on line %u\n", line->lineNumber);
														exit_program(-3);
													}

													// Copy the raw data
													output[instr->org + lnI] = instr->data[lnI];
												}

										} else if (instr->isInstruction) {
											//////////
											// Store the instruction
											//////
												if (instr->org + instr->size - 1 >= 2048)
												{
													// It will wrap around the end
													printf("Invalid address for line %u\n", line->lineNumber);
													exit_program(-4);
												}


											//////////
											// Increase for first byte
											//////
												++buffer[instr->org];
												output[instr->org] = instr->ora.i_data1;
												if (buffer[instr->org] > 1)
												{
													// We've overwritten a prior memory value
													printf("Addresses overlap on line %u\n", line->lineNumber);
													exit_program(-5);
												}


											//////////
											// If there's a second byte, do that one as well
											//////
												if (instr->size == 2)
												{
													++buffer[instr->org + 1];
													output[instr->org + 1] = instr->ora.i_data2;
													if (buffer[instr->org + 1] > 1)
													{
														// We've overwritten a prior memory value
														printf("Addresses overlap on line %u\n", line->lineNumber);
														exit_program(-6);
													}
												}
										}
									}
							}


						//////////
						// Create the otuput file
						//////
							memcpy(argv[1] + strlen(argv[1]) - 4, ".img", 4);
							lfh = fopen(argv[1], "wb+");
							if (!lfh)
							{
								// Could not create the output file
								printf("Error creating %s\n", argv[1]);
								exit_program(-7);
							}


						//////////
						// Write the buffer
						//////
							numread = fwrite(output, 1, 2048, lfh);
							fclose(lfh);
							if (numread != 2048)
							{
								printf("Error writing 2048 bytes\n");
								exit_program(-8);

							} else {
								// Success
								printf("Wrote 2048 bytes\n");
							}


						//////////
						// They specified a map file
						//////
							if (llMap)
							{
								//////////
								// Allocate our output buffer
								//////
									iBuilder_createAndInitialize(&map, -1);


								//////////
								// Iterate through each line and convey data, or disassembly for the output
								//////
									for (	line = asmFile->firstLine, lnErrors = 0, lnWarnings = 0;
											line;
											line = (SLine*)line->ll.next	)
									{
										//////////
										// Grab the instruction for this line
										//////
											instr = (SOppie1Instruction*)line->compilerInfo->extra_info;
											if (instr->size != 0)
											{
												//////////
												// Show the address:
												//////
													sprintf(buffer, "%03x: \0", instr->org);
													iBuilder_appendData(map, buffer, -1);


												//////////
												// There's some content there
												//////
													memset(buffer, 0, sizeof(buffer));
													if (instr->isData)
													{
														//////////
														// Show the data
														//////
															for (lnI = 0; lnI < instr->size; lnI++)
																sprintf(buffer + (lnI * 3), "%02x%s", instr->data[lnI], ((lnI + 1 < instr->size) ? ",\0" : " \0"));


													} else if (instr->isInstruction) {
														// Disassemble the instruction
														iiDebo1_decodeAssembly(buffer, instr->org, false, true, (u8*)output);
														memset(buffer + strlen(buffer), 32, 64);
														buffer[45] = '/';
														buffer[46] = '/';
														memcpy(buffer + 48, line->sourceCode->data_s8, line->sourceCode_populatedLength);
														buffer[48 + line->sourceCode_populatedLength] = 0;
													}


												//////////
												// Append the data
												//////
													iBuilder_appendData(map, buffer, strlen(buffer));
													iBuilder_appendCrLf(map);
											}

									}


								//////////
								// Save the map file
								//////
									memcpy(argv[1] + strlen(argv[1]) - 4, ".map", 4);
									iBuilder_asciiWriteOutFile(map, argv[1]);

							}

					}
				}
			}


		//////////
		// Task completed (one way or another :-))
		//////
			exit_program(0);
	}