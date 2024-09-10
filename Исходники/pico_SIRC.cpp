//Send a block of data to the FPGA, raise the execution signal, wait for the execution
// signal to be lowered, then read back up to values of results
// startAddress: local address on FPGA input buffer to begin writing at
// length: # of bytes to write
// inData: data to be sent to FPGA
// maxWaitTime: # of seconds to wait until execution timeout
// outData: readback data buffer (if function returns successfully)
// maxOutLength: maximum length of outData buffer provided
// outputLength: number of bytes actually returned (if function returns successfully)
// Returns true if entire process is successful.
// If function fails for any reason, returns false.
//  Check error code with getLastError().
//  error == FAILCAPACITY: The output was larger than provided buffer.  Rather than the number of
//			bytes actually returned, the outputLength variable will contain the TOTAL number bytes the
//			function wanted to return (the number of bytes actually returned will be maxOutLength).
//			If this occurs, user should read back bytes {maxOutLength, outputLength - 1} manually
//			with a subsequent sendRead command.
//  error == FAILREADACK: The write and execution phases completed correctly, but we retried
//			the readback phase too many times.  In this case, like the FAILCAPICITY error, outputLength
//			will contain the TOTAL number bytes the	function wanted to return.  The state of outData is unknown,
//			but some data has been partially written.  The user could try calling sendRead
//			from {0, outputLength-1} manually if re-calling sendWriteAndRun is not easy
//			(for example, if inData and outData overlapped).
//  error == anything else: see normal error list
BOOL PICO_SIRC::sendWriteAndRun(uint32_t startAddress, uint32_t inLength, uint8_t *inData, 
							  uint32_t maxWaitTimeInMsec, uint8_t *outData, uint32_t maxOutLength, 
							  uint32_t *outputLength)
{
	setLastError( 0);

	//Check the input parameters
	if(!inData){
		setLastError( INVALIDBUFFER);
		return false;
	}
	if(startAddress > OUTPUT_OFFSET){
		setLastError( INVALIDADDRESS);
		return false;
	}
	if(inLength == 0 || startAddress + inLength > OUTPUT_OFFSET){
		setLastError( INVALIDLENGTH);
		return false;
	}

	//Check the output parameters
	if(!outData){
		setLastError( INVALIDBUFFER);
		return false;
	}
	if(maxOutLength == 0 || maxOutLength > OUTPUT_OFFSET){
		setLastError( INVALIDLENGTH);
		return false;
	}

	//Send the data to the FPGA
    if (!sendWrite(startAddress,inLength,inData)){
        return false;
    }

    //Send the run cmd
    if (!sendRun()){
        return false;
    }

    //Wait till done
    if (!waitDone( maxWaitTimeInMsec)){
        return false;
    }

    //Read back data
    //BUGBUG what about partial results??
    if (!sendRead(0,maxOutLength,outData)){
        return false;
    }
    *outputLength = maxOutLength;

    //and done
    return true;
}