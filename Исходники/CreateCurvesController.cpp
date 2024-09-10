		MStatus CreateCurves::Curve::create(CreateCurves & instance) {
			MStatus status;

			MFnNurbsCurve curve;

			MObject curveObject = curve.create(points, knots, instance.m_degree, isLoop ? MFnNurbsCurve::kClosed : MFnNurbsCurve::kOpen, false, false, MObject::kNullObj, &status);

			if (!status) {
				status.perror("MFnNurbsCurve::create");
				return status;
			}

			MDagPath path;
			if (!(status = curve.getPath(path))) {
				status.perror("MFnNurbsCurve::getPath");
				return status;
			}

			instance.m_curves.append(path.transform());

			return MStatus::kSuccess;
		}