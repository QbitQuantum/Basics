TextureBinder::TextureBinder( const Texture& texture, GLint unit ) :
    m_texture( texture ),
    m_unit( unit )
{
    KVS_ASSERT( texture.isCreated() );
    kvs::OpenGL::ActivateTextureUnit( unit );
    texture.bind();
}