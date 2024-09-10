void QgsMeshCalcUtils::populateMaskFilter( QgsMeshMemoryDatasetGroup &filter, const QgsGeometry &mask ) const
{
  filter.clearDatasets();
  std::shared_ptr<QgsMeshMemoryDataset> output = create( filter );
  output->time = mTimes[0];

  const QVector<int> trianglesToNativeFaces = triangularMesh()->trianglesToNativeFaces();
  const QVector<QgsMeshVertex> &vertices = triangularMesh()->vertices();

  if ( mOutputType == QgsMeshDatasetGroupMetadata::DataOnVertices )
  {
    int nativeVertexCount = mMeshLayer->dataProvider()->vertexCount();

    for ( int i = 0; i < nativeVertexCount; ++i )
    {
      const QgsPointXY point( vertices[i] );
      if ( mask.contains( &point ) )
      {
        output->values[i].set( D_TRUE );
      }
      else
      {
        output->values[i].set( D_FALSE );
      }
    }
  }
  else
  {
    const QVector<QgsMeshFace> &triangles = triangularMesh()->triangles();
    for ( int i = 0; i < triangles.size(); ++i )
    {
      const QgsMeshFace face = triangles[i];
      const QgsGeometry geom = QgsMeshUtils::toGeometry( face, vertices );
      const QgsRectangle bbox = geom.boundingBox();
      if ( mask.intersects( bbox ) )
      {
        output->values[i].set( D_TRUE );
      }
      else
      {
        output->values[i].set( D_FALSE );
      }
    }
  }
  filter.addDataset( output );
}