void GLWidget3D::drawScene(int drawMode) {
	///////////////////////////////////
	// GEN MODE
	if(G::global().getInt("3d_render_mode")==0){
		//vboRenderManager.renderStaticGeometry(QString("sky"));

		glDisable(GL_CULL_FACE);
		mainWin->urbanGeometry->render(vboRenderManager);
		glEnable(GL_CULL_FACE);
		
		vboRenderManager.vboTerrain.render(vboRenderManager);
		if(mainWin->controlWidget->ui.terrain_2DShader->isChecked()==false)
			vboRenderManager.vboWater.render(vboRenderManager);

		// draw the selected vertex and edge
		if (vertexSelected) {
			RendererHelper::renderPoint(vboRenderManager, "selected_vertex", selectedVertex->pt, QColor(0, 0, 255), selectedVertex->pt3D.z() + 2.0f);
		}
		if (edgeSelected) {
			Polyline3D polyline(selectedEdge->polyline3D);
			for (int i = 0; i < polyline.size(); ++i) polyline[i].setZ(polyline[i].z() + 10.0f);
			RendererHelper::renderPolyline(vboRenderManager, "selected_edge_lines", "selected_edge_points", polyline, QColor(0, 0, 255));
		}

	}
	///////////////////////////////////
	// LC MODE
	if(G::global().getInt("3d_render_mode")==1||G::global().getInt("3d_render_mode")==2){//LC HATCH

		// NORMAL
		if(drawMode==0){
			glUniform1i(glGetUniformLocation(vboRenderManager.program,"shadowState"), 0);//SHADOW: Disable

			// RENDER SKY WATER

			vboRenderManager.renderStaticGeometry(QString("sky"));
			vboRenderManager.vboWater.render(vboRenderManager);

			

			if(shadowEnabled)
				glUniform1i(glGetUniformLocation(vboRenderManager.program,"shadowState"), 1);//SHADOW: Render Normal with Shadows

			vboRenderManager.vboTerrain.render(vboRenderManager);

			vboRenderManager.renderStaticGeometry(QString("3d_sidewalk"));
			vboRenderManager.renderStaticGeometry(QString("3d_roads"));

			
			vboRenderManager.renderStaticGeometry(QString("3d_roads_inter"));//
			vboRenderManager.renderStaticGeometry(QString("3d_roads_interCom"));//
			

			vboRenderManager.renderStaticGeometry(QString("3d_building"));
			vboRenderManager.renderStaticGeometry(QString("3d_building_fac"));

			if(mainWin->controlWidget->ui.render_3DtreesCheckBox->isChecked()){
				vboRenderManager.renderStaticGeometry(QString("3d_trees"));//hatch
				vboRenderManager.renderAllStreetElementName("tree");//LC
				vboRenderManager.renderAllStreetElementName("streetLamp");//LC
			}

		}
		// SHADOWS
		if(drawMode==1){
			glUniform1i(glGetUniformLocation(vboRenderManager.program,"shadowState"), 2);// SHADOW: From light

			vboRenderManager.vboTerrain.render(vboRenderManager);

			//vboRenderManager.renderStaticGeometry(QString("3d_sidewalk"));
			//vboRenderManager.renderStaticGeometry(QString("3d_roads"));
			vboRenderManager.renderStaticGeometry(QString("3d_building"));
			vboRenderManager.renderStaticGeometry(QString("3d_building_fac"));

			if(mainWin->controlWidget->ui.render_3DtreesCheckBox->isChecked()){
				vboRenderManager.renderStaticGeometry(QString("3d_trees"));//hatch
				vboRenderManager.renderAllStreetElementName("tree");//LC
				vboRenderManager.renderAllStreetElementName("streetLamp");//LC
			}
		}
	}

	///////////////////////////////////
	// 2D WITH BLOCKS MODE
	if(G::global().getInt("3d_render_mode")==3){

		glDisable(GL_CULL_FACE);
		mainWin->urbanGeometry->render(vboRenderManager);
		glEnable(GL_CULL_FACE);
		
		vboRenderManager.vboTerrain.render(vboRenderManager);

		vboRenderManager.renderStaticGeometry(QString("2d_blocks"));
		vboRenderManager.renderStaticGeometry(QString("2d_parks"));

		// draw the selected vertex and edge
		if (vertexSelected) {
			RendererHelper::renderPoint(vboRenderManager, "selected_vertex", selectedVertex->pt, QColor(0, 0, 255), selectedVertex->pt3D.z() + 2.0f);
		}
		if (edgeSelected) {
			Polyline3D polyline(selectedEdge->polyline3D);
			for (int i = 0; i < polyline.size(); ++i) polyline[i].setZ(polyline[i].z() + 10.0f);
			RendererHelper::renderPolyline(vboRenderManager, "selected_edge_lines", "selected_edge_points", polyline, QColor(0, 0, 255));
		}

	}
}