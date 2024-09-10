void EdLevelManipScale::draw (EdLevelToolWindow *parent, const std::shared_ptr<CameraObject> &camera, DTfloat scale)
{
    DrawBatcher b;
    
    Matrix4 axis;

    Matrix4 transform = getManipulatorTransform();
	Matrix3 orientation = transform.orientation();
	Vector3 translation = transform.translation();
    
    transform = Matrix4(orientation, translation, scale);
   
    ::glPushName(0);

    // Center
    ::glLoadName(CENTER);
    axis = Matrix4(     Matrix3(    1.0F, 0.0F, 0.0F,
                                    0.0F, 1.0F, 0.0F,
                                    0.0F, 0.0F, 1.0F), 
                        Vector3(0.0F,0.0F,0.0F), 
                        1.0F);
    
    DrawUtils::draw_cube (  b,
                            camera,
                            _tool_material,
                            _shader,
                            transform * axis,
                            Color4b::white,
                            0.05F);
    b.flush();


    // X Axis
    ::glLoadName(PLUS_X);
    axis = Matrix4(     Matrix3(    0.0F, 1.0F, 0.0F,
                                    1.0F, 0.0F, 0.0F,
                                    0.0F, 0.0F, -1.0F), 
                        Vector3(1.0F,0.0F,0.0F), 
                        1.0F);

    DrawUtils::draw_cube (  b,
                            camera,
                            _tool_material,
                            _shader,
                            transform * axis,
                            Color4b::red,
                            0.05F);
    b.flush();

    // Y Axis
    ::glLoadName(PLUS_Y);
    axis = Matrix4(     Matrix3(    1.0F, 0.0F, 0.0F,
                                    0.0F, 1.0F, 0.0F,
                                    0.0F, 0.0F, 1.0F), 
                        Vector3(0.0F,1.0F,0.0F), 
                        1.0F);

    DrawUtils::draw_cube (  b,
                            camera,
                            _tool_material,
                            _shader,
                            transform * axis,
                            Color4b::green,
                            0.05F);
    b.flush();

    // Z Axis
    ::glLoadName(PLUS_Z);
    axis = Matrix4(     Matrix3(    1.0F, 0.0F, 0.0F,
                                    0.0F, 0.0F, -1.0F,
                                    0.0F, 1.0F, 0.0F), 
                        Vector3(0.0F,0.0F,1.0F), 
                        1.0F);

    DrawUtils::draw_cube (  b,
                            camera,
                            _tool_material,
                            _shader,
                            transform * axis,
                            Color4b::blue,
                            0.05F);
    b.flush();
    
    ::glPopName();
    
    // Draw Lines
    b.batch_begin(camera, _tool_material, _shader, transform, DT3GL_PRIM_LINES, DrawBatcher::FMT_V);

    b.add().v(0.0F,0.0F,0.0F);
    b.add().v(1.0F,0.0F,0.0F);
    b.add().v(0.0F,0.0F,0.0F);
    b.add().v(0.0F,1.0F,0.0F);
    b.add().v(0.0F,0.0F,0.0F);
    b.add().v(0.0F,0.0F,1.0F);

    b.batch_end();
}