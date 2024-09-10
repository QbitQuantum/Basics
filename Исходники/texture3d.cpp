	void onDraw(Graphics& g){
		g.pointSize(renderMode+0.5);
		g.color(RGB(1));
		mesh.colors().reset();
		switch (renderMode) {
			case 0:
				// do it on the CPU:
				for (int k=0; k<N; k++) {
				for (int j=0; j<N; j++) {
				for (int i=0; i<N; i++) {
					Color color;
					data.read_interp(color.components, i,j,k);
					mesh.color(color);
				}}}
				g.draw(mesh);
				break;
			case 1:
				// use 3D texcoords:
				tex.bind();
				g.draw(mesh);
				tex.unbind();
				break;
			case 2:
				// use shader:
				shader.begin();
				tex.bind();
				g.draw(mesh);
				tex.unbind();
				shader.end();
				break;
			default:;
		}
	}