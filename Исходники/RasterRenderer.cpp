OGREnvelope wxGISRasterRGBRenderer::TransformEnvelope(OGREnvelope* pEnvelope, OGRSpatialReference* pSrsSpatialReference, OGRSpatialReference* pDstSpatialReference)
{
	//get new envelope - it may rotate
	OGRCoordinateTransformation *poCT = OGRCreateCoordinateTransformation( pSrsSpatialReference, pDstSpatialReference);
	double pointsx[4];
	double pointsy[4];
	pointsx[0] = pEnvelope->MaxX;
	pointsy[0] = pEnvelope->MaxY;
	pointsx[1] = pEnvelope->MinX;
	pointsy[1] = pEnvelope->MinY;
	pointsx[2] = pEnvelope->MaxX;
	pointsy[2] = pEnvelope->MinY;
	pointsx[3] = pEnvelope->MinX;
	pointsy[3] = pEnvelope->MaxY;
	//get real envelope
	poCT->Transform(4, pointsx, pointsy);
	OCTDestroyCoordinateTransformation(poCT);
	OGREnvelope out;
	out.MinX = MIN(pointsx[0], MIN(pointsx[1], MIN(pointsx[2], pointsx[3])));
	out.MaxX = MAX(pointsx[0], MAX(pointsx[1], MAX(pointsx[2], pointsx[3])));
	out.MinY = MIN(pointsy[0], MIN(pointsy[1], MIN(pointsy[2], pointsy[3])));
	out.MaxY = MAX(pointsy[0], MAX(pointsy[1], MAX(pointsy[2], pointsy[3])));
	return out;
}