QStringList cc2DLabel::getLabelContent(int precision)
{
	QStringList body;

	switch(m_points.size())
	{
	case 1: //point
		{
			//init title
			/*title = m_title;
			//automatically elide the title
			title = titleFontMetrics.elidedText(title,Qt::ElideRight,dx);
			//*/

			//coordinates
			ccGenericPointCloud* cloud = m_points[0].cloud;
			const unsigned& pointIndex = m_points[0].index;
			const CCVector3* P = cloud->getPointPersistentPtr(pointIndex);
			QString coordStr = QString("P#%0: (%1;%2;%3)").arg(pointIndex).arg(P->x,0,'f',precision).arg(P->y,0,'f',precision).arg(P->z,0,'f',precision);
			body << coordStr;

			//normal
			if (cloud->hasNormals())
			{
				const PointCoordinateType* N = cloud->getPointNormal(pointIndex);
				assert(N);
				QString normStr = QString("Normal: (%1;%2;%3)").arg(N[0],0,'f',precision).arg(N[1],0,'f',precision).arg(N[2],0,'f',precision);
				body << normStr;
			}
			//color
			if (cloud->hasColors())
			{
				const colorType* C = cloud->getPointColor(pointIndex);
				assert(C);
				QString colorStr = QString("Color: (%1;%2;%3)").arg(C[0]).arg(C[1]).arg(C[2]);
				body << colorStr;
			}
			//scalar field
			if (cloud->hasDisplayedScalarField())
			{
				ScalarType D = cloud->getPointScalarValue(pointIndex);
				QString sfStr = QString("Scalar: %1").arg(D,0,'f',precision);
				body << sfStr;
			}
		}
		break;
	case 2: //vector
		{
			//1st point
			ccGenericPointCloud* cloud1 = m_points[0].cloud;
			const unsigned& pointIndex1 = m_points[0].index;
			const CCVector3* P1 = cloud1->getPointPersistentPtr(pointIndex1);
			//2nd point
			ccGenericPointCloud* cloud2 = m_points[1].cloud;
			const unsigned& pointIndex2 = m_points[1].index;
			const CCVector3* P2 = cloud2->getPointPersistentPtr(pointIndex2);

			PointCoordinateType d = (*P1-*P2).norm();
			QString distStr = QString("Distance = %1").arg(d,0,'f',precision);
			body << distStr;

			QString coordStr1 = QString("P#%0: (%1;%2;%3)").arg(pointIndex1).arg(P1->x,0,'f',precision).arg(P1->y,0,'f',precision).arg(P1->z,0,'f',precision);
			body << coordStr1;
			QString coordStr2 = QString("P#%0: (%1;%2;%3)").arg(pointIndex2).arg(P2->x,0,'f',precision).arg(P2->y,0,'f',precision).arg(P2->z,0,'f',precision);
			body << coordStr2;
		}
		break;
	case 3: //triangle/plane
		{
			//1st point
			ccGenericPointCloud* cloud1 = m_points[0].cloud;
			const unsigned& pointIndex1 = m_points[0].index;
			const CCVector3* P1 = cloud1->getPointPersistentPtr(pointIndex1);
			//2nd point
			ccGenericPointCloud* cloud2 = m_points[1].cloud;
			const unsigned& pointIndex2 = m_points[1].index;
			const CCVector3* P2 = cloud2->getPointPersistentPtr(pointIndex2);
			//3rd point
			ccGenericPointCloud* cloud3 = m_points[2].cloud;
			const unsigned& pointIndex3 = m_points[2].index;
			const CCVector3* P3 = cloud3->getPointPersistentPtr(pointIndex3);

			//area
			CCVector3 P1P2 = *P2-*P1;
			CCVector3 P1P3 = *P3-*P1;
			CCVector3 N = P1P2.cross(P1P3); //N=ABxAC
			PointCoordinateType area = N.norm()*(PointCoordinateType)0.5;
			QString areaStr = QString("Area = %1").arg(area,0,'f',precision);
			body << areaStr;

			//coordinates
			QString coordStr1 = QString("A#%0: (%1;%2;%3)").arg(pointIndex1).arg(P1->x,0,'f',precision).arg(P1->y,0,'f',precision).arg(P1->z,0,'f',precision);
			body << coordStr1;
			QString coordStr2 = QString("B#%0: (%1;%2;%3)").arg(pointIndex2).arg(P2->x,0,'f',precision).arg(P2->y,0,'f',precision).arg(P2->z,0,'f',precision);
			body << coordStr2;
			QString coordStr3 = QString("C#%0: (%1;%2;%3)").arg(pointIndex3).arg(P3->x,0,'f',precision).arg(P3->y,0,'f',precision).arg(P3->z,0,'f',precision);
			body << coordStr3;

			//normal
			N.normalize();
			QString normStr = QString("Normal: (%1;%2;%3)").arg(N.x,0,'f',precision).arg(N.y,0,'f',precision).arg(N.z,0,'f',precision);
			body << normStr;

			//angle
			CCVector3 P2P3 = *P3-*P2;

            //negatives
            CCVector3 _P1P2 = -P1P2;
            CCVector3 _P1P3 = -P1P3;
            CCVector3 _P2P3 = -P2P3;

			double angleAtP1 = GetAngle_deg(P1P2,P1P3);
            double angleAtP2 = GetAngle_deg(P2P3,_P1P2);
            double angleAtP3 = GetAngle_deg(_P1P3,_P2P3); //should be equal to 180-a1-a2!
			QString angleStr = QString("Angles: A=%1 - B=%3 - C=%5 deg.").arg(angleAtP1,0,'f',precision).arg(angleAtP2,0,'f',precision).arg(angleAtP3,0,'f',precision);
			body << angleStr;
		}
		break;
	default:
		assert(false);
		break;
	}

	return body;
}