static int Init(win* p)
{
	tchar_t s[256];
	packetformat Format;
	int No;
	node* VOutput = NULL;
	node* Reader = NULL;
	node* Input = NULL;
	node* Player = Context()->Player;
	winunit y;

	Player->Get(Player,PLAYER_FORMAT,&Reader,sizeof(Reader));
	Player->Get(Player,PLAYER_INPUT,&Input,sizeof(Input));
	Player->Get(Player,PLAYER_VOUTPUT,&VOutput,sizeof(VOutput));

	y = 4;

	if (Input)
		Info(p,Input,&y,0);

	if (Reader)
	{
		pin Pin;

		Info(p,Reader,&y,MEDIAINFO_FORMAT);
		Comment(p,(player*)Player,&y,-1);

		for (No=0;Reader->Get(Reader,FORMAT_STREAM+No,&Pin,sizeof(Pin))==ERR_NONE;++No)
			if (PlayerGetStream((player*)Player,No,&Format,NULL,0,NULL))
			{
				y += 6;

				if (Format.Type != PACKET_NONE)
				{
					if (!PacketFormatName(&Format,s,TSIZEOF(s))) s[0] =0;
					WinPropLabel(p,&y,LangStr(PLAYER_ID,STREAM_NAME+Format.Type),s);
				}

				switch (Format.Type)
				{
				case PACKET_NONE:
					break;

				case PACKET_VIDEO:
					if (Pin.Node && Compressed(&Format.Format.Video.Pixel))
						Info(p,Pin.Node,&y,MEDIAINFO_CODEC);

					if (Format.Format.Video.Width && Format.Format.Video.Height)
					{
						stprintf_s(s,TSIZEOF(s),T("%d x %d"),Format.Format.Video.Width,Format.Format.Video.Height);
						WinPropLabel(p,&y,LangStr(MEDIAINFO_ID,MEDIAINFO_SIZE),s);
					}
					if (Format.PacketRate.Num)
					{
						FractionToString(s,TSIZEOF(s),&Format.PacketRate,0,3);
						WinPropLabel(p,&y,LangStr(MEDIAINFO_ID,MEDIAINFO_FPS),s);
					}
					if (Format.ByteRate)
					{
						IntToString(s,TSIZEOF(s),(Format.ByteRate+62)/125,0);
						tcscat_s(s,TSIZEOF(s),T(" kbit/s")); // 1000byte/sec
						WinPropLabel(p,&y,LangStr(MEDIAINFO_ID,MEDIAINFO_BITRATE),s);
					}

					break;

				case PACKET_AUDIO:

					if (Pin.Node && Format.Format.Audio.Format != AUDIOFMT_PCM)
						Info(p,Pin.Node,&y,MEDIAINFO_CODEC);

					s[0] = 0;
					if (Format.Format.Audio.SampleRate)
					{
						IntToString(s+tcslen(s),TSIZEOF(s)-tcslen(s),Format.Format.Audio.SampleRate,0);
						tcscat_s(s,TSIZEOF(s),T(" Hz "));
					}
					switch (Format.Format.Audio.Channels)
					{
					case 0: break;
					case 1: tcscat_s(s,TSIZEOF(s),LangStr(MEDIAINFO_ID,MEDIAINFO_AUDIO_MONO)); break;
					case 2: tcscat_s(s,TSIZEOF(s),LangStr(MEDIAINFO_ID,MEDIAINFO_AUDIO_STEREO)); break;
					default: stcatprintf_s(s,TSIZEOF(s),T("%d Ch"),Format.Format.Audio.Channels); break;
					}
					if (s[0])
						WinPropLabel(p,&y,LangStr(MEDIAINFO_ID,MEDIAINFO_FORMAT),s);

					if (Format.ByteRate)
					{
						IntToString(s,TSIZEOF(s),(Format.ByteRate+62)/125,0);
						tcscat_s(s,TSIZEOF(s),T(" kbit/s")); // 1000bit/sec
						WinPropLabel(p,&y,LangStr(MEDIAINFO_ID,MEDIAINFO_BITRATE),s);
					}

					break;

				case PACKET_SUBTITLE:
					if (Pin.Node)
						Info(p,Pin.Node,&y,MEDIAINFO_CODEC);
					break;
				}

				Comment(p,(player*)Player,&y,No);
			}

		if (VOutput)
		{
			int Total = 0;
			int Dropped = 0;

			VOutput->Get(VOutput,OUT_TOTAL,&Total,sizeof(int));
			VOutput->Get(VOutput,OUT_DROPPED,&Dropped,sizeof(int));

			Total += Dropped;
			if (Total)
			{
				y += 6;

				IntToString(s,TSIZEOF(s),Total,0);
				WinPropLabel(p,&y,LangStr(MEDIAINFO_ID,MEDIAINFO_VIDEO_TOTAL),s);

				IntToString(s,TSIZEOF(s),Dropped,0);
				WinPropLabel(p,&y,LangStr(MEDIAINFO_ID,MEDIAINFO_VIDEO_DROPPED),s);

				Player->Get(Player,PLAYER_VSTREAM,&No,sizeof(No));
				if (No>=0 && Reader->Get(Reader,(FORMAT_STREAM+No)|PIN_FORMAT,&Format,sizeof(Format))==ERR_NONE &&
					Format.Type == PACKET_VIDEO && Format.PacketRate.Num)
				{
					Simplify(&Format.PacketRate,(1<<30)/Total,(1<<30)/Total);
					Format.PacketRate.Num *= Total - Dropped;
					Format.PacketRate.Den *= Total;
					FractionToString(s,TSIZEOF(s),&Format.PacketRate,0,3);
					WinPropLabel(p,&y,LangStr(MEDIAINFO_ID,MEDIAINFO_AVG_FPS),s);
				}
			}
		}
	}

	return ERR_NONE;
}