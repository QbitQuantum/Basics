//==========================================================================
// The actual light def parsing code is there.
// DoParseDefs is no longer called directly by ParseDefs, now it's called
// by LoadDynLightDefs, which wasn't simply integrated into ParseDefs
// because of the way the code needs to load two out of five lumps.
//==========================================================================
void gl_DoParseDefs(FScanner &sc, int workingLump)
{
	int recursion=0;
	int lump, type;

	// Get actor class name.
	while (true)
	{
		sc.SavePos();
		if (!sc.GetToken ())
		{
			return;
		}
		type = sc.MatchString(CoreKeywords);
		switch (type)
		{
		case TAG_INCLUDE:
			{
				sc.MustGetString();
				// This is not using sc.Open because it can print a more useful error message when done here
				lump = Wads.CheckNumForFullName(sc.String, true);
				if (lump==-1)
					sc.ScriptError("Lump '%s' not found", sc.String);

				FScanner newscanner(lump);
				gl_DoParseDefs(newscanner, lump);
				break;
			}
		case LIGHT_POINT:
			gl_ParsePointLight(sc);
			break;
		case LIGHT_PULSE:
			gl_ParsePulseLight(sc);
			break;
		case LIGHT_FLICKER:
			gl_ParseFlickerLight(sc);
			break;
		case LIGHT_FLICKER2:
			gl_ParseFlickerLight2(sc);
			break;
		case LIGHT_SECTOR:
			gl_ParseSectorLight(sc);
			break;
		case LIGHT_OBJECT:
			gl_ParseObject(sc);
			break;
		case LIGHT_CLEAR:
			gl_ReleaseLights();
			break;
		case TAG_SHADER:
			gl_ParseShader(sc);
			break;
		case TAG_CLEARSHADERS:
			break;
		case TAG_SKYBOX:
			gl_ParseSkybox(sc);
			break;
		case TAG_GLOW:
			gl_InitGlow(sc);
			break;
		case TAG_BRIGHTMAP:
			gl_ParseBrightmap(sc, workingLump);
			break;
		case TAG_HARDWARESHADER:
			gl_ParseHardwareShader(sc, workingLump);
			break;
		case TAG_DETAIL:
			gl_ParseDetailTexture(sc);
			break;
		case TAG_DISABLE_FB:
			{
				/* not implemented.
				sc.MustGetString();
				const PClass *cls = PClass::FindClass(sc.String);
				if (cls) GetDefaultByType(cls)->renderflags |= RF_NEVERFULLBRIGHT;
				*/
			}
			break;
		default:
			sc.ScriptError("Error parsing defs.  Unknown tag: %s.\n", sc.String);
			break;
		}
	}
}