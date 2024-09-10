//
// Command line.
//
UBOOL UXViewport::Exec( const TCHAR* Cmd, FOutputDevice& Ar )
{
	guard(UXViewport::Exec);
	if( UViewport::Exec( Cmd, Ar ) )
	{
		return 1;
	}
	else if( ParseCommand(&Cmd,TEXT("EndFullscreen")) )
	{
		EndFullscreen();
		return 1;
	}
	else if( ParseCommand(&Cmd,TEXT("ToggleFullscreen")) )
	{
		ToggleFullscreen();
		return 1;
	}
	else if( ParseCommand(&Cmd,TEXT("Iconify")) )
	{
		Iconify();
		return 1;
	}
	else if( ParseCommand(&Cmd,TEXT("GetCurrentRes")) )
	{
		Ar.Logf( TEXT("%ix%i"), SizeX, SizeY, (ColorBytes?ColorBytes:2)*8 );
		return 1;
	}
	else if( ParseCommand(&Cmd,TEXT("GetCurrentColorDepth")) )
	{
		Ar.Logf( TEXT("%i"), (ColorBytes?ColorBytes:2)*8 );
		return 1;
	}
	else if( ParseCommand(&Cmd,TEXT("GetColorDepths")) )
	{
		Ar.Log( TEXT("16 32") );
		return 1;
	}
	else if( ParseCommand(&Cmd,TEXT("GetCurrentRenderDevice")) )
	{
		Ar.Log( RenDev->GetClass()->GetPathName() );
		return 1;
	}
	else if( ParseCommand(&Cmd,TEXT("SetRenderDevice")) )
	{
		FString Saved = RenDev->GetClass()->GetPathName();
		INT SavedSizeX=SizeX, SavedSizeY=SizeY, SavedColorBytes=ColorBytes, SavedFullscreen=((BlitFlags & BLIT_Fullscreen)!=0);
		TryRenderDevice( Cmd, SizeX, SizeY, ColorBytes, SavedFullscreen );
		if( !RenDev )
		{
			TryRenderDevice( *Saved, SavedSizeX, SavedSizeY, SavedColorBytes, SavedFullscreen );
			check(RenDev);
			Ar.Log(TEXT("0"));
		}
		else Ar.Log(TEXT("1"));
		return 1;
	}
	else if( ParseCommand(&Cmd,TEXT("GetRes")) )
	{
		return 1;
	}
	else if( ParseCommand(&Cmd,TEXT("SetRes")) )
	{
		INT X=appAtoi(Cmd);
		TCHAR* CmdTemp = (TCHAR*) (appStrchr(Cmd,'x') ? appStrchr(Cmd,'x')+1 : appStrchr(Cmd,'X') ? appStrchr(Cmd,'X')+1 : TEXT(""));
		INT Y=appAtoi(CmdTemp);
		Cmd = CmdTemp;
		CmdTemp = (TCHAR*) (appStrchr(Cmd,'x') ? appStrchr(Cmd,'x')+1 : appStrchr(Cmd,'X') ? appStrchr(Cmd,'X')+1 : TEXT(""));
		INT C=appAtoi(CmdTemp);
		INT NewColorBytes = C ? C/8 : ColorBytes;
		if( X && Y )
		{
			HoldCount++;
			UBOOL Result = RenDev->SetRes( X, Y, NewColorBytes, IsFullscreen() );
			HoldCount--;
			if( !Result )
				EndFullscreen();
		}
		return 1;
	}
	else if( ParseCommand(&Cmd,TEXT("Preferences")) )
	{
		// No preferences window.
	
		return 1;
	}
	else return 0;
	unguard;
}