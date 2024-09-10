void run ()
{
  auto input_header = Header::open (argument[0]);
  Header output_header (input_header);
  output_header.datatype() = DataType::from_command_line (DataType::from<float> ());

  // Linear
  transform_type linear_transform;
  bool linear = false;
  auto opt = get_options ("linear");
  if (opt.size()) {
    linear = true;
    linear_transform = load_transform (opt[0][0]);
  } else {
    linear_transform.setIdentity();
  }

  // Replace
  const bool replace = get_options ("replace").size();
  if (replace && !linear) {
    INFO ("no linear is supplied so replace with the default (identity) transform");
    linear = true;
  }

  // Template
  opt = get_options ("template");
  Header template_header;
  if (opt.size()) {
    if (replace)
      throw Exception ("you cannot use the -replace option with the -template option");
    template_header = Header::open (opt[0][0]);
    for (size_t i = 0; i < 3; ++i) {
      output_header.size(i) = template_header.size(i);
      output_header.spacing(i) = template_header.spacing(i);
    }
    output_header.transform() = template_header.transform();
    add_line (output_header.keyval()["comments"], std::string ("regridded to template image \"" + template_header.name() + "\""));
  }

  // Warp 5D warp
  // TODO add reference to warp format documentation
  opt = get_options ("warp_full");
  Image<default_type> warp;
  if (opt.size()) {
    warp = Image<default_type>::open (opt[0][0]).with_direct_io();
    if (warp.ndim() != 5)
      throw Exception ("the input -warp_full image must be a 5D file.");
    if (warp.size(3) != 3)
      throw Exception ("the input -warp_full image must have 3 volumes (x,y,z) in the 4th dimension.");
    if (warp.size(4) != 4)
      throw Exception ("the input -warp_full image must have 4 volumes in the 5th dimension.");
    if (linear)
      throw Exception ("the -warp_full option cannot be applied in combination with -linear since the "
                       "linear transform is already included in the warp header");
  }

  // Warp from image1 or image2
  int from = 1;
  opt = get_options ("from");
  if (opt.size()) {
    from = opt[0][0];
    if (!warp.valid())
      WARN ("-from option ignored since no 5D warp was input");
  }

  // Warp deformation field
  opt = get_options ("warp");
  if (opt.size()) {
    if (warp.valid())
      throw Exception ("only one warp field can be input with either -warp or -warp_mid");
    warp = Image<default_type>::open (opt[0][0]).with_direct_io (Stride::contiguous_along_axis(3));
    if (warp.ndim() != 4)
      throw Exception ("the input -warp file must be a 4D deformation field");
    if (warp.size(3) != 3)
      throw Exception ("the input -warp file must have 3 volumes in the 4th dimension (x,y,z positions)");
  }

  // Inverse
  const bool inverse = get_options ("inverse").size();
  if (inverse) {
    if (!(linear || warp.valid()))
      throw Exception ("no linear or warp transformation provided for option '-inverse'");
    if (warp.valid())
      if (warp.ndim() == 4)
        throw Exception ("cannot apply -inverse with the input -warp_df deformation field.");
    linear_transform = linear_transform.inverse();
  }

  // Half
  const bool half = get_options ("half").size();
  if (half) {
    if (!(linear))
      throw Exception ("no linear transformation provided for option '-half'");
    {
      Eigen::Matrix<default_type, 4, 4> temp;
      temp.row(3) << 0, 0, 0, 1.0;
      temp.topLeftCorner(3,4) = linear_transform.matrix().topLeftCorner(3,4);
      linear_transform.matrix() = temp.sqrt().topLeftCorner(3,4);
    }
  }

  // Flip
  opt = get_options ("flip");
  if (opt.size()) {
    std::vector<int> axes = opt[0][0];
    transform_type flip;
    flip.setIdentity();
    for (size_t i = 0; i < axes.size(); ++i) {
      if (axes[i] < 0 || axes[i] > 2)
        throw Exception ("axes supplied to -flip are out of bounds (" + std::string (opt[0][0]) + ")");
      flip(axes[i],3) += flip(axes[i],axes[i]) * input_header.spacing(axes[i]) * (input_header.size(axes[i])-1);
      flip(axes[i], axes[i]) *= -1.0;
    }
    if (!replace)
      flip = input_header.transform() * flip * input_header.transform().inverse();
    linear_transform = linear_transform * flip;
    linear = true;
  }

  Stride::List stride = Stride::get (input_header);

  // Detect FOD image for reorientation
  opt = get_options ("noreorientation");
  bool fod_reorientation = false;
  Eigen::MatrixXd directions_cartesian;
  if (!opt.size() && (linear || warp.valid() || template_header.valid()) && input_header.ndim() == 4 &&
      input_header.size(3) >= 6 &&
      input_header.size(3) == (int) Math::SH::NforL (Math::SH::LforN (input_header.size(3)))) {
    CONSOLE ("SH series detected, performing apodised PSF reorientation");
    fod_reorientation = true;

    Eigen::MatrixXd directions_az_el;
    opt = get_options ("directions");
    if (opt.size())
      directions_az_el = load_matrix (opt[0][0]);
    else
      directions_az_el = DWI::Directions::electrostatic_repulsion_300();
    Math::SH::spherical2cartesian (directions_az_el, directions_cartesian);

    // load with SH coeffients contiguous in RAM
    stride = Stride::contiguous_along_axis (3, input_header);
  }

  // Modulate FODs
  bool modulate = false;
  if (get_options ("modulate").size()) {
    modulate = true;
    if (!fod_reorientation)
      throw Exception ("modulation can only be performed with FOD reorientation");
  }

  // Rotate/Flip gradient directions if present
  if (linear && input_header.ndim() == 4 && !warp && !fod_reorientation) {
    try {
      auto grad = DWI::get_DW_scheme (input_header);
      if (input_header.size(3) == (ssize_t) grad.rows()) {
        INFO ("DW gradients detected and will be reoriented");
        Eigen::MatrixXd rotation = linear_transform.linear();
        Eigen::MatrixXd test = rotation.transpose() * rotation;
        test = test.array() / test.diagonal().mean();
        if (!test.isIdentity (0.001))
        WARN ("the input linear transform contains shear or anisotropic scaling and "
              "therefore should not be used to reorient diffusion gradients");
        if (replace)
          rotation = linear_transform.linear() * input_header.transform().linear().inverse();
        for (ssize_t n = 0; n < grad.rows(); ++n) {
          Eigen::Vector3 grad_vector = grad.block<1,3>(n,0);
          grad.block<1,3>(n,0) = rotation * grad_vector;
        }
        DWI::set_DW_scheme (output_header, grad);
      }
    }
    catch (Exception& e) {
      e.display (2);
    }
  }

  // Interpolator
  int interp = 2;  // cubic
  opt = get_options ("interp");
  if (opt.size()) {
    interp = opt[0][0];
    if (!warp && !template_header)
      WARN ("interpolator choice ignored since the input image will not be regridded");
  }

  // Out of bounds value
  float out_of_bounds_value = 0.0;
  opt = get_options ("nan");
  if (opt.size()) {
    out_of_bounds_value = NAN;
    if (!warp && !template_header)
      WARN ("Out of bounds value ignored since the input image will not be regridded");
  }

  auto input = input_header.get_image<float>().with_direct_io (stride);

  // Reslice the image onto template
  if (template_header.valid() && !warp) {
    INFO ("image will be regridded");

    if (get_options ("midway_space").size()) {
      INFO("regridding to midway space");
      std::vector<Header> headers;
      headers.push_back(input_header);
      headers.push_back(template_header);
      std::vector<Eigen::Transform<default_type, 3, Eigen::Projective>> void_trafo;
      auto padding = Eigen::Matrix<double, 4, 1>(1.0, 1.0, 1.0, 1.0);
      int subsampling = 1;
      auto midway_header = compute_minimum_average_header (headers, subsampling, padding, void_trafo);
      for (size_t i = 0; i < 3; ++i) {
        output_header.size(i) = midway_header.size(i);
        output_header.spacing(i) = midway_header.spacing(i);
      }
      output_header.transform() = midway_header.transform();
    }

    if (interp == 0)
      output_header.datatype() = DataType::from_command_line (input_header.datatype());
    auto output = Image<float>::create (argument[1], output_header).with_direct_io();

    switch (interp) {
      case 0:
        Filter::reslice<Interp::Nearest> (input, output, linear_transform, Adapter::AutoOverSample, out_of_bounds_value);
        break;
      case 1:
        Filter::reslice<Interp::Linear> (input, output, linear_transform, Adapter::AutoOverSample, out_of_bounds_value);
        break;
      case 2:
        Filter::reslice<Interp::Cubic> (input, output, linear_transform, Adapter::AutoOverSample, out_of_bounds_value);
        break;
      case 3:
        Filter::reslice<Interp::Sinc> (input, output, linear_transform, Adapter::AutoOverSample, out_of_bounds_value);
        break;
      default:
        assert (0);
        break;
    }

    if (fod_reorientation)
      Registration::Transform::reorient ("reorienting", output, output, linear_transform, directions_cartesian.transpose(), modulate);

  } else if (warp.valid()) {

    if (replace)
      throw Exception ("you cannot use the -replace option with the -warp or -warp_df option");

    if (!template_header) {
      for (size_t i = 0; i < 3; ++i) {
        output_header.size(i) = warp.size(i);
        output_header.spacing(i) = warp.spacing(i);
      }
      output_header.transform() = warp.transform();
      add_line (output_header.keyval()["comments"], std::string ("resliced using warp image \"" + warp.name() + "\""));
    }

    auto output = Image<float>::create(argument[1], output_header).with_direct_io();

    if (warp.ndim() == 5) {
      Image<default_type> warp_deform;

      // Warp to the midway space defined by the warp grid
      if (get_options ("midway_space").size()) {
        warp_deform = Registration::Warp::compute_midway_deformation (warp, from);
      // Use the full transform to warp from the image image to the template
      } else {
        warp_deform = Registration::Warp::compute_full_deformation (warp, template_header, from);
      }
      apply_warp (input, output, warp_deform, interp, out_of_bounds_value);
      if (fod_reorientation)
        Registration::Transform::reorient_warp ("reorienting", output, warp_deform, directions_cartesian.transpose(), modulate);

    // Compose and apply input linear and 4D deformation field
    } else if (warp.ndim() == 4 && linear) {
      auto warp_composed = Image<default_type>::scratch (warp);
      Registration::Warp::compose_linear_deformation (linear_transform, warp, warp_composed);
      apply_warp (input, output, warp_composed, interp, out_of_bounds_value);
      if (fod_reorientation)
        Registration::Transform::reorient_warp ("reorienting", output, warp_composed, directions_cartesian.transpose(), modulate);

    // Apply 4D deformation field only
    } else {
      apply_warp (input, output, warp, interp, out_of_bounds_value);
      if (fod_reorientation)
        Registration::Transform::reorient_warp ("reorienting", output, warp, directions_cartesian.transpose(), modulate);
    }

  // No reslicing required, so just modify the header and do a straight copy of the data
  } else {

    if (get_options ("midway").size())
      throw Exception ("midway option given but no template image defined");

    INFO ("image will not be regridded");
    Eigen::MatrixXd rotation = linear_transform.linear();
    Eigen::MatrixXd temp = rotation.transpose() * rotation;
    if (!temp.isIdentity (0.001))
      WARN("the input linear transform is not orthonormal and therefore applying this without the -template"
           "option will mean the output header transform will also be not orthonormal");

    add_line (output_header.keyval()["comments"], std::string ("transform modified"));
    if (replace)
      output_header.transform() = linear_transform;
    else
      output_header.transform() = linear_transform.inverse() * output_header.transform();
    auto output = Image<float>::create (argument[1], output_header).with_direct_io();
    copy_with_progress (input, output);

    if (fod_reorientation) {
      transform_type transform = linear_transform;
      if (replace)
        transform = linear_transform * output_header.transform().inverse();
      Registration::Transform::reorient ("reorienting", output, output, transform, directions_cartesian.transpose());
    }
  }
}