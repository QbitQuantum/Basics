void ParseDecorate (FScanner &sc)
{
	// Get actor class name.
	for(;;)
	{
		FScanner::SavedPos pos = sc.SavePos();
		if (!sc.GetToken ())
		{
			return;
		}
		switch (sc.TokenType)
		{
		case TK_Include:
		{
			sc.MustGetString();
			// This check needs to remain overridable for testing purposes.
			if (Wads.GetLumpFile(sc.LumpNum) == 0 && !Args->CheckParm("-allowdecoratecrossincludes"))
			{
				int includefile = Wads.GetLumpFile(Wads.CheckNumForFullName(sc.String, true));
				if (includefile != 0)
				{
					I_FatalError("File %s is overriding core lump %s.",
						Wads.GetWadFullName(includefile), sc.String);
				}
			}
			FScanner newscanner;
			newscanner.Open(sc.String);
			ParseDecorate(newscanner);
			break;
		}

		case TK_Const:
			ParseConstant (sc, &GlobalSymbols, NULL);
			break;

		case TK_Enum:
			ParseEnum (sc, &GlobalSymbols, NULL);
			break;

		case ';':
			// ';' is the start of a comment in the non-cmode parser which
			// is used to parse parts of the DECORATE lump. If we don't add 
			// a check here the user will only get weird non-informative
			// error messages if a semicolon is found.
			sc.ScriptError("Unexpected ';'");
			break;

		case TK_Identifier:
			// 'ACTOR' cannot be a keyword because it is also needed as a class identifier
			// so let's do a special case for this.
			if (sc.Compare("ACTOR"))
			{
				ParseActor (sc);
				break;
			}
			else if (sc.Compare("PICKUP"))
			{
				ParseOldDecoration (sc, DEF_Pickup);
				break;
			}
			else if (sc.Compare("BREAKABLE"))
			{
				ParseOldDecoration (sc, DEF_BreakableDecoration);
				break;
			}
			else if (sc.Compare("PROJECTILE"))
			{
				ParseOldDecoration (sc, DEF_Projectile);
				break;
			}
			else if (sc.Compare("DAMAGETYPE"))
			{
				ParseDamageDefinition(sc);
				break;
			}
		default:
			sc.RestorePos(pos);
			ParseOldDecoration(sc, DEF_Decoration);
			break;
		}
	}
}