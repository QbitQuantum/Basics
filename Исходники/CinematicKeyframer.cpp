bool AddKey(C_KEY * key, bool writecolor, bool writecolord, bool writecolorf)
{
	int			num;

	if(!CKTrack || (key->frame < CKTrack->startframe) || (key->frame > CKTrack->endframe))
		return false;

	C_KEY * k = SearchKey(key->frame, &num);
	if(!k) {
		if(!CKTrack->nbkey) {
			CKTrack->key = k = (C_KEY *)malloc(sizeof(C_KEY));
		} else {
			CKTrack->key = (C_KEY *)realloc(CKTrack->key, sizeof(C_KEY) * (CKTrack->nbkey + 1));
			k = SearchAndMoveKey(key->frame);
		}

		CKTrack->nbkey++;

		k->frame = key->frame;
	}

	if(key->numbitmap > -2)
		k->numbitmap = key->numbitmap;

	if(key->fx > -2) {
		if((key->fx > 255) && (k->fx > 0)) {
			k->fx |= key->fx;
		} else {
			if((k->fx >= 255) && (key->fx >= 0)) {
				k->fx |= key->fx;
			} else {
				k->fx = key->fx;
			}
		}
	}

	if(key->speed > -1.f) {
		k->speed = key->speed;
	}

	if(writecolor)
		k->color = key->color;

	if(writecolord)
		k->colord = key->colord;

	if(writecolorf)
		k->colorf = key->colorf;

	if(key->idsound > -2) {
		k->idsound = key->idsound;
	}

	if(key->force > -2)
		k->force = key->force;

	k->frame = key->frame;
	k->pos = key->pos;
	k->angz = key->angz;

	if(key->typeinterp > -2)
		k->typeinterp = key->typeinterp;

	float a = -2.f;

	if(C_NEQUAL_F32(key->light.intensity, a)) {
		k->light = key->light;
	}

	k->posgrille = key->posgrille;
	k->angzgrille = key->angzgrille;
	k->speedtrack = key->speedtrack;

	UpDateAllKeyLight();

	return true;
}