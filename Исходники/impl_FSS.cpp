void _FSSEnvironment::runStage(const Operation& subject, 
		DynamicArray<StyleTreeNode*>& styleTreePositions,
		HashMap<StyleTreeNode*, bool, HashCollection::pointerHash<StyleTreeNode>,
			HashCollection::pointerMatch<StyleTreeNode>>& styleTreePositionSet,
		Allocator& stackAllocator, FDUint depth) {

#ifdef FD_FSS_DIAGNOSTIC_PRINT
	const char* depthString = "                                         ";
	FDUint depthStringLen = strlen(depthString);
	printf("%s%c/%s\n", depthString + depthStringLen - depth, 
			subject.getName().ownerType, subject.getName().name);
#endif

	int positionsListingStart = styleTreePositions.getSize();
	StyleTree& tree = styleSheet.getTree();
	DynamicArray<StyleTreeNode*> styleTreePositionsToAdd(stackAllocator);
	HashMap<PropertyDef*, void*, HashCollection::pointerHash<PropertyDef>,
			HashCollection::pointerMatch<PropertyDef>> defToProperty(
			stackAllocator);

	// Check the style sheet tree for the properties of the subject.
	{
		Profiler p("FSS check for properties", true);

		Profiler pApplicable("Def Applicable Rules", true);
		DynamicArray<StyleRule*> applicableRules(stackAllocator);
		pApplicable.close();

		// Follow up on rules suggested by the subject.
		// Note that we do not keep such rules in the listing of styleTreePositions
		// - instead we only store multi-atom rules that have a first-atom match.
		{
			Profiler p("FSS check rules", true);

			Array<StyleRule* const> relatedRules = subject.getRelatedRules();
			for (int i = 0; i < relatedRules.length; i++) {
				applicableRules.append(relatedRules[i]);
				Selector& selector = relatedRules[i]->getSelector();
				tree.advanceTopRule(*relatedRules[i], subject, 
						styleTreePositionsToAdd, styleTreePositionSet);
			}
		}

		// Extract properties from the list of rules.
		{
			Profiler p("FSS extract properties", true);

			FDUint ruleCount = applicableRules.getSize();
			for (FDUint i = 0; i < ruleCount; i++) {
				Array<Style> styles = applicableRules[i]->getStyles();

				for (int j = 0; j < styles.length; j++) {
					Style& style = styles[j];
					StyleDef& styleDef = style.getDef();
					PropertyDef& propertyDef = styleDef.getPropertyDef();

					// Create the property if it doesn't already exist.
					void* prop;
					if (!defToProperty.get(&propertyDef, prop)) {
						prop = propertyDef.createProperty(stackAllocator);
						defToProperty[&propertyDef] = prop;
					}

					style.invoke(prop);
				}
			}
		}

		{
			Profiler p("FSS do inline styles.", true);

			Array<const Style> inlineStyles = subject.getInlineStyles();
			FDUint inlineStyleCount = inlineStyles.length;

			for (FDUint i = 0; i < inlineStyleCount; i++) {
				const Style& style = inlineStyles[i];

				StyleDef& styleDef = style.getDef();
				PropertyDef& propertyDef = styleDef.getPropertyDef();

				// Create the property if it doesn't already exist.
				void* prop;
				if (!defToProperty.get(&propertyDef, prop)) {
					Profiler pNF("Not found shit", true);
					prop = propertyDef.createProperty(stackAllocator);
					defToProperty[&propertyDef] = prop;
				}

				Profiler p("Invoke Style", true);
				style.invoke(prop);
			}
		}

		Profiler pC("FSS prop check cleanup.", true);
	}

	
	void* hideVS;
	FDbool hasHideProp = defToProperty.get(environment.hidePDef, hideVS);
	if (!hasHideProp || 
			!((SinglePropertyDef<FDbool>::ValueSpecificity*)hideVS)->value) {

		DoOperation doOp(subject, defToProperty);

		user->onDoOperation(doOp);

		// Recurse on children.
		void* childrenVoid;
		bool hasChildren = defToProperty.get(
				styleSheet.getDefaultDefs().childrenDef, childrenVoid);
		if (hasChildren) {
			Profiler p("FSS Children operations", true);

			DefaultDefCollection::OpSet* children = 
					(DefaultDefCollection::OpSet*)childrenVoid;

			FDUint count = children->getSize();
			OpConstraint* ops = FD_NEW_ARRAY(OpConstraint, count, *allocator, 
					allocator);

			DefaultDefCollection::OpSetIterator childrenIterator(*children);
			Operation* key;
			bool value;
			FDUint i = 0;
			while (childrenIterator.getNext(key, value)) {
				ops[i++].op = key;
			}

			// Set up constraints here
			void* orderVoid;
			bool hasConstraints = defToProperty.get(
					styleSheet.getDefaultDefs().orderDef, orderVoid);
			if (hasConstraints) {
				DefaultDefCollection::ConstraintSet* constraints =
						(DefaultDefCollection::ConstraintSet*)orderVoid;

				// Iterate through constraints.
				DefaultDefCollection::ConstraintSetIterator 
						constraintIterator(*constraints);
				Pair<Selector, Selector>* key;
				bool value;
				while (constraintIterator.getNext(key, value)) {

					// TODO: Make this better. I know this can be better,
					// this is a w f u l.

					// We first obtain a list of the things that are supposed to
					// happen before.
					OpConstraint* priors[100];
					FDUint priorCount = 0;
					for (i = 0; i < count; i++) {
						if (key->first.isAtomMatch(*ops[i].op)) {
							priors[priorCount++] = &ops[i];
						}
					}

					// We then match that list to the things that are supposed to
					// happen after.
					for (i = 0; i < count; i++) {
						if (!key->second.isAtomMatch(*ops[i].op)) {
							continue;
						}

						for (FDUint j = 0; j < priorCount; j++) {

							// We check that i isn't already dependent on j.
							if (ops[i].constraints.contains(priors[j])) {
								continue;
							}

							ops[i].constraints.append(priors[j]);
						}
					}

				}
			}

			p.close();

			// Go through the children, respecting the constraints.
			FDUint renderCount = 0;
			for (i = 0; i < count; i++) {

				FDUint current = i;
				if (!ops[i].alreadyRendered) {
					constraintRecurse(ops[i], styleTreePositions, 
							styleTreePositionSet, stackAllocator, depth);
				}
			}

			FD_FREE(ops, *allocator);
		}

		Profiler p("FSS Undo", true);

		user->onUndoOperation(doOp);
	}

	// Clean up positions listing
	int positionsToAddCount = styleTreePositionsToAdd.getSize();
	for (int i = 0; i < positionsToAddCount; i++) {
		styleTreePositionSet.remove(styleTreePositionsToAdd[i]);
	}

	// Clean up defToProperty listing
	{
		HashMap<PropertyDef*, void*, HashCollection::pointerHash<PropertyDef>,
				HashCollection::pointerMatch<PropertyDef>>::Iterator 
				propertyIterator(defToProperty);
		PropertyDef* key;
		void* value;
		while (propertyIterator.getNext(key, value)) {
			key->deleteProperty(value, stackAllocator);
		}
	}
}