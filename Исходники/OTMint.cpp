// Make sure this contract checks out. Very high level. 
// Verifies ID and signature.
bool OTMint::VerifyMint(const OTPseudonym & theOperator)
{
	// Make sure that the supposed Contract ID that was set is actually
	// a hash of the contract file, signatures and all.
	if (false == VerifyContractID())
	{
		OTLog::Error("Error comparing Mint ID to Asset Contract ID in OTMint::VerifyMint\n");
		return false;
	}
	else if (false == VerifySignature(theOperator))
	{
		OTLog::Error("Error verifying signature on mint in OTMint::VerifyMint.\n");
		return false;
	}
	
	OTLog::Output(3, "\nWe now know that...\n"
			"1) The Asset Contract ID matches the Mint ID loaded from the Mint file.\n"
			"2) The SIGNATURE VERIFIED.\n\n");
	return true;
}