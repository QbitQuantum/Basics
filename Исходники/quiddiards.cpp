void Quiddiards::keyPressEvent(QKeyEvent *event){
	switch (event->key()) {
	case Qt::Key_F2:
		actStart();
		break;
	case Qt::Key_P:
		actPause();
		break;
	case Qt::Key_Escape:
	case Qt::Key_Q:
		close();
		break;
	case Qt::Key_Space:
	case Qt::Key_Enter:
	case Qt::Key_Return:
		break;
	case Qt::Key_W:{
		/* forward cueball */
		QVector3D n = -eye;
		n.setZ(0);
		n.normalize();
		n += cueball.getVelocity();
		if (n.length() > cueball.getSpeed()){
			n = cueball.getSpeed()*n.normalized();
		}
		cueball.setVelocity(n);
		break;
	}
	case Qt::Key_A:
		phi += 10;
		break;
	case Qt::Key_S:{
		QVector3D n = eye;
		n.setZ(0);
		n.normalize();
		n += cueball.getVelocity();
		if (n.length() > cueball.getSpeed()){
			n = cueball.getSpeed()*n.normalized();
		}
		cueball.setVelocity(n);
		break;
	}
	case Qt::Key_D:
		phi -= 10;
		break;
	case Qt::Key_Tab:
		//camera = CAMERA((camera + 1) % 2);
		break;
	default:
		return;
	}
	update();
}