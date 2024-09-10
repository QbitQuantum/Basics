void Vector4::PopulateMetaType( Reflect::MetaStruct& comp )
{
	comp.AddField( &Vector4::x, "x" );
	comp.AddField( &Vector4::y, "y" );
	comp.AddField( &Vector4::z, "z" );
	comp.AddField( &Vector4::w, "w" );
}