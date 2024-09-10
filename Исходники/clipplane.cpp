bool
ClipPlanes::viewportKeypressEvent(int i, QKeyEvent *event)
{
  if (i >= 0 && i < m_clips.count())
    {
      if (event->key() == Qt::Key_Delete)
	{
	  QMessageBox::information(0, "", "Switching off the viewport");
	  m_clips[i]->setViewport(QVector4D(-1,-1,-1,-1));
	  return true;
	}

      bool ok = m_clips[i]->keyPressEvent(event);
      if (ok)
	{
	  if (m_clips[i]->mopClip())
	    {
	      Vec pos = m_clips[i]->position();
	      Vec normal = m_clips[i]->m_tang;
	      Vec voxelScaling = Global::voxelScaling();
	      normal = VECPRODUCT(normal, voxelScaling);
	      normal.normalize();
	      pos = VECPRODUCT(pos, voxelScaling);
	      emit mopClip(pos, normal);
	    }
	  if (m_clips[i]->saveSliceImage())
	    emit saveSliceImage(i, m_clips[i]->resliceSubsample());
	  else if (m_clips[i]->resliceVolume())
	    {
	      int subsample = m_clips[i]->resliceSubsample();
	      int tagvalue = m_clips[i]->resliceTag();
	      emit extractClip(i, subsample, tagvalue);
	    }
	  else if (m_clips[i]->reorientCamera())
	    emit reorientCameraUsingClipPlane(i);
	}
      return ok;
    }

  return false;
}