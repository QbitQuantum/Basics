void run ()
{
  auto in_data_image = Fixel::open_fixel_data_file<float> (argument[0]);
  if (in_data_image.size(2) != 1)
    throw Exception ("Only a single scalar value for each fixel can be output as a track scalar file, "
                     "therefore the input fixel data file must have dimension Nx1x1");

  Header in_index_header = Fixel::find_index_header (Fixel::get_fixel_directory (argument[0]));
  auto in_index_image = in_index_header.get_image<uint32_t>();
  auto in_directions_image = Fixel::find_directions_header (Fixel::get_fixel_directory (argument[0])).get_image<float>().with_direct_io();

  DWI::Tractography::Properties properties;
  DWI::Tractography::Reader<float> reader (argument[1], properties);
  properties.comments.push_back ("Created using fixel2tsf");
  properties.comments.push_back ("Source fixel image: " + Path::basename (argument[0]));
  properties.comments.push_back ("Source track file: " + Path::basename (argument[1]));

  DWI::Tractography::ScalarWriter<float> tsf_writer (argument[2], properties);

  float angular_threshold = get_option_value ("angle", DEFAULT_ANGULAR_THRESHOLD);
  const float angular_threshold_dp = cos (angular_threshold * (Math::pi / 180.0));

  const size_t num_tracks = properties["count"].empty() ? 0 : to<int> (properties["count"]);

  DWI::Tractography::Mapping::TrackMapperBase mapper (in_index_image);
  mapper.set_use_precise_mapping (true);

  ProgressBar progress ("mapping fixel values to streamline points", num_tracks);
  DWI::Tractography::Streamline<float> tck;

  Transform transform (in_index_image);
  Eigen::Vector3 voxel_pos;

  while (reader (tck)) {
    SetVoxelDir dixels;
    mapper (tck, dixels);
    vector<float> scalars (tck.size(), 0.0);
    for (size_t p = 0; p < tck.size(); ++p) {
      voxel_pos = transform.scanner2voxel * tck[p].cast<default_type> ();
      for (SetVoxelDir::const_iterator d = dixels.begin(); d != dixels.end(); ++d) {
        if ((int)round(voxel_pos[0]) == (*d)[0] && (int)round(voxel_pos[1]) == (*d)[1] && (int)round(voxel_pos[2]) == (*d)[2]) {
          assign_pos_of (*d).to (in_index_image);
          Eigen::Vector3f dir = d->get_dir().cast<float>();
          dir.normalize();
          float largest_dp = 0.0;
          int32_t closest_fixel_index = -1;

          in_index_image.index(3) = 0;
          uint32_t num_fixels_in_voxel = in_index_image.value();
          in_index_image.index(3) = 1;
          uint32_t offset = in_index_image.value();

          for (size_t fixel = 0; fixel < num_fixels_in_voxel; ++fixel) {
            in_directions_image.index(0) = offset + fixel;
            float dp = std::abs (dir.dot (Eigen::Vector3f (in_directions_image.row(1))));
            if (dp > largest_dp) {
              largest_dp = dp;
              closest_fixel_index = fixel;
            }
          }
          if (largest_dp > angular_threshold_dp) {
            in_data_image.index(0) = offset + closest_fixel_index;
            scalars[p] = in_data_image.value();
          } else {
            scalars[p] = 0.0;
          }
          break;
        }
      }
    }
    tsf_writer (scalars);
    progress++;
  }
}