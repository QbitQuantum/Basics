static void JsArrayConstCall(struct JsObject *self, struct JsObject *thisobj,
			int argc, struct JsValue **argv, struct JsValue *res){
	struct JsValue v;
	int length;
	
	length = argc;
	if(argc == 1){
		//Array(len)
		length = JsToUint32(argv[0]);
	}
	(*self->Get)(self,"prototype",NULL,&v);
	if(v.type != JS_OBJECT || strcmp(v.u.object->Class,"Array") != 0)
		JsAssert(FALSE);
	struct JsObject* array;
	//根据参数数量不同, 选择初始化模式
	if(argc == 1){
		array = JsCreateArray(v.u.object,length,NULL);
	}else{
		array = JsCreateArray(v.u.object,length,argv);
	}
	res->type = JS_OBJECT;
	res->u.object = array;
}