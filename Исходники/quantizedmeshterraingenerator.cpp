    virtual Qt3DCore::QEntity *createEntity( Qt3DCore::QEntity *parent )
    {
      Qt3DCore::QEntity *entity = new Qt3DCore::QEntity;

      // create geometry renderer

      Qt3DRender::QGeometryRenderer *mesh = new Qt3DRender::QGeometryRenderer;
      mesh->setGeometry( new QuantizedMeshGeometry( qmt, mTerrain->map3D(), mapSettings.mapToPixel(), mTerrain->terrainToMapTransform(), mesh ) );
      entity->addComponent( mesh );

      // create material

      createTextureComponent( entity );

      // create transform

      Qt3DCore::QTransform *transform;
      transform = new Qt3DCore::QTransform();
      entity->addComponent( transform );

      const Map3D &map = mTerrain->map3D();

      transform->setScale3D( QVector3D( 1.f, map.zExaggeration, 1.f ) );

      QgsRectangle mapExtent = mapSettings.extent();
      float x0 = mapExtent.xMinimum() - map.originX;
      float y0 = mapExtent.yMinimum() - map.originY;
      float x1 = mapExtent.xMaximum() - map.originX;
      float y1 = mapExtent.yMaximum() - map.originY;
      float z0 = qmt->header.MinimumHeight, z1 = qmt->header.MaximumHeight;

      node->setExactBbox( AABB( x0, z0 * map.zExaggeration, -y0, x1, z1 * map.zExaggeration, -y1 ) );
      //epsilon = mapExtent.width() / map.tileTextureSize;

      entity->setEnabled( false );
      entity->setParent( parent );
      return entity;
    }