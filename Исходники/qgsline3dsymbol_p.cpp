void QgsSimpleLine3DSymbolHandler::makeEntity( Qt3DCore::QEntity *parent, const Qgs3DRenderContext &context, LineData &out, bool selected )
{
  if ( out.indexes.isEmpty() )
    return;

  // material (only ambient color is used for the color)

  Qt3DExtras::QPhongMaterial *mat = _material( mSymbol );
  if ( selected )
  {
    // update the material with selection colors
    mat->setAmbient( context.map().selectionColor() );
  }

  // geometry renderer

  QByteArray vertexBufferData;
  vertexBufferData.resize( out.vertices.size() * 3 * sizeof( float ) );
  float *rawVertexArray = reinterpret_cast<float *>( vertexBufferData.data() );
  int idx = 0;
  for ( const auto &v : qgis::as_const( out.vertices ) )
  {
    rawVertexArray[idx++] = v.x();
    rawVertexArray[idx++] = v.y();
    rawVertexArray[idx++] = v.z();
  }

  QByteArray indexBufferData;
  indexBufferData.resize( out.indexes.size() * sizeof( int ) );
  unsigned int *rawIndexArray = reinterpret_cast<unsigned int *>( indexBufferData.data() );
  idx = 0;
  for ( unsigned int indexVal : qgis::as_const( out.indexes ) )
  {
    rawIndexArray[idx++] = indexVal;
  }

  Qt3DCore::QEntity *entity = new Qt3DCore::QEntity;

  Qt3DRender::QBuffer *vertexBuffer = new Qt3DRender::QBuffer( Qt3DRender::QBuffer::VertexBuffer, entity );
  vertexBuffer->setData( vertexBufferData );

  Qt3DRender::QBuffer *indexBuffer = new Qt3DRender::QBuffer( Qt3DRender::QBuffer::IndexBuffer, entity );
  indexBuffer->setData( indexBufferData );

  Qt3DRender::QAttribute *positionAttribute = new Qt3DRender::QAttribute( entity );
  positionAttribute->setAttributeType( Qt3DRender::QAttribute::VertexAttribute );
  positionAttribute->setBuffer( vertexBuffer );
  positionAttribute->setVertexBaseType( Qt3DRender::QAttribute::Float );
  positionAttribute->setVertexSize( 3 );
  positionAttribute->setName( Qt3DRender::QAttribute::defaultPositionAttributeName() );

  Qt3DRender::QAttribute *indexAttribute = new Qt3DRender::QAttribute( entity );
  indexAttribute->setAttributeType( Qt3DRender::QAttribute::IndexAttribute );
  indexAttribute->setBuffer( indexBuffer );
  indexAttribute->setVertexBaseType( Qt3DRender::QAttribute::UnsignedInt );

  Qt3DRender::QGeometry *geom = new Qt3DRender::QGeometry;
  geom->addAttribute( positionAttribute );
  geom->addAttribute( indexAttribute );

  Qt3DRender::QGeometryRenderer *renderer = new Qt3DRender::QGeometryRenderer;
  renderer->setPrimitiveType( Qt3DRender::QGeometryRenderer::LineStrip );
  renderer->setGeometry( geom );
  renderer->setVertexCount( out.vertices.count() );
  renderer->setPrimitiveRestartEnabled( true );
  renderer->setRestartIndexValue( 0 );

  // make entity
  entity->addComponent( renderer );
  entity->addComponent( mat );
  entity->setParent( parent );
}