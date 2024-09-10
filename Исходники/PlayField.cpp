PlayField::PlayField(Hiscore *h, View *parent, ScrollText *st) : View(Rect(0,0,1,1)), Message(){ //-.25f,-.25f,1.25f,1.25f)){

//	Listen("/Devices/Input/Dialogic");
	SetClearState(false);

	#ifdef NEWSCALE

	parent->Apply(this);
	players  = new DynamicArray();
	channels = new DynamicArray();
	int dir = 0;
	int x = 1;
	int y = 1;
	int xr = 2;
	int yb = 2;
	int xl = 0;
	int yt = 0;
	int n = 1;
	for(int _x=0; _x<4; _x++){
		for(int _y=0; _y<4; _y++){
			Player *pl = new Player(h,Rect((float(x)/4.0f),(float(y)/4.0f),(float(x+1)/4.0f),(float(y+1)/4.0f)),st,n++);
			Apply(pl);
			players->Add(pl);
			channels->Add(0);
			switch(dir){
			case 0: if(++x==xr){ dir++; xr++; } break;
			case 1: if(++y==yb){ dir++; yb++; } break;
			case 2: if(--x==xl){ dir++; xl--; } break;
			case 3: if(--y==yt){ dir=0; yt--; } break;
			}
		}
	}

	#else

	parent->Apply(this);
	players  = new DynamicArray();
	channels = new DynamicArray();
	int dir = 0;
	int x = 1;
	int y = 1;
	int xr = 2;
	int yb = 2;
	int xl = 1;
	int yt = 1;
	int n = 1;
	for(int _x=0; _x<4; _x++){
		for(int _y=0; _y<4; _y++){
			Player *pl = new Player(h,Rect((float(x)/4.0f),(float(y)/4.0f),(float(x+1)/4.0f),(float(y+1)/4.0f)),st,n++);
			Apply(pl);
			players->Add(pl);
			channels->Add(0);
			switch(dir){
			case 0: if(++x==xr){ dir++; xr++; } break;
			case 1: if(++y==yb){ dir++; yb++; } break;
			case 2: if(--x==xl){ dir++; xl--; } break;
			case 3: if(--y==yt){ dir=0; yt--; x--; y--; } break;
			}
		}
	}
	#endif
	foo = 0;
	player_count=0;

	zoom = .5f;
	xz = yz = 0;

	Listen("/Devices/Input/Dialogic");
}