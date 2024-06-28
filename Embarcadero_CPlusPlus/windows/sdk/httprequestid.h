//+-------------------------------------------------------------------------
//
//  Microsoft Windows HTTP Services (WinHTTP)
//  Copyright (C) Microsoft Corporation. All rights reserved.
//
//--------------------------------------------------------------------------


#ifndef __HTTPREQUESTID_H__
#pragma option push -b -a8 -pc -A- -w-pun /*P_O_Push*/
#define __HTTPREQUESTID_H__
#include <winapifamily.h>

#pragma region Desktop Family or OneCore Family
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)


#define DISPID_HTTPREQUEST_BASE                     0x00000001


#define DISPID_HTTPREQUEST_OPEN                     (DISPID_HTTPREQUEST_BASE)
#define DISPID_HTTPREQUEST_SETREQUESTHEADER         (DISPID_HTTPREQUEST_BASE + 1)
#define DISPID_HTTPREQUEST_GETRESPONSEHEADER        (DISPID_HTTPREQUEST_BASE + 2)
#define DISPID_HTTPREQUEST_GETALLRESPONSEHEADERS    (DISPID_HTTPREQUEST_BASE + 3)
#define DISPID_HTTPREQUEST_SEND                     (DISPID_HTTPREQUEST_BASE + 4)
#define DISPID_HTTPREQUEST_OPTION                   (DISPID_HTTPREQUEST_BASE + 5)
#define DISPID_HTTPREQUEST_STATUS                   (DISPID_HTTPREQUEST_BASE + 6)
#define DISPID_HTTPREQUEST_STATUSTEXT               (DISPID_HTTPREQUEST_BASE + 7)
#define DISPID_HTTPREQUEST_RESPONSETEXT             (DISPID_HTTPREQUEST_BASE + 8)
#define DISPID_HTTPREQUEST_RESPONSEBODY             (DISPID_HTTPREQUEST_BASE + 9)
#define DISPID_HTTPREQUEST_RESPONSESTREAM           (DISPID_HTTPREQUEST_BASE + 10)
#define DISPID_HTTPREQUEST_ABORT                    (DISPID_HTTPREQUEST_BASE + 11)
#define DISPID_HTTPREQUEST_SETPROXY                 (DISPID_HTTPREQUEST_BASE + 12)
#define DISPID_HTTPREQUEST_SETCREDENTIALS           (DISPID_HTTPREQUEST_BASE + 13)
#define DISPID_HTTPREQUEST_WAITFORRESPONSE          (DISPID_HTTPREQUEST_BASE + 14)
#define DISPID_HTTPREQUEST_SETTIMEOUTS              (DISPID_HTTPREQUEST_BASE + 15)
#define DISPID_HTTPREQUEST_SETCLIENTCERTIFICATE     (DISPID_HTTPREQUEST_BASE + 16)
#define DISPID_HTTPREQUEST_SETAUTOLOGONPOLICY       (DISPID_HTTPREQUEST_BASE + 17)


#endif /* WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM) */
#pragma endregion

#pragma option pop /*P_O_Pop*/
#endif // __HTTPREQUESTID_H__
