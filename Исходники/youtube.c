void DecodeYouTubeFormats(char *Formats, ListNode *Vars)
{
char *Token=NULL, *Tempstr=NULL, *TypeCode=NULL, *URL=NULL, *ptr;

ptr=Gettoken(Formats,",",&Token,0);
while (ptr)
{
	YouTubeFormatGetData(Token, &URL, &TypeCode);
	switch (atoi(TypeCode))
	{
			case 5:
			SetVar(Vars,"item:flv:400x240",URL);
			break;

			case 6:
			SetVar(Vars,"item:flv:480x270",URL);
			break;

			case 13:
			SetVar(Vars,"item:3gp",URL);
			break;

			case 17:
			SetVar(Vars,"item:3gp:176x144",URL);
			break;

			case 18:
			SetVar(Vars,"item:mp4:480x360",URL);
			break;

			case 22:
			SetVar(Vars,"item:mp4:1280x720",URL);
			break;

			case 34:
			SetVar(Vars,"item:flv-h264:640x360",URL);
			break;

			case 35:
			SetVar(Vars,"item:flv-h264:854x480",URL);
			break;

			case 36:
			SetVar(Vars,"item:3gp:400x240",URL);
			break;


			case 37:
			SetVar(Vars,"item:mp4:1920x1080",URL);
			break;

			case 38:
			SetVar(Vars,"item:mp4:4096x3072",URL);
			break;

			case 43:
			SetVar(Vars,"item:webm:640x360",URL);
			break;

			case 44:
			SetVar(Vars,"item:webm:854x480",URL);
			break;

			case 45:
			SetVar(Vars,"item:webm:1280x720",URL);
			break;

			case 46:
			SetVar(Vars,"item:webm:1920x1080",URL);
			break;

			case 82:
			SetVar(Vars,"item:mp4-3D:640x360",URL);
			break;

			case 83:
			SetVar(Vars,"item:mp4-3D:854x240",URL);
			break;

			case 84:
			SetVar(Vars,"item:mp4-3D:1280x720",URL);
			break;

			case 85:
			SetVar(Vars,"item:mp4-3D:1920x520",URL);
			break;

			case 100:
			SetVar(Vars,"item:webm-3D:640x360",URL);
			break;

			case 101:
			SetVar(Vars,"item:webm-3D:854x480",URL);
			break;

			case 102:
			SetVar(Vars,"item:webm-3D:1280x720",URL);
			break;



			default:
			//	if (! Flags & FLAG_QUIET)
			if (StrLen(ptr)) fprintf(stderr,"Unknown youtube format [%s]\n",Token);
			break;
		}
ptr=Gettoken(ptr,",",&Token,0);
}

DestroyString(TypeCode);
DestroyString(URL);
DestroyString(Token);
DestroyString(Tempstr);
}