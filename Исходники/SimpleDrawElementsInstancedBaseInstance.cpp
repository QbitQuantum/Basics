	void initializeGL() {
		gl::createVertexArrays(1, &vao);
		gl::createBuffers(1, &positionBuffer);
		gl::createBuffers(1, &colorBuffer);
		gl::createBuffers(1, &indexBuffer);
		vao.bindElementBuffer(indexBuffer);
		constexpr static gl::Float colors[] = {
			1,0,0,1,
			0,1,0,1,
			0,0,1,1,
			1,1,0,1,
			1,0,0,1,
			0,1,0,1,
			0,0,1,1,
			1,1,0,1,
			1,0,0,1,
			0,1,0,1,
			0,0,1,1,
			1,1,0,1,
			1,0,0,1,
			0,1,0,1,
			0,0,1,1,
			1,1,0,1,
		};
#define POS0 -0.5f, 0.5f,0,1,
#define POS1 -0.5f,-0.5f,0,1,
#define POS2  0.5f,-0.5f,0,1,
#define POS3  0.5f, 0.5f,0,1,
		constexpr static gl::Float positions[] = {
			POS0
			POS1
			POS2
			POS3
			POS1
			POS2
			POS3
			POS0
			POS2
			POS3
			POS0
			POS1
			POS3
			POS0
			POS1
			POS2
		};
		gl::bufferData(positionBuffer, sizeof(positions), positions);
		gl::bufferData(colorBuffer, sizeof(colors), colors);
		constexpr static gl::UnsignedInteger index[] = { 0 };
		gl::bufferData(indexBuffer, sizeof(index), index);
		vao.bindBuffer(0, positionBuffer);
		vao.bindBuffer(1, colorBuffer);
		vao.bindDivisor(0, 1);
		vao.bindDivisor(1, 1);
		constexpr static char vs[] = R"(#version 450
layout(location=0) in vec4 iposition;
layout(location=1) in vec4 icolor;
out vec4 color;
void main(){
gl_Position = iposition;
gl_PointSize = 36+15*gl_InstanceID;
color = icolor;
}
)";
		constexpr static char fs[] = R"(#version 450
in vec4 color;
out vec4 fcolor;
void main(){
fcolor = vec4( gl_PointCoord.xy  ,color.x, 1);
}
)";
		program = gl::VFProgramLoadSources(vs, fs);
		{
			typedef void(QTimer::*TT)();
			timer.connect(&timer,TT(&QTimer::timeout),
				[this]() {
				++baseIndex;
				if (baseIndex > 3) { baseIndex = 0; }
				super->updateGL();
			}
				);
			timer.start(666);
		}
	}