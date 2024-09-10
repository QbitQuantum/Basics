fiducial_detector_error_t fiducial_detector_project_fiducial(fiducial_detector_t* self, fiducial_pose_t fd_pose)
{
 
  
  if(!self->camera_models_set)
  {
    fprintf(stderr,"camera models not set\n");
    return FIDUCIAL_DETECTOR_ERR;
  }

  // reset projection
  self->fiducial_projected = 0;

  // Check if fiducial is visible
  double T[4][4];
  fiducial_pose_to_transform(fd_pose, T);
  fiducial_vec_t camera_to_fiducial = fiducial_vec_unit(fd_pose.pos);
  fiducial_vec_t fiducial_normal = {T[0][2], T[1][2], T[2][2]};

  double angle = 180 * acos( fiducial_vec_dot(camera_to_fiducial,fiducial_normal) / ( fiducial_vec_mag(fiducial_normal) * fiducial_vec_mag(camera_to_fiducial) ) ) / M_PI;

  double min_viewing_angle = self->params.min_viewing_angle;
  if( (angle > (270 + min_viewing_angle) ) || (angle < (90 + min_viewing_angle)) )
  {
    return FIDUCIAL_DETECTOR_ERR;
  }

  int in_bounds;
  int err;
  double col;
  double row;
  int cols, rows;
  double image_point[2];
  double world_point[3];
  fiducial_vec_t world_template_pt;

  //-----------------------------------------------------------------------------
  //  inner circle
  //-----------------------------------------------------------------------------
  // get image dimensions
  cols = self->camera.cols;
  rows = self->camera.rows;


  // Center point
  fiducial_vec_t center_pt = {0,0,0};
  world_template_pt = fiducial_vec_transform(fd_pose, center_pt);
  world_point[0] = world_template_pt.x;
  world_point[1] = world_template_pt.y;
  world_point[2] = world_template_pt.z;

  // reproject the point into the image frame
  err = world_point_reproject(&self->camera, &world_point[0], &image_point[0]);
  col = image_point[0];
  row = image_point[1];

  if( ((int)col < 0) || ((int)col > (cols)) ||
      ((int)row < 0) || ((int)row > (rows)) || (err != 0) )
    in_bounds = false;
  else
    in_bounds = true;

  if(in_bounds)
  {
    self->proj_center_pt.x = (double) col;
    self->proj_center_pt.y = (double) row;
  }

  // Remaining points
  int num_proj_inner_circle_pts = 0;
  int i = 0;

  for(i = 0; i < self->num_inner_circle_pts; i++)
  {
    world_template_pt = fiducial_vec_transform(fd_pose, self->inner_circle_pts[i]);
    world_point[0] = world_template_pt.x;
    world_point[1] = world_template_pt.y;
    world_point[2] = world_template_pt.z;

    err = world_point_reproject(&self->camera, &world_point[0], &image_point[0]);
    col = image_point[0];
    row = image_point[1];

    if( ((int)col < 0) || ((int)col > (cols)) ||
        ((int)row < 0) || ((int)row > (rows)) || (err != 0) )
      in_bounds = false;
    else
      in_bounds = true;

    if(in_bounds)
    {
      self->proj_inner_circle_pts[num_proj_inner_circle_pts].x = (double) col;
      self->proj_inner_circle_pts[num_proj_inner_circle_pts].y = (double) row;
      num_proj_inner_circle_pts = num_proj_inner_circle_pts + 1;
              
    }
  }

  if(num_proj_inner_circle_pts != self->num_inner_circle_pts)
  {
    return FIDUCIAL_DETECTOR_ERR;
  }
  else
  {
    self->num_proj_inner_circle_pts = self->num_inner_circle_pts;
  }


  //-----------------------------------------------------------------------------
  //  outer circle
  //-----------------------------------------------------------------------------
  // get image dimensions
  cols = self->camera.cols;
  rows = self->camera.rows;

  // Remaining points
  int num_proj_outer_circle_pts = 0;

  for(i = 0; i < self->num_outer_circle_pts; i++)
  {
    world_template_pt = fiducial_vec_transform(fd_pose, self->outer_circle_pts[i]);
    world_point[0] = world_template_pt.x;
    world_point[1] = world_template_pt.y;
    world_point[2] = world_template_pt.z;

    err = world_point_reproject(&self->camera, &world_point[0], &image_point[0]);
    col = image_point[0];
    row = image_point[1];

    if( ((int)col < 0) || ((int)col > (cols)) ||
        ((int)row < 0) || ((int)row > (rows)) || (err != 0) )
      in_bounds = false;
    else
      in_bounds = true;

    if(in_bounds)
    {
      self->proj_outer_circle_pts[num_proj_outer_circle_pts].x = (double) col;
      self->proj_outer_circle_pts[num_proj_outer_circle_pts].y = (double) row;
      num_proj_outer_circle_pts = num_proj_outer_circle_pts + 1;
    }
  }

  if(num_proj_outer_circle_pts != self->num_outer_circle_pts)
  {
    return FIDUCIAL_DETECTOR_ERR;
  }
  else
  {
    self->num_proj_outer_circle_pts = self->num_outer_circle_pts;
  }


  //-----------------------------------------------------------------------------
  //  edges
  //-----------------------------------------------------------------------------
  // get image dimensions
  cols = self->camera.cols;
  rows = self->camera.rows;

  // Remaining points
  int num_proj_edge_pts = 0;

  for(i = 0; i < self->num_edge_pts; i++)
  {
    world_template_pt = fiducial_vec_transform(fd_pose, self->edge_pts[i]);
    world_point[0] = world_template_pt.x;
    world_point[1] = world_template_pt.y;
    world_point[2] = world_template_pt.z;

    err = world_point_reproject(&self->camera, &world_point[0], &image_point[0]);
    col = image_point[0];
    row = image_point[1];

    if( ((int)col < 0) || ((int)col > (cols)) ||
        ((int)row < 0) || ((int)row > (rows)) || (err != 0) )
      in_bounds = false;
    else
      in_bounds = true;

    if(in_bounds)
    {
      self->proj_edge_pts[num_proj_edge_pts].x = (double) col;
      self->proj_edge_pts[num_proj_edge_pts].y = (double) row;
      num_proj_edge_pts = num_proj_edge_pts + 1;

    }
  }

  if(num_proj_edge_pts != self->num_edge_pts)
  {
    return FIDUCIAL_DETECTOR_ERR;
  }
  else
  {
    self->num_proj_edge_pts = self->num_edge_pts;
  }


  self->fiducial_projected = 1;

  return FIDUCIAL_DETECTOR_OK;
}