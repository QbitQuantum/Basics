 ~MyOGRHandler() {
     m_layer_polygon->CommitTransaction();
     m_layer_linestring->CommitTransaction();
     m_layer_point->CommitTransaction();
     OGRDataSource::DestroyDataSource(m_data_source);
     OGRCleanupAll();
 }