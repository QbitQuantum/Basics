static void Add_File_Events(REBGOB *gob, REBINT flags, HDROP drop)
{
	REBEVT evt;
	REBINT num;
	REBINT len;
	REBINT i;
	REBCHR* buf;
	POINT xy;

	//Get the mouse position
	DragQueryPoint(drop, &xy);

	evt.type  = EVT_DROP_FILE;
	evt.flags = (u8) (flags | (1<<EVF_HAS_XY));
	evt.info = 0;
	evt.data = xy.x | xy.y<<16;


	num = DragQueryFile(drop, -1, NULL, 0);

	for (i = 0; i < num; i++){
		len = DragQueryFile(drop, i, NULL, 0);
		buf = OS_Make(len+1);
		DragQueryFile(drop, i, buf, len+1);
		//Reb_Print("DROP: %s", buf);
		buf[len] = 0;
		// ?! convert to REBOL format? E.g.: evt.ser = OS_To_REBOL_File(buf, &len);
		OS_Free(buf);
		if (!Reb_Event(&evt)) break;	// queue is full
	}
}