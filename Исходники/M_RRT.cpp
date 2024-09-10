/**
 * @function workspaceDist
 * @brief
 */
Eigen::VectorXd M_RRT::workspaceDist( Eigen::VectorXd node, Eigen::VectorXd ws_target )
{
  Eigen::Transform<double, 3, Eigen::Affine> T;
  Eigen::VectorXd diff;

  // Calculate the EE position
  robinaLeftArm_fk( node, TWBase, Tee, T );
  Eigen::VectorXd ws_node = T.translation();

  // Calculate the workspace distance to goal
  diff = ( ws_target - ws_node );

  return diff;
}