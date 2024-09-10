void Iwa_TiledParticlesFx::doCompute(TTile &tile, double frame, const TRenderSettings &ri)
{
	std::vector<int> lastframe;
	std::vector<TLevelP> partLevel;

	TPointD p_offset;
	TDimension p_size(0, 0);

	/*- 参照画像ポートの取得 -*/
	std::vector<TRasterFxPort *> part_ports;   /*- テクスチャ素材画像のポート -*/
	std::map<int, TRasterFxPort *> ctrl_ports; /*- コントロール画像のポート番号／ポート -*/
	int portsCount = this->getInputPortCount();

	for (int i = 0; i < portsCount; ++i) {
		std::string tmpName = this->getInputPortName(i);
		QString portName = QString::fromStdString(tmpName);

		if (portName.startsWith("T")) {
			TRasterFxPort *tmpPart = (TRasterFxPort *)this->getInputPort(tmpName);
			if (tmpPart->isConnected())
				part_ports.push_back((TRasterFxPort *)this->getInputPort(tmpName));
		} else {
			portName.replace(QString("Control"), QString(""));
			TRasterFxPort *tmpCtrl = (TRasterFxPort *)this->getInputPort(tmpName);
			if (tmpCtrl->isConnected())
				ctrl_ports[portName.toInt()] = (TRasterFxPort *)this->getInputPort(tmpName);
		}
	}

	/*- テクスチャ素材のバウンディングボックスを足し合わせる ←この工程、いらないかも？-*/
	if (!part_ports.empty()) {
		TRectD outTileBBox(tile.m_pos, TDimensionD(tile.getRaster()->getLx(), tile.getRaster()->getLy()));
		TRectD bbox;

		for (unsigned int i = 0; i < (int)part_ports.size(); ++i) {
			const TFxTimeRegion &tr = (*part_ports[i])->getTimeRegion();

			lastframe.push_back(tr.getLastFrame() + 1);
			partLevel.push_back(new TLevel());
			partLevel[i]->setName((*part_ports[i])->getAlias(0, ri));

			// The particles offset must be calculated without considering the affine's translational
			// component
			TRenderSettings riZero(ri);
			riZero.m_affine.a13 = riZero.m_affine.a23 = 0;

			// Calculate the bboxes union
			for (int t = 0; t <= tr.getLastFrame(); ++t) {
				TRectD inputBox;
				(*part_ports[i])->getBBox(t, inputBox, riZero);
				bbox += inputBox;
			}
		}

		if (bbox == TConsts::infiniteRectD)
			bbox *= outTileBBox;

		p_size.lx = (int)bbox.getLx() + 1;
		p_size.ly = (int)bbox.getLy() + 1;
		p_offset = TPointD(0.5 * (bbox.x0 + bbox.x1), 0.5 * (bbox.y0 + bbox.y1));
	} else {
		partLevel.push_back(new TLevel());
		partLevel[0]->setName("particles");
		TDimension vecsize(10, 10);
		TOfflineGL *offlineGlContext = new TOfflineGL(vecsize);
		offlineGlContext->clear(TPixel32(0, 0, 0, 0));

		TStroke *stroke;
		stroke = makeEllipticStroke(0.07, TPointD((vecsize.lx - 1) * .5, (vecsize.ly - 1) * .5), 2.0, 2.0);
		TVectorImageP vectmp = new TVectorImage();

		TPalette *plt = new TPalette();
		vectmp->setPalette(plt);
		vectmp->addStroke(stroke);
		TVectorRenderData rd(AffI, TRect(vecsize), plt, 0, true, true);
		offlineGlContext->makeCurrent();
		offlineGlContext->draw(vectmp, rd);

		partLevel[0]->setFrame(0, TRasterImageP(offlineGlContext->getRaster()->clone()));
		p_size.lx = vecsize.lx + 1;
		p_size.ly = vecsize.ly + 1;
		lastframe.push_back(1);

		delete offlineGlContext;
	}

	Iwa_Particles_Engine myEngine(this, frame);

	// Retrieving the dpi multiplier from the accumulated affine (which is isotropic). That is,
	// the affine will be applied *before* this effect - and we'll multiply geometrical parameters
	// by this dpi mult. in order to compensate.
	float dpi = sqrt(fabs(ri.m_affine.det())) * 100;

	TTile tileIn;
	if (TRaster32P raster32 = tile.getRaster()) {
		TFlash *flash = 0;
		myEngine.render_particles(flash, &tile, part_ports, ri, p_size, p_offset, ctrl_ports, partLevel,
								  1, (int)frame, 1, 0, 0, 0, 0, lastframe, getIdentifier());
	} else if (TRaster64P raster64 = tile.getRaster()) {
		TFlash *flash = 0;
		myEngine.render_particles(flash, &tile, part_ports, ri, p_size, p_offset, ctrl_ports, partLevel,
								  1, (int)frame, 1, 0, 0, 0, 0, lastframe, getIdentifier());
	} else
		throw TException("ParticlesFx: unsupported Pixel Type");
}