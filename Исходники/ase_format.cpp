static Layer *ase_file_read_layer_chunk(FILE *f, Sprite *sprite, Layer **previous_layer, int *current_level)
{
  std::string name;
  Layer *layer = NULL;
  /* read chunk data */
  int flags;
  int layer_type;
  int child_level;

  flags = fgetw(f);
  layer_type = fgetw(f);
  child_level = fgetw(f);
  fgetw(f);                     // default width
  fgetw(f);                     // default height
  fgetw(f);                     // blend mode

  ase_file_read_padding(f, 4);
  name = ase_file_read_string(f);

  /* image layer */
  if (layer_type == 0) {
    layer = new LayerImage(sprite);
  }
  /* layer set */
  else if (layer_type == 1) {
    layer = new LayerFolder(sprite);
  }

  if (layer) {
    // flags
    layer->setFlags(flags);

    // name
    layer->setName(name.c_str());

    // child level...
    if (child_level == *current_level)
      (*previous_layer)->get_parent()->add_layer(layer);
    else if (child_level > *current_level)
      static_cast<LayerFolder*>(*previous_layer)->add_layer(layer);
    else if (child_level < *current_level)
      (*previous_layer)->get_parent()->get_parent()->add_layer(layer);

    *previous_layer = layer;
    *current_level = child_level;
  }

  return layer;
}