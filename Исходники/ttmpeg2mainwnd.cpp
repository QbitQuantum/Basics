void TTMpeg2MainWnd::analyzeMpegStream( )
{
  uint     max_print_frames = 2500;
  uint     i;
  long     num_frames = 0;
  QString  strHeaderType;
  QString  strHeaderOffset;
  QString  strPictureType;
  QString  strTempRef;
  QString  strDOrder;
  QString  strSOrder;
  QString  strTime;
  QString  strOut;
  Q3ListViewItem*      item;
  TTPicturesHeader*  current_picture;
  uint num_index;

  double             read_percent;

  // TODO: use QTime for timing purpose (have better resolution)
  time_t             seconds_start;
  time_t             seconds_end;

  num_frames = 0;

  // start time
  seconds_start = time( NULL );

  // open the mpeg2 stream
  if ( !file_name.isEmpty() )
  {
    // get the stream type and create according stream-object
    video_type   = new TTVideoType( file_name );

    // test
    audio_type = new TTAudioType( "rbb_test.mpa" );
    if ( audio_type->avStreamType() == TTAVTypes::mpeg_audio )
    {
      qDebug( "%sfound mpeg audio stream",cName );

      TTMPEGAudioStream* audio_stream = (TTMPEGAudioStream*)audio_type->createAudioStream();
      uint h_count = audio_stream->createHeaderList();
    }

    if ( video_type->avStreamType() == TTAVTypes::mpeg2_demuxed_video )
      video_stream = (TTMpeg2VideoStream*)video_type->createVideoStream();
    else
    {
      qDebug("%swrong video type",cName);
      return;
    }
 
    progress_bar = new TTProgressBar( this );
    video_stream->setProgressBar( progress_bar );
    progress_bar->show();
    qApp->processEvents();

    // create header- and index-list
    video_stream->createHeaderList();
    num_index = video_stream->createIndexList();

    qDebug("%snum index: %d",cName,num_index);
    // get pointer to the lists
    index_list  = video_stream->indexList();
    header_list = video_stream->headerList();

    // get pointer to stream
    mpeg2_stream = video_stream->streamBuffer();

    // sort frame index list to display (decoder) order
    index_list->sortDisplayOrder();
    
    // get end time
    seconds_end = time( NULL );

    setReadTime( diffTime( seconds_start, seconds_end ) );

    // print out statistic informations
    // get stream length and set label text
    setFileLength( mpeg2_stream->streamLength() );

    read_percent = (double)mpeg2_stream->readCount()/(double)mpeg2_stream->streamLength()*100.0;

    setReadOps( mpeg2_stream->readCount(), read_percent );
    setFillOps( mpeg2_stream->fillCount() );

    // print out the number of frames in stream
    num_frames = index_list->count();
    total_time = ttFramesToTime( num_frames, 25.0 );

    setNumFramesTotal( num_frames );
    setNumIFrames( index_list->numIFrames() );
    setNumPFrames( index_list->numPFrames() );
    setNumBFrames( index_list->numBFrames() );

    setNumSequence( header_list->numSequenceHeader() );
    setNumPicture( header_list->numPictureHeader() );
    setNumGOP( header_list->numGopHeader() );
    setNumSequenceEnd( header_list->numSequenceEndHeader() );

    if ( video_stream->indexList()->count() < max_print_frames )
      max_print_frames = video_stream->indexList()->count();

    // print out the frame list; print maximal 1000 rows (!)
    for( i = 0; i < max_print_frames; i++ )
    {
      item = new Q3ListViewItem( lvStreamInfo );

      strDOrder.sprintf("%08ld",index_list->displayOrder(i));
      strSOrder.sprintf("%08ld",index_list->streamOrder(i));
      strHeaderType.sprintf("0x%02x",header_list->at(index_list->headerListIndex(i))->headerType());
      strHeaderOffset.sprintf("%12ld",header_list->at(index_list->headerListIndex(i))->headerOffset());
      
      current_picture = (TTPicturesHeader*)header_list->at(index_list->headerListIndex(i));
      
      switch(index_list->videoIndexAt(i)->picture_coding_type)
      {
      case(1):
	strPictureType.sprintf("I-Frame");
	strTempRef.sprintf("%04d",current_picture->temporal_reference);
	break;
      case(2):
	strPictureType.sprintf("P-Frame");
	strTempRef.sprintf("%04d",current_picture->temporal_reference);
	break;
      case(3):
	strPictureType.sprintf("B-Frame");
	strTempRef.sprintf("%04d",current_picture->temporal_reference);
	break;
      }
      num_frames++;
      
      item->setText( 0, strHeaderType );
      item->setText( 1, strHeaderOffset );
      item->setText( 2, strPictureType );
      item->setText( 3, strTempRef );
      item->setText( 4, strSOrder );
      item->setText( 5, strDOrder );
      strTime.sprintf("%s,%d",ttFramesToTime(index_list->displayOrder(i),25.0).toString().ascii(),
		      ttFramesToTime(index_list->displayOrder(i),25.0).msec());
      item->setText( 6, strTime );
    }

    // delete the progress bar
    delete progress_bar;
    video_stream->setProgressBar( NULL );

    sbFrames->setMinValue( 0 );
    sbFrames->setMaxValue( index_list->count()-1 );
    slider_update = false;
    sbFrames->setValue( 0 );

    // show information about the first frame
    showFrame( 0 );
    mpeg2_window->openVideoFile( file_name, 
    				 index_list, 
    				 header_list );
    mpeg2_window->resize( 400, 350 );
    mpeg2_window->moveToFirstFrame( true );
    
  }
}