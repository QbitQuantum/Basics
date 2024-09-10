int main(int argc, char** argv)
{
    if (argc != 2) {
        printf("Please use VMID as argument\n");
        return -1;
    }

	const char *msg = "***Hello! This message is from the host!***\n";
	WSADATA wsaData;
	SOCKADDR_HV remoteAddr;
	SOCKET fd;
	int ret;

	// Initialize Winsock
	ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (ret != NO_ERROR) {
		printf("WSAStartup() failed with error: %d\n", ret);
		return -1;
	}

	memset(&remoteAddr, 0, sizeof(SOCKADDR_HV));
	remoteAddr.Family = AF_HYPERV;

	// The Linux VM is listening in Vsock port 0x808
	TryConvertVsockPortToServiceId(0x808, &remoteAddr.ServiceId);

	// This is the "remote" VM's VMID got by the PowerShell command
	// "Get-VM -Name <the_VM_name> | ft id".
	if (UuidFromStringA((RPC_CSTR)argv[1],
		&remoteAddr.VmId) != RPC_S_OK) {
		printf("Failed to parse the remote VMID: %d\n", GetLastError());
		ret = -1;
		goto out;
	}

	if (ConnectToVM(&remoteAddr, &fd) < 0) {
		printf("Failed to connect to the VM!\n");
		ret = -1;
		goto out;
	}
	ret = send(fd, msg, strlen(msg), 0);
	printf("Sent a msg to the VM: msg_len = %d.\nExited.\n", ret);

	closesocket(fd);
	WSACleanup();
	return 0;
out:
	WSACleanup();
	return ret;
}