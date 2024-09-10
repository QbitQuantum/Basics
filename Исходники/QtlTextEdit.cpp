int TextEdit::loadResource(lua_State * L) // ( int type, const QUrl & name ) : QVariant virtual
{
	QTextEdit* obj = ObjectHelper<QTextEdit>::check( L, 1);
	QUrl* name = ValueInstaller2<QUrl>::create( L );
	Variant::push( L, obj->loadResource( Util::toInt( L, 2 ), *name ) );
	return 1;
}