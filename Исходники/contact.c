void load_contacts_with_hashtable(FILE *fsource, struct Region *aRegion, struct Hashtable *table, int mode, time_t *startAt, time_t *endAt)
{
	char buf[128], *vName1, *vName2, *tm1,*tm2, *strp, key[128];
	struct Contact *newContact;
	struct Item *aPairItem, *anEgoItem, *aLinkmanItem;
	struct Pair *aPair = NULL;
	struct Ego *anEgo = NULL;
	struct Linkman *aLinkman = NULL;

	time_t sAt, eAt;
	time_t tableStartAt, tableEndAt;
	struct Point aPoint;
	int xNumber, yNumber;
	int needed;
	int first;

	if(table == NULL)
		return;
	first = 1;
	while(fgets(buf, 128, fsource)) {

		vName1 = strtok(buf, ",");
		vName2 = strtok(NULL, ",");
		tm1 = strtok(NULL, ",");
		tm2 = strtok(NULL, ",");
		strp = strtok(NULL, ",");
		aPoint.x = atof(strp);
		strp = strtok(NULL, ",");
		aPoint.y = atof(strp);
		strp = strtok(NULL, ",");
		xNumber = atoi(strp);
		strp = strtok(NULL, ",");
		yNumber = atoi(strp);
		sAt = strtot(tm1);
		eAt = strtot(tm2);

		if(aRegion == NULL && *startAt == 0 && *endAt == 0) {
			needed = 1;
		} else if (aRegion == NULL && *startAt == 0 && *endAt) {
			if (eAt <= *endAt) needed = 1; else needed = 0;
		} else if (aRegion == NULL && *startAt && *endAt == 0) {
			if (sAt >= *startAt) needed = 1; else needed = 0;
		} else if (aRegion == NULL && *startAt && *endAt) {
			if (eAt <= *endAt && sAt >= *startAt) needed = 1; else needed = 0;
		} else if (aRegion && *startAt == 0 && *endAt == 0) {
			if (is_point_in_polygon(&aPoint, aRegion->chosen_polygon))
				needed = 1; else needed = 0;
		} else if (aRegion && *startAt == 0 && *endAt) {
			if (eAt <= *endAt && is_point_in_polygon(&aPoint, aRegion->chosen_polygon))
				needed = 1; else needed = 0;
		} else if (aRegion && *startAt && *endAt == 0) {
			if (is_point_in_polygon(&aPoint, aRegion->chosen_polygon) && sAt >= *startAt)
				needed = 1; else needed = 0;
		} else if (aRegion && *startAt && *endAt) {
			if (is_point_in_polygon(&aPoint, aRegion->chosen_polygon) && sAt >= *startAt && eAt <= *endAt)
				needed = 1; else needed = 0;
		} 
		if( needed ) {	
			newContact = (struct Contact*)malloc(sizeof(struct Contact));
			newContact->gPoint.x = aPoint.x;
			newContact->gPoint.y = aPoint.y;
			newContact->xNumber = xNumber;
			newContact->yNumber = yNumber;
			newContact->startAt = sAt;
			newContact->endAt = eAt;

			if(mode == PAIRWISE_TABLE) {
				sprintf(key, "%s,%s", vName1, vName2);
				aPairItem = hashtable_find(table, key);
				if(aPairItem == NULL) {
					aPair = (struct Pair*)malloc(sizeof(struct Pair));
					pair_init_func(aPair);
					strncpy(aPair->vName1, vName1, strlen(vName1)+1);
					strncpy(aPair->vName2, vName2, strlen(vName2)+1);
					hashtable_add(table, key, aPair);
					aPair->color.integer = rand();
					aPair->startAt = sAt;
					aPair->endAt = eAt;
					if(first) {
						tableStartAt = aPair->startAt;
						tableEndAt = aPair->endAt;
						first = 0;
					}	
				} else {
					aPair = (struct Pair*)aPairItem->datap;
					if(sAt < aPair->startAt) {
						aPair->startAt = sAt;
						if(aPair->startAt < tableStartAt)
							tableStartAt = aPair->startAt;
					}
					if(eAt > aPair->endAt) {
						aPair->endAt = eAt;
						if(aPair->endAt > tableEndAt)
							tableEndAt = aPair->endAt;
					}
				}

				newContact->fromPair = aPair;
				duallist_add_to_tail(&aPair->contents, newContact);
			} else {
				/* Ego vName1 */
				anEgoItem = hashtable_find(table, vName1);
				if(anEgoItem == NULL) {
					anEgo = (struct Ego*)malloc(sizeof(struct Ego));
					ego_init_func(anEgo);
					strncpy(anEgo->vName, vName1, strlen(vName1)+1);
					hashtable_add(table, vName1, anEgo);
					anEgo->startAt = sAt;
					anEgo->endAt = eAt;
					if(first) {
						tableStartAt = anEgo->startAt;
						tableEndAt = anEgo->endAt;
						first = 0;
					}	
				} else {
					anEgo = (struct Ego*)anEgoItem->datap;
					if(sAt < anEgo->startAt) {
						anEgo->startAt = sAt;
						if(anEgo->startAt < tableStartAt)
							tableStartAt = anEgo->startAt;
					}
					if(eAt > anEgo->endAt) {
						anEgo->endAt = eAt;
						if(anEgo->endAt > tableEndAt)
							tableEndAt = anEgo->endAt;
					}
				}

				aLinkmanItem = duallist_find(&anEgo->linkmen, vName2, (int(*)(void*,void*))linkman_has_name);
				if(aLinkmanItem == NULL) {
					aLinkman = (struct Linkman*)malloc(sizeof(struct Linkman));
					linkman_init_func(aLinkman);
					aLinkman->color.integer=rand();
					strncpy(aLinkman->vName, vName2, strlen(vName2)+1);
					duallist_add_to_tail(&anEgo->linkmen, aLinkman);
				} else 
					aLinkman = (struct Linkman*)aLinkmanItem->datap;
				newContact->fromPair = NULL;
				duallist_add_to_tail(&aLinkman->contacts, newContact);

				/* Ego vName2 */
				anEgoItem = hashtable_find(table, vName2);
				if(anEgoItem == NULL) {
					anEgo = (struct Ego*)malloc(sizeof(struct Ego));
					ego_init_func(anEgo);
					strncpy(anEgo->vName, vName2, strlen(vName2)+1);
					hashtable_add(table, vName2, anEgo);
					anEgo->startAt = sAt;
					anEgo->endAt = eAt;
				} else {
					anEgo = (struct Ego*)anEgoItem->datap;
					if(sAt < anEgo->startAt) {
						anEgo->startAt = sAt;
					}
					if(eAt > anEgo->endAt) {
						anEgo->endAt = eAt;
					}
				}

				aLinkmanItem = duallist_find(&anEgo->linkmen, vName1, (int(*)(void*,void*))linkman_has_name);
				if(aLinkmanItem == NULL) {
					aLinkman = (struct Linkman*)malloc(sizeof(struct Linkman));
					linkman_init_func(aLinkman);
					aLinkman->color.integer=rand();
					strncpy(aLinkman->vName, vName1, strlen(vName1)+1);
					duallist_add_to_tail(&anEgo->linkmen, aLinkman);
				} else 
					aLinkman = (struct Linkman*)aLinkmanItem->datap;
				duallist_add_to_tail(&aLinkman->contacts, contact_copy_func(newContact));
			}
		}

	}
	if(table->count) {
		*startAt = tableStartAt;
		*endAt = tableEndAt;
	}
}