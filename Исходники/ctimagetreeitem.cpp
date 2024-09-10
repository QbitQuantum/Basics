//calculate segmentation values
bool CTImageTreeItem::internalGetSegmentationValues( SegmentationValues &values) const {
	
	//get ITK image
	ImageType::Pointer image = getITKImage();
	if (image.IsNull()) 
		return false;

	//get buffered region of the image
	ImageType::RegionType ctregion = image->GetBufferedRegion();
	//define an iterator for the binary segment
	typedef itk::ImageRegionConstIteratorWithIndex< BinaryImageType > BinaryIteratorType;
	//get binary segment
	BinaryImageTreeItem::ImageType::Pointer segment = values.m_segment->getITKImage();
	if (segment.IsNull()) 
		return false;

/*	typedef itk::ImageFileWriter< ImageType >  WriterType;
	WriterType::Pointer writer = WriterType::New();
	writer->SetFileName( "test.dcm" );

	writer->SetInput( image );
		try 
		{
			writer->Update();
		}
		catch( itk::ExceptionObject & excep )
		{
			std::cerr << "Exception catched !" << std::endl;
			std::cerr << excep << std::endl;
		}
*/
	//create a binary iterator for the segment and its buffered region
	BinaryIteratorType binIter( segment, segment->GetBufferedRegion() );
	ImageType::PointType point;
  
	//The Accumulators Framework is framework for performing incremental calculations
	using namespace boost::accumulators;
	//http://boost-sandbox.sourceforge.net/libs/accumulators/doc/html/accumulators/user_s_guide.html#accumulators.user_s_guide.the_accumulators_framework
	accumulator_set<double,features<tag::count, tag::min, tag::mean, tag::max, tag::variance> > acc;  
  
	//check selected accuracy
	if (values.m_accuracy == SegmentationValues::SimpleAccuracy) {
		ImageType::IndexType index;
		//iterate over the pixel of the binary segment
		for(binIter.GoToBegin(); !binIter.IsAtEnd(); ++binIter) {
			//if actual value = 255
			if (binIter.Value() == BinaryPixelOn) {
				//transforms the index to a physical point in the binary segment
				segment->TransformIndexToPhysicalPoint(binIter.GetIndex(),point);
				//transform that point to an index of the CT image
				image->TransformPhysicalPointToIndex(point, index);
				//check if that index is inside the CT region
				if (ctregion.IsInside(index)) {
					//get the pixel value at the index
					int t = image->GetPixel(index);
					//check if pixel value != -2048
					if (isRealHUvalue(t)) {
						//accumulate pixel value
						acc( t );
					}
				}
			}
		}
	//check selected accuracy
	} else if (values.m_accuracy == SegmentationValues::PreventDoubleSamplingAccuracy) {
		ImageType::IndexType index;
		//definition for a set of indices, which can be compared
		typedef std::set< ImageType::IndexType, IndexCompareFunctor > IndexSetType;
		IndexSetType indexSet;
		//iterate over the pixel of the binary segment
		for(binIter.GoToBegin(); !binIter.IsAtEnd(); ++binIter) {
			//if actual value = 255
			if (binIter.Value() == BinaryPixelOn) {
				//transforms the index to a physical point in the binary segment
				segment->TransformIndexToPhysicalPoint(binIter.GetIndex(),point);
				//transform that point to an index of the CT image
				image->TransformPhysicalPointToIndex(point, index);
				//check if that index is inside the CT region
				if (ctregion.IsInside(index)) {

					std::pair<IndexSetType::iterator,IndexSetType::iterator> ret;
					//
					ret = indexSet.equal_range(index);
					//If x does not match any key in the container, the range returned has a length of zero, 
					//with both iterators pointing to the nearest value greater than x, if any, 
					//or to set::end if x is greater than all the elements in the container.
					if (ret.first == ret.second) {
						indexSet.insert(ret.first, index);
						//get the pixel value at the index
						int t = image->GetPixel(index);
						//check if pixel value != -2048
						if (isRealHUvalue(t)) {
							//accumulate pixel value
							acc( t );
						}
					}
				}
			}
		}
	//check selected accuracy
	} else if (values.m_accuracy == SegmentationValues::InterpolatedAccuracy) {
		//define an interpolate function
		typedef  itk::LinearInterpolateImageFunction< CTImageType > InterpolatorType;
		InterpolatorType::Pointer interpolator = InterpolatorType::New();
		//set input to the interpolator
		interpolator->SetInputImage( image );
		InterpolatorType::ContinuousIndexType index;
		//iterate over the pixel of the binary segment
		for(binIter.GoToBegin(); !binIter.IsAtEnd(); ++binIter) {
			//if actual value = 255
			if (binIter.Value() == BinaryPixelOn) {
				//transforms the index to a physical point in the binary segment
				segment->TransformIndexToPhysicalPoint(binIter.GetIndex(),point);
				//transform that point to an index of the CT image
				image->TransformPhysicalPointToContinuousIndex(point, index);
				//check if the index is inside the buffer of the interpolator
				if (interpolator->IsInsideBuffer(index)) {
					//Returns the linearly interpolated image intensity
					int t = interpolator->EvaluateAtContinuousIndex(index);
					//check if pixel value != -2048
					if (isRealHUvalue(t)) {
						//accumulate pixel value
						acc( t );
					}
				}
			}
		}  
	}
	//set sample count, min, mean, max and standard deviation
	//from the accumulated intensities
	values.m_sampleCount = count( acc );
	values.m_min = min( acc );
	values.m_mean = mean( acc );
	values.m_max = max( acc );
	values.m_stddev = std::sqrt( variance( acc ) );
	//set the image modification time
	values.m_mtime = segment->GetMTime();
	const_cast<CTImageTreeItem*>(this)->m_segmentationValueCache[ values.m_segment ] = values;
	return values.m_sampleCount > 0;
}    