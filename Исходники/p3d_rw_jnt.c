/*! \brief Create a structure to store the parameters of the joints.
 *
 * \param type: the joint type.
 *
 * \return the joint data.
 */
p3d_read_jnt_data * p3d_create_read_jnt_data(p3d_type_joint type)
{
  p3d_read_jnt_data * data;
  int i;

  data = MY_ALLOC(p3d_read_jnt_data, 1);
  if (data == NULL) {
    PrintError(("Not enough memory !!!\n"));
    return NULL;
  }

  data->type = type;
  p3d_jnt_get_nb_param(type, &(data->nb_dof), &(data->nb_param));
  data->v         = MY_ALLOC(double, data->nb_dof);
  data->v_pos0    = MY_ALLOC(double, data->nb_dof);
  data->vmin      = MY_ALLOC(double, data->nb_dof);
  data->vmax      = MY_ALLOC(double, data->nb_dof);
  data->vmin_rand = MY_ALLOC(double, data->nb_dof);
  data->vmax_rand = MY_ALLOC(double, data->nb_dof);
  data->velocity_max = MY_ALLOC(double, data->nb_dof);
  data->acceleration_max = MY_ALLOC(double, data->nb_dof);
  data->jerk_max = MY_ALLOC(double, data->nb_dof);
  
  data->torque_max = MY_ALLOC(double, data->nb_dof);
  data->is_user   = MY_ALLOC(int,    data->nb_dof);
  data->is_active_for_planner   = MY_ALLOC(int,    data->nb_dof);
 
  if ((data->nb_dof>0) && 
      ((data->v == NULL) || (data->v_pos0 == NULL) ||
       (data->vmin == NULL) || (data->vmax == NULL) || 
       (data->vmin_rand == NULL) || (data->vmax_rand == NULL) ||
       (data->is_user == NULL) || (data->is_active_for_planner == NULL) ||
           ( data->velocity_max == NULL) || (data->acceleration_max == NULL) || ( data->jerk_max == NULL) )) {
    PrintError(("Not enough memory !!!\n"));
    return NULL;
  }
  data->flag_v            = FALSE;
  data->flag_v_pos0       = FALSE;
  data->flag_vmin         = FALSE;
  data->flag_vmax         = FALSE;
  data->flag_velocity_max = FALSE;
  data->flag_acceleration_max = FALSE;
  data->flag_jerk_max = FALSE;
  data->flag_torque_max   = FALSE;
  data->flag_vmin_rand    = FALSE;
  data->flag_vmax_rand    = FALSE;
  data->flag_is_user      = FALSE;
  data->flag_is_active_for_planner   = FALSE;
  for(i=0; i<data->nb_dof; i++)
    { data->v[i] = 0.0; }

  data->param      = MY_ALLOC(double, data->nb_param);
  if ((data->nb_param>0) && (data->param == NULL)) {
    PrintError(("Not enough memory !!!\n"));
    return NULL;
  }
  data->flag_param = FALSE;
  
  data->flag_pos = FALSE;
  data->flag_relative_pos = FALSE;

  data->prev_jnt = 0;
  data->flag_prev_jnt = FALSE;

  data->flag_name = FALSE;

  data->nb_links = 0;
  data->link_array = NULL;

  return data;
}