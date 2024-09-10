        void initializeGL(){
    {
		rotate_value = 0;
		constexpr static char vs[] = R"(#version 450
    layout(location=0) in vec4 iposition;
    layout(location=1) in vec4 inormal_  ;
    layout(location=1) uniform mat4 MVP ;
    layout(location=3) uniform mat4 NMVP ;
    layout(location=2) uniform vec4 light_pos = vec4(1,1,-1,1);
    out vec4 color ;
    void main(){
    gl_Position = MVP * iposition  ;
    vec4 inormal = NMVP * inormal_ ;
    vec3 light = light_pos.xyz - gl_Position.xyz ;
    light = normalize( light );
    float v = smoothstep(0,1, dot(light ,
    normalize( inormal.xyz ) ));
    v*=0.85;
    v+=0.05;
    color = vec4(v,v,v,1) ;
    }
    )";
        constexpr static char fs[] = R"(#version 450
    out vec4 fcolor ;
    in vec4 color ;
    void main(){
    fcolor = color ;
    }
    )";
        program = gl::VFProgramLoadSources(vs,fs);
    }
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
            glClearDepth(1);
            glClearColor(0,0,0,0);
    #ifdef _DEBUG_OPENGL_QT_
    QGLDebugTool::setSimpleCallbackFunction();
    QGLDebugTool::test();
    #endif
    gl::createBuffers(1, &pointsNormalBuffer);
    gl::createBuffers(1,&indexBuffer);

    {
        gl::VertexNormalElementCallBack callBack ;

        callBack.loadFile(
            ":/model.zip"
            );

        gl::bufferData(indexBuffer,
    callBack.triangles.size()*sizeof(callBack.triangles[0]),
    &callBack.triangles[0]
    );

        gl::bufferData(pointsNormalBuffer,
    callBack.pointNormal.size()*sizeof(callBack.pointNormal[0]),
    &callBack.pointNormal[0]);

		const double scale__ = (std::max)({
			double(callBack.xMax) - callBack.xMin ,
			double(callBack.yMax) - callBack.yMin,
			double(callBack.zMax) - callBack.zMin
		});

		modelScaleBase = glm::scale(glm::vec3(
            float( 1.50 / scale__),
            float( 1.50 / scale__),
            float(-1.50 / scale__)
            ));

		modelScale = modelScaleBase;
		normalMatrix = glm::mat4( 
			1,0, 0,0,
			0,1, 0,0,
			0,0,-1,0,
			0,0, 0,1
			);
        indexCount = 3 * callBack.triangles.size() ;
    }

    gl::createVertexArrays(1,&vao);
    vao.bindBuffer(0, pointsNormalBuffer, 0,
        sizeof(gl::Float) * 6, 0,
        gl::NamedVertexArrayObject::Size::Three);
    vao.bindBuffer(1, pointsNormalBuffer, 0,
        sizeof(gl::Float) * 6, sizeof(gl::Float) * 3,
        gl::NamedVertexArrayObject::Size::Three);
    vao.bindElementBuffer(indexBuffer);
	{
		typedef void(QTimer::*TT)();
		timer.connect( &timer,TT(&QTimer::timeout),
			[this]() {
			rotate();
			super->updateGL();
		}
			);
	}
	timer.start(666);
     }