/* Computes a cross-product of two 3-element vectors.  */
int ns__cross(  struct soap *soap, 
			std::string InputMatFilename,
			std::string AnotherMatFilename,
			std::string &OutputMatFilename=ERROR_FILENAME)
{
	bool timeChecking, memoryChecking;
	getConfig(timeChecking, memoryChecking);
	if(timeChecking){
		start = omp_get_wtime();
	}

    /* read from bin */
    Mat src;
	Mat dst;
	if(!readMat(InputMatFilename, src))
    {
		Log(logERROR) << "cross :: can not read bin file for src1" << std::endl;
        return soap_receiver_fault(soap, "cross :: can not read bin file for src1", NULL);
    }
	
	Mat anotherMat;
	if(!readMat(AnotherMatFilename, anotherMat))
    {
		Log(logERROR) << "cross:: can not read bin file for src2" << std::endl;
        return soap_receiver_fault(soap, "cross :: can not read bin file for src2", NULL);
    }
	try{
        dst = src.cross(anotherMat);
    } catch( cv::Exception& e ) {
        Log(logERROR) << e.what() << std::endl;
        return soap_receiver_fault(soap, e.what(), NULL);
    }
    
	std::string toAppend = "_cross";
    getOutputFilename(OutputMatFilename, toAppend);
    if(!saveMat(OutputMatFilename, dst))
    {
        Log(logERROR) << "cross :: can not save mat to binary file" << std::endl;
        return soap_receiver_fault(soap, "cross :: can not save mat to binary file", NULL);
    }

    src.release();
    dst.release();
    anotherMat.release();

	if(timeChecking) 
	{ 
		end = omp_get_wtime();
		Log(logINFO) << "cross :: " << "time elapsed " << end-start << std::endl;
	}
	
	if(memoryChecking)
	{	
		double vm, rss;
		getMemoryUsage(vm, rss);
		Log(logINFO)<< "mul :: VM usage :" << vm << std::endl 
					<< "Resident set size :" << rss << std::endl;
	}

    return SOAP_OK;
}