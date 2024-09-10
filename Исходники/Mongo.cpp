void Model::PopulateMetaType( Helium::Reflect::MetaStruct& type )
{
	// some db interactions require _id NOT be set (update), so discard the value but load it if we find it in data
	type.AddField( &Model::id, "_id", Reflect::FieldFlags::Discard );
}