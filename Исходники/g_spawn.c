static void HandleEntityAdjustment(void)
{
	char		*value;
	vec3_t		origin, newOrigin, angles;
	char		temp[MAX_QPATH];
	float		rotation;

	G_SpawnString("origin", NOVALUE, &value);
	if (Q_stricmp(value, NOVALUE) != 0)
	{
		if ( sscanf( value, "%f %f %f", &origin[0], &origin[1], &origin[2] ) != 3 ) {
			G_Printf( "HandleEntityAdjustment: failed sscanf on 'origin' (%s)\n", value );
			VectorClear( origin );
		}
	}
	else
	{
		origin[0] = origin[1] = origin[2] = 0.0;
	}

	rotation = DEG2RAD(level.mRotationAdjust);
	newOrigin[0] = origin[0]*cos(rotation) - origin[1]*sin(rotation);
	newOrigin[1] = origin[0]*sin(rotation) + origin[1]*cos(rotation);
	newOrigin[2] = origin[2];
	VectorAdd(newOrigin, level.mOriginAdjust, newOrigin);
	// damn VMs don't handle outputing a float that is compatible with sscanf in all cases
	Com_sprintf(temp, sizeof( temp ), "%0.0f %0.0f %0.0f", newOrigin[0], newOrigin[1], newOrigin[2]);
	AddSpawnField("origin", temp);

	G_SpawnString("angles", NOVALUE, &value);
	if (Q_stricmp(value, NOVALUE) != 0)
	{
		if ( sscanf( value, "%f %f %f", &angles[0], &angles[1], &angles[2] ) != 3 ) {
			G_Printf( "HandleEntityAdjustment: failed sscanf on 'angles' (%s)\n", value );
			VectorClear( angles );
		}

		angles[YAW] = fmod(angles[YAW] + level.mRotationAdjust, 360.0f);
		// damn VMs don't handle outputing a float that is compatible with sscanf in all cases
		Com_sprintf(temp, sizeof( temp ), "%0.0f %0.0f %0.0f", angles[0], angles[1], angles[2]);
		AddSpawnField("angles", temp);
	}
	else
	{
		G_SpawnString("angle", NOVALUE, &value);
		if (Q_stricmp(value, NOVALUE) != 0)
		{
			angles[YAW] = atof( value );
		}
		else
		{
			angles[YAW] = 0.0;
		}
		angles[YAW] = fmod(angles[YAW] + level.mRotationAdjust, 360.0f);
		Com_sprintf(temp, sizeof( temp ), "%0.0f", angles[YAW]);
		AddSpawnField("angle", temp);
	}

	// RJR experimental code for handling "direction" field of breakable brushes
	// though direction is rarely ever used.
	G_SpawnString("direction", NOVALUE, &value);
	if (Q_stricmp(value, NOVALUE) != 0)
	{
		if ( sscanf( value, "%f %f %f", &angles[0], &angles[1], &angles[2] ) != 3 ) {
			G_Printf( "HandleEntityAdjustment: failed sscanf on 'direction' (%s)\n", value );
			VectorClear( angles );
		}
	}
	else
	{
		angles[0] = angles[1] = angles[2] = 0.0;
	}
	angles[YAW] = fmod(angles[YAW] + level.mRotationAdjust, 360.0f);
	Com_sprintf(temp, sizeof( temp ), "%0.0f %0.0f %0.0f", angles[0], angles[1], angles[2]);
	AddSpawnField("direction", temp);


	AddSpawnField("BSPInstanceID", level.mTargetAdjust);

	G_SpawnString("targetname", NOVALUE, &value);
	if (Q_stricmp(value, NOVALUE) != 0)
	{
		Com_sprintf(temp, sizeof( temp ), "%s%s", level.mTargetAdjust, value);
		AddSpawnField("targetname", temp);
	}

	G_SpawnString("target", NOVALUE, &value);
	if (Q_stricmp(value, NOVALUE) != 0)
	{
		Com_sprintf(temp, sizeof( temp ), "%s%s", level.mTargetAdjust, value);
		AddSpawnField("target", temp);
	}

	G_SpawnString("killtarget", NOVALUE, &value);
	if (Q_stricmp(value, NOVALUE) != 0)
	{
		Com_sprintf(temp, sizeof( temp ), "%s%s", level.mTargetAdjust, value);
		AddSpawnField("killtarget", temp);
	}

	G_SpawnString("brushparent", NOVALUE, &value);
	if (Q_stricmp(value, NOVALUE) != 0)
	{
		Com_sprintf(temp, sizeof( temp ), "%s%s", level.mTargetAdjust, value);
		AddSpawnField("brushparent", temp);
	}

	G_SpawnString("brushchild", NOVALUE, &value);
	if (Q_stricmp(value, NOVALUE) != 0)
	{
		Com_sprintf(temp, sizeof( temp ), "%s%s", level.mTargetAdjust, value);
		AddSpawnField("brushchild", temp);
	}

	G_SpawnString("enemy", NOVALUE, &value);
	if (Q_stricmp(value, NOVALUE) != 0)
	{
		Com_sprintf(temp, sizeof( temp ), "%s%s", level.mTargetAdjust, value);
		AddSpawnField("enemy", temp);
	}

	G_SpawnString("ICARUSname", NOVALUE, &value);
	if (Q_stricmp(value, NOVALUE) != 0)
	{
		Com_sprintf(temp, sizeof( temp ), "%s%s", level.mTargetAdjust, value);
		AddSpawnField("ICARUSname", temp);
	}
}