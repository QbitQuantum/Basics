void ON_InstanceDefinition::UpdateLinkedIdefReferenceFileLayerSettings( unsigned int layer_count, ON_Layer** layer_settings )
{
  ON__IDefLayerSettingsUserData* ud;

  if ( layer_count <= 0 || 0 == layer_settings )
  {
    // delete linked idef layer settings
    ud = ON__IDefLayerSettingsUserData::FindOrCreate(*this,false);
    if ( 0 != ud )
      delete ud;
    return;
  }

  // Create an index_map[] into the layer_settings[] array that is sorted
  // by layer_settings[]->m_layer_id
  ON_Workspace ws;
  int* index_map = (int*)ws.GetMemory(layer_count*sizeof(index_map[0]));
  ON_Sort(ON::quick_sort,index_map,layer_settings,layer_count,sizeof(layer_settings[0]),compareLayerPtrId);

  // Use index_map[] to get a unique list of layers with valid ids
  ON_UuidIndex* iddex = (ON_UuidIndex*)ws.GetMemory(layer_count*sizeof(iddex[0]));
  unsigned int iddex_count = 0;
  unsigned int i;
  ON_Layer* layer;
  for ( i = 0; i < layer_count; i++ )
  {
    layer = layer_settings[index_map[i]];
    if ( 0 == layer )
      continue;
    layer->SaveSettings(0,false); // remove any saved settings on input layers
    if ( ON_UuidIsNil(layer->m_layer_id) )
      continue;
    if ( iddex_count > 0 && iddex[iddex_count-1].m_id == layer->m_layer_id )
      continue;
    iddex[iddex_count].m_i = index_map[i];
    iddex[iddex_count].m_id = layer->m_layer_id;
    iddex_count++;
  }

  if ( iddex_count <= 0 )
  {
    // delete settings
    UpdateLinkedIdefReferenceFileLayerSettings(0,0);
    return;
  }

  // Create or get user data where the saved layer settings
  // are stored.
  ud = ON__IDefLayerSettingsUserData::FindOrCreate(*this,true);
  if ( 0 == ud )
    return;
    
  // Go through the saved settings that were previously
  // on this idef apply those settings to the layer_settings[]
  // list. Then delete the information from ud->m_layers[].
  ON_UuidIndex idx;
  idx.m_i = 0;
  unsigned int settings;
  for ( i = 0; i < ud->m_layers.UnsignedCount(); i++ )
  {
    if ( 0 == ud->m_layers[i] )
      continue;
    layer = ud->m_layers[i];
    ud->m_layers[i] = 0;
    for(;;)
    {
      settings = layer->SavedSettings();
      if ( 0 == settings )
        break; // no settings were modified
      idx.m_id = layer->m_layer_id;
      const ON_UuidIndex* idx0 = (const ON_UuidIndex*)bsearch(&idx,iddex,iddex_count,sizeof(iddex[0]),compareUuidIndexId);
      if ( 0 == idx0)
        break; // this layer is not in the current layer_settings[] list
      layer_settings[idx0->m_i]->SaveSettings(settings,false); // saves the layer settings found in linked file
      layer_settings[idx0->m_i]->Set(settings,*layer);   // applies modifications found on idef
      break;
    }
    delete layer;
  }

  // Save a copy of this information on the user data
  // so it will persist in the file containing the idef.
  ud->m_layers.SetCount(0);
  ud->m_layers.Reserve(iddex_count);
  for ( i = 0; i < iddex_count; i++ )
  {
    layer = new ON_Layer( *layer_settings[iddex[i].m_i] );
    ud->m_layers.Append(layer);
  }
}