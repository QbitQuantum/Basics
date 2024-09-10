void MissileType::Load(lua_State *l)
{
	this->NumDirections = 1;
	this->Flip = true;
	// Ensure we don't divide by zero.
	this->SplashFactor = 100;

	// Parse the arguments
	std::string file;
	for (lua_pushnil(l); lua_next(l, 2); lua_pop(l, 1)) {
		const char *value = LuaToString(l, -2);

		if (!strcmp(value, "File")) {
			file = LuaToString(l, -1);
		} else if (!strcmp(value, "Size")) {
			if (!lua_istable(l, -1) || lua_rawlen(l, -1) != 2) {
				LuaError(l, "incorrect argument");
			}
			lua_rawgeti(l, -1, 1);
			this->size.x = LuaToNumber(l, -1);
			lua_pop(l, 1);
			lua_rawgeti(l, -1, 2);
			this->size.y = LuaToNumber(l, -1);
			lua_pop(l, 1);
		} else if (!strcmp(value, "Frames")) {
			this->SpriteFrames = LuaToNumber(l, -1);
		} else if (!strcmp(value, "Flip")) {
			this->Flip = LuaToBoolean(l, -1);
		} else if (!strcmp(value, "NumDirections")) {
			this->NumDirections = LuaToNumber(l, -1);
		} else if (!strcmp(value, "Transparency")) {
			this->Transparency = LuaToNumber(l, -1);
		} else if (!strcmp(value, "FiredSound")) {
			this->FiredSound.Name = LuaToString(l, -1);
		} else if (!strcmp(value, "ImpactSound")) {
			this->ImpactSound.Name = LuaToString(l, -1);
		} else if (!strcmp(value, "ChangeVariable")) {
			const int index = UnitTypeVar.VariableNameLookup[LuaToString(l, -1)];// User variables
			if (index == -1) {
				fprintf(stderr, "Bad variable name '%s'\n", LuaToString(l, -1));
				Exit(1);
				return;
			}
			this->ChangeVariable = index;
		} else if (!strcmp(value, "ChangeAmount")) {
			this->ChangeAmount = LuaToNumber(l, -1);
		} else if (!strcmp(value, "ChangeMax")) {
			this->ChangeMax = LuaToBoolean(l, -1);
		} else if (!strcmp(value, "Class")) {
			const char *className = LuaToString(l, -1);
			unsigned int i = 0;
			for (; MissileClassNames[i]; ++i) {
				if (!strcmp(className, MissileClassNames[i])) {
					this->Class = i;
					break;
				}
			}
			if (!MissileClassNames[i]) {
				LuaError(l, "Unsupported class: %s" _C_ value);
			}
		} else if (!strcmp(value, "NumBounces")) {
			this->NumBounces = LuaToNumber(l, -1);
		} else if (!strcmp(value, "Delay")) {
			this->StartDelay = LuaToNumber(l, -1);
		} else if (!strcmp(value, "Sleep")) {
			this->Sleep = LuaToNumber(l, -1);
		} else if (!strcmp(value, "Speed")) {
			this->Speed = LuaToNumber(l, -1);
		} else if (!strcmp(value, "TTL")) {
			this->TTL = LuaToNumber(l, -1);
		} else if (!strcmp(value, "Damage")) {
			this->Damage = LuaToNumber(l, -1);
		} else if (!strcmp(value, "DrawLevel")) {
			this->DrawLevel = LuaToNumber(l, -1);
		} else if (!strcmp(value, "Range")) {
			this->Range = LuaToNumber(l, -1);
		} else if (!strcmp(value, "ImpactMissile")) {
			this->Impact.Name = LuaToString(l, -1);
		} else if (!strcmp(value, "SmokeMissile")) {
			this->Smoke.Name = LuaToString(l, -1);
		} else if (!strcmp(value, "ImpactParticle")) {
			this->ImpactParticle = new LuaCallback(l, -1);
		} else if (!strcmp(value, "SmokeParticle")) {
			this->SmokeParticle = new LuaCallback(l, -1);
		} else if (!strcmp(value, "CanHitOwner")) {
			this->CanHitOwner = LuaToBoolean(l, -1);
		} else if (!strcmp(value, "AlwaysFire")) {
			this->AlwaysFire = LuaToBoolean(l, -1);
		} else if (!strcmp(value, "Pierce")) {
			this->Pierce = LuaToBoolean(l, -1);
		} else if (!strcmp(value, "PierceOnce")) {
			this->PierceOnce = LuaToBoolean(l, -1);
		} else if (!strcmp(value, "FriendlyFire")) {
			this->FriendlyFire = LuaToBoolean(l, -1);
		} else if (!strcmp(value, "SplashFactor")) {
			this->SplashFactor = LuaToNumber(l, -1);
		} else if (!strcmp(value, "CorrectSphashDamage")) {
			this->CorrectSphashDamage = LuaToBoolean(l, -1);
		} else {
			LuaError(l, "Unsupported tag: %s" _C_ value);
		}
	}

	if (!file.empty()) {
		this->G = CGraphic::New(file, this->Width(), this->Height());
	}

}