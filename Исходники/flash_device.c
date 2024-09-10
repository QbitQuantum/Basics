void flash_device_listup(struct flash_listup *t)
{
	const wgChar *str;
	HSQUIRRELVM v = qr_open(NULL);
	SQInteger top = sq_gettop(v);

	if(SQ_FAILED(sqstd_dofile(v, _SC("flashdevice.nut"), SQFalse, SQTrue))){
//		puts("flash device script error");
		qr_close(v);
		return;
	}

	int i;
	const int device_num = flash_device_number_get(v);
	sq_settop(v, top);

	for(i = 0; i < device_num; i++){
		flash_device_name_get(v, i, &str);
		if(STRNCMP(str, _SC("dummy"), 6) != 0){
			t->append(t->obj_cpu, str);
			t->append(t->obj_ppu, str);
		}
		sq_settop(v, top);
	}

	qr_close(v);
	v = NULL;
}