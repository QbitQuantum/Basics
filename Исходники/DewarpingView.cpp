void
DewarpingView::onPaint(QPainter& painter, InteractionState const& interaction)
{
	painter.setRenderHint(QPainter::Antialiasing);

	painter.setPen(Qt::NoPen);
	painter.setBrush(QColor(0xff, 0xff, 0xff, 150)); // Translucent white.
	painter.drawPolygon(virtMarginArea(0)); // Left margin.
	painter.drawPolygon(virtMarginArea(1)); // Right margin.

	painter.setWorldTransform(imageToVirtual() * painter.worldTransform());
	painter.setBrush(Qt::NoBrush);

	QPen grid_pen;
	grid_pen.setColor(Qt::blue);
	grid_pen.setCosmetic(true);
	grid_pen.setWidthF(1.2);

	painter.setPen(grid_pen);
	painter.setBrush(Qt::NoBrush);
	
	int const num_vert_grid_lines = 30;
	int const num_hor_grid_lines = 30;

	bool valid_model = m_distortionModel.isValid();

	if (valid_model) {
		try {
			std::vector<QVector<QPointF> > curves(num_hor_grid_lines);

			dewarping::CylindricalSurfaceDewarper dewarper(
				m_distortionModel.topCurve().polyline(),
				m_distortionModel.bottomCurve().polyline(), m_depthPerception.value()
			);
			dewarping::CylindricalSurfaceDewarper::State state;

			for (int j = 0; j < num_vert_grid_lines; ++j) {
				double const x = j / (num_vert_grid_lines - 1.0);
				dewarping::CylindricalSurfaceDewarper::Generatrix const gtx(dewarper.mapGeneratrix(x, state));
				QPointF const gtx_p0(gtx.imgLine.pointAt(gtx.pln2img(0)));
				QPointF const gtx_p1(gtx.imgLine.pointAt(gtx.pln2img(1)));
				painter.drawLine(gtx_p0, gtx_p1);
				for (int i = 0; i < num_hor_grid_lines; ++i) {
					double const y = i / (num_hor_grid_lines - 1.0);
					curves[i].push_back(gtx.imgLine.pointAt(gtx.pln2img(y)));
				}
			}

			BOOST_FOREACH(QVector<QPointF> const& curve, curves) {
				painter.drawPolyline(curve);
			}
		} catch (std::runtime_error const&) {
			// Still probably a bad model, even though DistortionModel::isValid() was true.
			valid_model = false;
		}
	} // valid_model

	if (!valid_model) {
		// Just draw the frame.
		dewarping::Curve const& top_curve = m_distortionModel.topCurve();
		dewarping::Curve const& bottom_curve = m_distortionModel.bottomCurve();
		painter.drawLine(top_curve.polyline().front(), bottom_curve.polyline().front());
		painter.drawLine(top_curve.polyline().back(), bottom_curve.polyline().back());
		painter.drawPolyline(QVector<QPointF>::fromStdVector(top_curve.polyline()));
		painter.drawPolyline(QVector<QPointF>::fromStdVector(bottom_curve.polyline()));
	}

	paintXSpline(painter, interaction, m_topSpline);
	paintXSpline(painter, interaction, m_bottomSpline);
}