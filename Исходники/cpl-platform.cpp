/**
 * Get the MAC address of the first logical IP-enabled network interface
 *
 * @param out the output character array
 * @return CPL_OK on success or an error code
 */
cpl_return_t
cpl_platform_get_mac_address(cpl_mac_address_t* out)
{

#ifdef __unix__

	// From: http://stackoverflow.com/questions/1779715/how-to-get-mac-address-of-your-machine-using-a-c-program

	ifreq ifr;
	ifconf ifc;
	char buf[1024];
	int success = 0;

	int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
	if (sock == -1) return CPL_E_PLATFORM_ERROR;

	ifc.ifc_len = sizeof(buf);
	ifc.ifc_buf = buf;
	if (ioctl(sock, SIOCGIFCONF, &ifc) == -1) return CPL_E_PLATFORM_ERROR;

	ifreq* it = ifc.ifc_req;
	const ifreq* const end = it + (ifc.ifc_len / sizeof(ifreq));

	for (; it != end; ++it) {
		strcpy(ifr.ifr_name, it->ifr_name);
		if (ioctl(sock, SIOCGIFFLAGS, &ifr) == 0) {
			if (! (ifr.ifr_flags & IFF_LOOPBACK)) { // don't count loopback
				if (ioctl(sock, SIOCGIFHWADDR, &ifr) == 0) {
					success = 1;
					break;
				}
			}
		}
		else { /* ignore error */ }
	}

	if (success && out) {
		memcpy(out, ifr.ifr_hwaddr.sa_data, 6);
	}

	if (!success) return CPL_E_NOT_FOUND;

#elif defined(__APPLE__)

	/*
	 * Adapted from GetMACAddress.c:
	 *   http://opensource.apple.com/source/DirectoryService
	 *            /DirectoryService-621/CoreFramework/Private/GetMACAddress.c
	 *
	 * Copyright (c) 2003 Apple Computer, Inc. All rights reserved.
	 * 
	 * This file contains Original Code and/or Modifications of Original Code
	 * as defined in and that are subject to the Apple Public Source License
	 * Version 2.0 (the 'License'). You may not use this file except in
	 * compliance with the License. Please obtain a copy of the License at
	 * http://www.opensource.apple.com/apsl/ and read it before using this
	 * file.
	 * 
	 * The Original Code and all software distributed under the License are
	 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
	 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
	 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
	 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
	 * Please see the License for the specific language governing rights and
	 * limitations under the License.
	 */

	kern_return_t kernResult = KERN_FAILURE; 
	mach_port_t masterPort = MACH_PORT_NULL;
	CFMutableDictionaryRef classesToMatch = NULL;
	io_object_t intfService = MACH_PORT_NULL;
	io_object_t controllerService = MACH_PORT_NULL;
	io_iterator_t intfIterator = MACH_PORT_NULL;
	unsigned char macAddress[kIOEthernetAddressSize];
	io_iterator_t *matchingServices = &intfIterator;
	UInt8 *MACAddress = macAddress;

	// Create an iterator with Primary Ethernet interface
	kernResult = IOMasterPort(MACH_PORT_NULL, &masterPort);
	if (kernResult != KERN_SUCCESS) return CPL_E_PLATFORM_ERROR;

	// Ethernet interfaces are instances of class kIOEthernetInterfaceClass
	classesToMatch = IOServiceMatching(kIOEthernetInterfaceClass);
	if (classesToMatch != NULL) {

		CFMutableDictionaryRef propertyMatch;
		propertyMatch = CFDictionaryCreateMutable(kCFAllocatorDefault, 0,
				&kCFTypeDictionaryKeyCallBacks,
				&kCFTypeDictionaryValueCallBacks);

		CFDictionarySetValue(propertyMatch,
				CFSTR(kIOPrimaryInterface), kCFBooleanTrue);
		CFDictionarySetValue(classesToMatch,
				CFSTR(kIOPropertyMatchKey), propertyMatch);

		CFRelease(propertyMatch);

		kernResult = IOServiceGetMatchingServices(masterPort,
				classesToMatch, matchingServices);    
	}


	// Given an iterator across a set of Ethernet interfaces, return the
	// MAC address of the first one.

	intfService = IOIteratorNext(intfIterator);
	if (intfService == MACH_PORT_NULL) {
			IOObjectRelease(intfIterator);
			return CPL_E_PLATFORM_ERROR;
	}

	CFDataRef MACAddressAsCFData = NULL;        
	kernResult = IORegistryEntryGetParentEntry(intfService,
			kIOServicePlane,
			&controllerService);

	if (kernResult != KERN_SUCCESS || controllerService == MACH_PORT_NULL) {
		IOObjectRelease(intfService);
		IOObjectRelease(intfIterator);
		return CPL_E_PLATFORM_ERROR;
	}

	MACAddressAsCFData = (CFDataRef) IORegistryEntryCreateCFProperty(
			controllerService,
			CFSTR(kIOMACAddress),
			kCFAllocatorDefault,
			0);

	if (MACAddressAsCFData != NULL) {
		CFDataGetBytes(MACAddressAsCFData,
				CFRangeMake(0, kIOEthernetAddressSize), MACAddress);
		CFRelease(MACAddressAsCFData);
	}
	else {
		IOObjectRelease(controllerService);
		IOObjectRelease(intfService);
		IOObjectRelease(intfIterator);
		return CPL_E_NOT_FOUND;
	}

	IOObjectRelease(controllerService);
	IOObjectRelease(intfService);
	IOObjectRelease(intfIterator);

	if (out) memcpy(out, macAddress, 6);
	

#elif defined(_WINDOWS)

	PIP_ADAPTER_ADDRESSES AdapterAddresses;
	ULONG family = AF_UNSPEC;
	ULONG flags = 0;
	ULONG outBufLen = 0;
	bool success = false;

	DWORD dwRetVal = GetAdaptersAddresses(family, flags, NULL, NULL, &outBufLen);
	if (dwRetVal == ERROR_NO_DATA) return CPL_E_NOT_FOUND;
	if (dwRetVal == 0 && outBufLen == 0) return CPL_E_NOT_FOUND;
	if (dwRetVal != ERROR_BUFFER_OVERFLOW) return CPL_E_PLATFORM_ERROR;

	AdapterAddresses = (IP_ADAPTER_ADDRESSES*)
		malloc(sizeof(IP_ADAPTER_ADDRESSES) * outBufLen);
	if (AdapterAddresses == NULL) return CPL_E_INSUFFICIENT_RESOURCES;

	dwRetVal = GetAdaptersAddresses(family, flags, NULL, AdapterAddresses,
		&outBufLen);
	if (dwRetVal != 0) { free(AdapterAddresses); return CPL_E_PLATFORM_ERROR; }

	for (PIP_ADAPTER_ADDRESSES p = AdapterAddresses; p != NULL; p = p->Next) {
		if (p->IfType == IF_TYPE_SOFTWARE_LOOPBACK) continue;
		if (p->PhysicalAddressLength != 6 /* Ethernet */) continue;

		success = true;
		if (out) memcpy(out, p->PhysicalAddress, 6);
		break;
	}

	free(AdapterAddresses);

	if (!success) return CPL_E_NOT_FOUND;

#else
#error "Not implemented for this platform"
#endif

	return CPL_OK;
}