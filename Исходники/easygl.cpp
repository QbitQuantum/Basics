void easygl::init()
{
    target = vec3(0, 1, 0);
    up = vec3(0, 1, 0);
    orientation = quat();

    direction = vec3(0, 0, -1);
    right = cross(up, direction);
    up = cross(direction, right);
    position = vec3(5.0f, 5.0f, 5.0f);
    
	fieldOfView = 60.0f;
	near = 0.1f, far = 1000.0f;
	aspectRatio = 1.0;
    dragl = false;
    dragr = false;

    //sphere.load("sphere.stl", vec4(1.0f, 0.0f, 1.0f, 1.0f));
    for(layer &l : d.layers){
        l.findcontours();
        l.offset(1);
        l.show();
    }
}