static VALUE
swinilist_getimageinfo(VALUE obj, VALUE idx){
	struct SwinImagelist* si;
	IMAGEINFO imi;
	int index;
	VALUE robj,rect;

	index = NUM2INT(idx);

	Data_Get_Struct(obj,struct SwinImagelist,si);
	SWIN_IMAGELISTALIVECHECK(si)
	if(ImageList_GetImageInfo(si->himagelist,index,&imi)==0){
		rb_raise(rb_eRuntimeError,
			"ImageList_GetImageInfo failed for index:%d",index);
		return Qfalse;
	}
	robj = rb_ary_new2(3);
	rb_ary_push(robj,UINT2NUM((unsigned)imi.hbmImage));
	rb_ary_push(robj,UINT2NUM((unsigned)imi.hbmMask));
	rect = rb_ary_new2(4);
	rb_ary_push(rect,INT2NUM(imi.rcImage.left));
	rb_ary_push(rect,INT2NUM(imi.rcImage.top));
	rb_ary_push(rect,INT2NUM(imi.rcImage.right));
	rb_ary_push(rect,INT2NUM(imi.rcImage.bottom));
	rb_ary_push(robj,rect);
	return robj;
}