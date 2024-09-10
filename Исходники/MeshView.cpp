void GLUTMotion(int x, int y)
{
  // Invert y coordinate
  y = GLUTwindow_height - y;
  
  // Compute mouse movement
  int dx = x - GLUTmouse[0];
  int dy = y - GLUTmouse[1];
  
  // Process mouse motion event
  if ((dx != 0) || (dy != 0)) {
    R3Point mesh_center = mesh->Center();
    if ((GLUTbutton[0] && (GLUTmodifiers & GLUT_ACTIVE_SHIFT)) || GLUTbutton[1]) {
      // Scale world 
      double factor = (double) dx / (double) GLUTwindow_width;
      factor += (double) dy / (double) GLUTwindow_height;
      factor = exp(2.0 * factor);
      factor = (factor - 1.0) / factor;
      R3Vector translation = (mesh_center - camera_eye) * factor;
      camera_eye += translation;
      glutPostRedisplay();
    }
    else if (GLUTbutton[0] && (GLUTmodifiers & GLUT_ACTIVE_CTRL)) {
      // Translate world
      double length = R3Distance(mesh_center, camera_eye) * tan(camera_yfov);
      double vx = length * (double) dx / (double) GLUTwindow_width;
      double vy = length * (double) dy / (double) GLUTwindow_height;
      R3Vector camera_right = camera_up % camera_towards;
      R3Vector translation = -((camera_right * vx) + (camera_up * vy));
      camera_eye += translation;
      glutPostRedisplay();
    }
    else if (GLUTbutton[0]) {
      // Rotate world
      double vx = (double) dx / (double) GLUTwindow_width;
      double vy = (double) dy / (double) GLUTwindow_height;
      double theta = 4.0 * (fabs(vx) + fabs(vy));
      R3Vector camera_right = camera_up % camera_towards;
      R3Vector vector = (camera_right * vx) + (camera_up * vy);
      R3Vector rotation_axis = vector % camera_towards;
      rotation_axis.Normalize();
      camera_eye.Rotate(R3Line(mesh_center, rotation_axis), theta);
      camera_towards.Rotate(rotation_axis, theta);
      camera_up.Rotate(rotation_axis, theta);
      camera_right = camera_up % camera_towards;
      camera_up = camera_towards % camera_right;
      camera_towards.Normalize();
      camera_up.Normalize();
      glutPostRedisplay();
    }
  }

  // Remember mouse position 
  GLUTmouse[0] = x;
  GLUTmouse[1] = y;
}