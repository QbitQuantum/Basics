/**
 *	@call
 *		Font.new						-> font	对象。
 *		Font.new(font_name) 			-> font 对象。
 *		Font.new(font_name, font_size) 	-> font 对象。
 *
 *	@desc
 *		创建一个字体对象。
 */
VALUE CRbFont::initialize(int argc, VALUE * argv, VALUE obj)
{
	//	检查参数个数
	if(argc > 2) rb_raise(rb_eArgError, "wrong number of arguments (%d for 2)", argc);

	//	检查参数有效性
	if(argc > 0) SafeStringValue(argv[0]);
	if(argc > 1) SafeFontSetSize(argv[1]);

	//	初始化默认属性
	m_name			= rb_obj_dup(argc > 0 ? argv[0] : dm_get_default_name(rb_cFont));
	m_size			= argc > 1 ? argv[1] : dm_get_default_size(rb_cFont);
	m_bold			= dm_get_default_bold(rb_cFont);
	m_italic		= dm_get_default_italic(rb_cFont);
	m_shadow		= dm_get_default_shadow(rb_cFont);

	VALUE __argv[1]	= { ULONG2NUM(GetObjectPtr<CRbColor>(__default_color__)->GetColor()) };
	VALUE color		= rb_class_new_instance(1, __argv, rb_cColor);//CRbColor::dm_clone(dm_get_default_color(rb_cFont));
	m_color_ptr		= GetObjectPtr<CRbColor>(color);
	
	//	创建逻辑字体
	m_lfw.lfHeight = FIX2INT(m_size);
	m_lfw.lfItalic = (BYTE)RTEST(m_italic);
	m_lfw.lfWeight = RTEST(m_bold) ? FW_BOLD : FW_NORMAL;
	wcscpy_s(m_lfw.lfFaceName, Kconv::UTF8ToUnicode(RSTRING_PTR(m_name)));

	m_hFont = CreateFontIndirectW(&m_lfw);

	return obj;
}