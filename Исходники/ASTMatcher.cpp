		/*
		   this helper function is called when the traversal reaches a node of type Decl
		 */
		bool DeclHelper(Decl *D){

			const Stmt* parent = getStmtParent(D, Context);
			//const Stmt* parentsParent = getStmtParent(parent, Context);

			//if it is part of the (init; condition; increment) of a for loop, we don't care about it
			if(isFlowControl(D, Context)){
				return false;
			}


			//supresses the catch stmt's arguments
			if(parent != NULL && strcmp(parent->getStmtClassName(), "CXXCatchStmt") == 0){
				return true;
			}


			string filename;
			if(!isInCurFile(Context, D, filename) && filename.size() != 0){
				return false;
			}else if(filename.size() == 0){
				return true;
			}



			string output = "";
			//get the name of the node type
			string node = D->getDeclKindName();
			//calculate the current level, nextLevel, and previousLevel
			int intLevel = getLevelDecl(D);int intNextLevel = intLevel+1;
			int intNextNextLevel = intLevel+2; int intPrevLevel = intLevel-1;
			//create string values for the levels to use as output
			string level; string nextLevel;
			string nextNextLevel; string prevLevel;
			stringstream ss; stringstream ss2; stringstream ss3; stringstream ss4;
			ss << intLevel;
			level = ss.str();
			ss2 << intNextLevel;
			nextLevel = ss2.str();
			ss3 << intPrevLevel;
			prevLevel = ss3.str();
			ss4 << intNextNextLevel;
			nextNextLevel = ss4.str();



			if(callStackDebug && !callStack.empty()){
				cerr << "decl: call stack top: " << callStack.top()->getStmtClassName() << endl;
			}

			//if top of stack is no longer a parent
			while(!callStack.empty() && numClosingArgsNeeded > 0
					&& !isParentDecl(D, callStack.top()->getStmtClassName())){

				if(debugPrint){
					cerr << "adding args" << endl;
				}
				numClosingArgsNeeded--;
				output += "</args,1>\n";

				callStack.pop();
				if(callStackDebug){
					cerr << "poping" << endl;
					printCallStack();
				}
			}


			//add new calls to stack
			if(isParentDeclInCurFile(D,"CXXConstructExpr") && isParentDecl(D, "CXXConstructExpr")){

				if(debugPrint){
					cerr << "setting previousConstructorCall to true" << endl;
				}


			}else if(isParentDeclInCurFile(D,"CXXTemporaryObjectExpr") && isParentDecl(D, "CXXTemporaryObjectExpr")){

				if(debugPrint){
					cerr << "setting previousTempConstructorCallArg" << endl;
				}


			}else if(isParentDecl(D, "CallExpr")){

				if(debugPrint){
					cerr << "setting previousCallArgs to true" << endl;
				}


			}else if(isParentDecl(D, "CXXMemberCallExpr")){

				if(debugPrint){
					cerr << "setting previousMemberCallArg to true" << endl;
				}

			}


			if(isParentDecl(getDeclParent(D, Context), "Var")){
				previousRhsDecl = true;
				if(debugPrint){
					cout << "setting prev var to true" << endl;
				}
			}else if(previousRhsDecl && numClosingVarsNeeded > 0){
				//if the current node is not a child of a variable declaration 
				//but the previous node was a child of a variable declation 
				//then we know to print a </decl>
				output +="</variableDecl,1>\n";
				numClosingVarsNeeded--;
				previousRhsDecl = false;
			}


			if(node == "Var"){
				output += "<variableDecl, " + prevLevel +  ">";
				numClosingVarsNeeded++;
				VarDecl* VD = (VarDecl*) D;
				if(!VD->hasInit()){
					output +="\n</variableDecl,1>\n";
					numClosingVarsNeeded--;
				}
			}else if(node == "Function"){
				FunctionDecl* FD = (FunctionDecl*) D; 
				output += "<functionDef," + level +">";
				//add function name to the output
				output += "\n<name: " + FD->getNameInfo().getAsString()
					+ "," + nextLevel + ">";

			}else if(node == "CXXRecord"){
				const Decl* parent = getDeclParent(D, Context);
				if(parent && strcmp(parent->getDeclKindName(), "CXXRecord") != 0){
					CXXRecordDecl* CD = (CXXRecordDecl*) D;
					output += "<classDef," + level + ">";
					output += "\n<name: " + CD->getNameAsString() + "," + nextLevel + ">";
					output += "\n<bases," + nextLevel + ">";

					//iterate over all bases and add them to the output
					CXXRecordDecl::base_class_iterator basesItr =  CD->bases_begin();
					while(basesItr != CD->bases_end()){
						QualType qt = basesItr->getType();
						output +=  "\n<base: " +  qt.getBaseTypeIdentifier()->getName().str();
						output +=  "," + nextNextLevel + ">";
						basesItr++;
					}

					//iterate over all of the virtual bases and add them to the output
					auto vBasesItr = CD->vbases_begin();
					while(vBasesItr != CD->vbases_end()){
						QualType qt = vBasesItr->getType();
						output +=  "\n<base: " +  qt.getBaseTypeIdentifier()->getName().str();
						output +=  "," + nextNextLevel + ">";
						vBasesItr++;
					}

				}
			}else if(node == "CXXDestructor"){
				CXXDestructorDecl* CD = (CXXDestructorDecl*) D;
				if(!CD->isImplicit()){
					output += "<functionDef," + level +">";
					//add function name to the output
					output += "\n<name: ~" + CD->getNameInfo().getAsString()
						+ "," + nextLevel + ">";
				}


			}else if(node == "CXXConstructor"){
				CXXConstructorDecl* CD = (CXXConstructorDecl*) D;
				if(!CD->isImplicit()){
					output += "<functionDef," + level +">";
					//add function name to the output
					output += "\n<name: " + CD->getNameInfo().getAsString()
						+ "," + nextLevel + ">";
				}
			}else if(node == "CXXMethod"){
				CXXMethodDecl* CM = (CXXMethodDecl*) D;
				if(!CM->isImplicit()){
					output += "<functionDef," + level +">";
					//add function name to the output
					output += "\n<name: " + CM->getNameInfo().getAsString()
						+ "," + nextLevel + ">";
				}
			}else{

				if(debugPrint){
					output += "<";
					output += node;
					output += ">";
				}
			}

			if(output.size() != 0){
				cout << output << endl;
			}

			return true;
		}