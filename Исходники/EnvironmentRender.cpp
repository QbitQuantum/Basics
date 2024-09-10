void EnvironmentRender::reflection(vec3 pos, vec3 nor, f32 dis, gchandle tex)
{
  kgmCamera cam;

  vec3 cpos = gr->m_camera->mPos;
  vec3 cdir = gr->m_camera->mDir;
  f32  fov  = gr->m_camera->mFov;
  f32  asp  = gr->m_camera->mAspect;
  f32  zfar  = gr->m_camera->mFar;
  f32  zner  = gr->m_camera->mNear;

  cpos.z *= -1;
  cdir.z *= -1;

  cam.set(fov, asp, zner, zfar, cpos, cdir, vec3(0, 0, 1));

  kgmGraphics::Options o;

  o.width = 512;
  o.height = 512;

  o.clipping = true;
  o.light    = false;

  nor.normalize();

  plane plane(nor, pos);
  o.plane[0] = plane.x;
  o.plane[1] = plane.y;
  o.plane[2] = plane.z;
  o.plane[3] = plane.w;

  o.discard = m_discard;

  gc->gcTexTarget(m_target, tex, gctype_tex2d);
  gc->gcSetTarget(m_target);
  gr->render(cam, o);
  gc->gcSetTarget(null);
}