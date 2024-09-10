/*
--------------------------------------------------
int PassClipboardDataToObject(ENTITY *e)

Desc: Copies general information from the clipboard 
struct to ENTITY *e, and continues to copy the remaining 
unique characteristics information based on clipboard.of_objtype.

Returns: -1 if e.ObjectType falls out of range (rare) or 
the clipboard is empty. (clipboard.AnyData = 0)
--------------------------------------------------
*/
int PassClipboardDataToObject(ENTITY *e) {
	
	while(!e) wait(1);
	
	WriteLog("[ ] Copying back data from clipboard to ");
	WriteLog( (STRING *) e->type);
	NewLine();

	// Double check
	if(!clipboard.AnyData) {
		
		_beep();
		
		WriteLog("!! [ERROR] Clipboard contains no data, returns -1.");
		NewLine();
		
		return -1;
		
	}

	////////////////////////////////////////////////////////////
	// As usual, pass general data first.
	////////////////////////////////////////////////////////////
	e.ambient = clipboard._ambient;
	e.alpha = clipboard._alpha;

	e.scale_x = clipboard._scale_x;
	e.scale_y = clipboard._scale_y;
	e.scale_z = clipboard._scale_z;

	e.pan = clipboard._pan;
	e.tilt = clipboard._tilt;
	e.roll = clipboard._roll;
	
	int i = 0;
	for(; i < MAX_PUBLIC_SKILLS + MAX_PRIVATE_SKILLS;i++) e.skill[i] = clipboard._skill[i];

	if(clipboard.of_objtype > Object && clipboard.of_objtype <= ObjectNode) {
		
		WriteLog("[ ] Clipboard contains information of a neutral object.");
		NewLine();
		
		e.ObjectType = clipboard.of_objtype;
		
		if(clipboard._flags[0]) set(e,BRIGHT);
		else reset(e,BRIGHT);
		
		if(clipboard._flags[1]) set(e,INVISIBLE);
		else reset(e,INVISIBLE);
		
		if(clipboard._flags[2]) set(e,NOFOG);
		else reset(e,NOFOG);
		
		if(clipboard._flags[3]) set(e,OVERLAY);
		else reset(e,OVERLAY);
		
		if(clipboard._flags[4]) set(e,PASSABLE);
		else reset(e,PASSABLE);
		
		if(clipboard._flags[5]) set(e,POLYGON);
		else reset(e,POLYGON);
		
		if(clipboard._flags[6]) set(e,SHADOW);
		else reset(e,SHADOW);
		
		if(clipboard._flags[7]) set(e,TRANSLUCENT);
		else reset(e,TRANSLUCENT);
		
		WriteLog("[X] Task completed.");
		NewLine();
		
		return 1;
		
	}

	if(clipboard.of_objtype == Light) {
		
		WriteLog("[ ] Clipboard contains information of a light object.");
		NewLine();
		
		e.red = clipboard._red;
		e.green = clipboard._green;
		e.blue = clipboard._blue;
		e.lightrange = clipboard._range;
		e.LightMode = clipboard._LightMode;
		
		#ifndef A7_DEVELOPMENT
		e.material = mtl_model;
		#endif
		
		WriteLog("[X] Task completed.");
		NewLine();
		
		return 1;
		
	}

	if(clipboard.of_objtype == Particle) {
		
		WriteLog("[ ] Clipboard contains information of a particle object.");
		NewLine();
		
		#ifndef A7_DEVELOPMENT
		e.material = mtl_model;
		#endif
		
		WriteLog("[X] Task completed.");
		NewLine();
		
		return 1;
		
	}

	if(clipboard.of_objtype == Sound) {
		
		WriteLog("[ ] Clipboard contains information of a sound object.");
		NewLine();
		
		#ifndef A7_DEVELOPMENT
		e.material = mtl_sprite;
		#endif
		
		WriteLog("[X] Task completed.");
		NewLine();
		
		return 1;
		
	}

	if(clipboard.of_objtype == Sprite) {
		
		WriteLog("[ ] Clipboard contains information of a sprite object.");
		NewLine();
		
		WriteLog("[X] Task completed.");
		NewLine();
		
		return 1;
		
	}

	if(clipboard.of_objtype == Terrain) {
		
		WriteLog("[ ] Clipboard contains information of a terrain.");
		NewLine();
		
		WriteLog("[X] Task completed.");
		NewLine();
		
		return 1;
		
	}

	if(clipboard.of_objtype == ObjectNode) {
		
		WriteLog("[ ] Clipboard contains data of a node object.");
		NewLine();
		
		WriteLog("[X] Task completed.");
		NewLine();
		
		return 1;
		
	}
	
	return -1;

}