IOReturn
SATSMARTUserClient::ReadLogAtAddress ( ATASMARTReadLogStruct * structIn,
                                      void * structOut,
                                      IOByteCount inStructSize,
                                      IOByteCount *outStructSize)
{
    
    IOReturn status                  = kIOReturnSuccess;
    IOSATCommand *                  command                 = NULL;
    IOMemoryDescriptor *    buffer                  = NULL;
    DEBUG_LOG("%s[%p]::%s %p(%ld) %p(%ld)\n", getClassName(), this, __FUNCTION__, structIn, (long)inStructSize, structOut, (long)(outStructSize));
    
    if ( inStructSize != sizeof ( ATASMARTReadLogStruct )  || !outStructSize || *outStructSize < 1) {
        return kIOReturnBadArgument;
    }
    
    fOutstandingCommands++;
    
    if ( isInactive ( ) )
    {
        
        status = kIOReturnNoDevice;
        goto ErrorExit;
        
    }
    
    fProvider->retain ( );
    
    command = AllocateCommand ( );
    if ( command == NULL )
    {
        
        status = kIOReturnNoResources;
        goto ReleaseProvider;
        
    }
    
    buffer = IOMemoryDescriptor::withAddress (structOut,  *outStructSize, kIODirectionIn);
    if ( buffer == NULL )
    {
        
        status = kIOReturnNoResources;
        goto ReleaseCommand;
        
    }
    
    status = buffer->prepare ( );
    DEBUG_LOG("%s[%p]::%s status %x\n", getClassName(), this, __FUNCTION__, status);
    if ( status != kIOReturnSuccess )
    {
        
        goto ReleaseBuffer;
        
    }
    
    command->setBuffer                      ( buffer );
    command->setByteCount           ( buffer->getLength());
    command->setFeatures            ( kFeaturesRegisterReadLogAtAddress );
    command->setOpcode                      ( kATAFnExecIO );
    command->setTimeoutMS           ( kATAThirtySecondTimeoutInMS );
    command->setSectorCount         ( structIn->numSectors );
    command->setSectorNumber        ( structIn->logAddress );
    command->setCylLo                       ( kSMARTMagicCylinderLoValue );
    command->setCylHi                       ( kSMARTMagicCylinderHiValue );
    command->setCommand                     ( kATAcmdSMART );
    command->setFlags                       ( mATAFlagIORead );
    
    status = SendSMARTCommand ( command );
    if ( status == kIOReturnIOError )
    {
        
        if ( command->getEndErrorReg ( ) & 0x04 )
        {
            
            ERROR_LOG ( "ReadLogAtAddress %d unsupported\n", structIn->logAddress );
            status = kIOReturnUnsupported;
            
        }
        
        if ( command->getEndErrorReg ( ) & 0x10 )
        {
            
            ERROR_LOG ( "ReadLogAtAddress %d unreadable\n", structIn->logAddress );
            status = kIOReturnNotReadable;
            
        }
        
    }
    
    *outStructSize = buffer->getLength();
    
    buffer->complete ( );
    
    
    
ReleaseBuffer:
    
    
    buffer->release ( );
    buffer = NULL;
    
    
ReleaseCommand:
    
    
    DeallocateCommand ( command );
    command = NULL;
    
    
ReleaseProvider:
    
    
    fProvider->release ( );
    
    
ErrorExit:
    
    
    fOutstandingCommands--;
    
    DEBUG_LOG("%s[%p]::%s result %d\n", getClassName(), this,  __FUNCTION__, status);
    return status;
    
}