void
DisplayMods(
	    ImageHdr *		Hdr,
	    unsigned char *	image )
{
	Module *mod = (Module *)image;
	word	swap, type, size, imsize;

	printf("\nIMAGE BODY:\n");
	imsize = swapword(Hdr->Size);

	while ((unsigned char *)mod < image + imsize)
	{
	putchar('\n');
	type = swapword(mod->Type);

	switch(type)
		{
		case T_Program:
			printf("Type      = Program\n");
			goto bypass;
		case T_Module:
			printf("Type      = Code Module\n");
		bypass:
			size = swapword(mod->Size);
			printf("Size      = %#lx (%ld)\n",size,size);

			printf("Name      = \"%s\"\n",mod->Name);

			swap = swapword(mod->Id);
			printf("Slot      = %#lx (%ld)\n",swap,swap);

			swap = swapword(mod->Version);
			printf("Version   = %#lx (%ld)\n",swap,swap);

			swap = swapword(mod->MaxData);
			printf("MaxData   = %#lx (%ld)\n",swap,swap);

			swap = swapword(mod->Init);
			printf("Init RPTR = %#lx (%ld)\n",swap,swap);

			if (smtopt) {
				/* Cheat slightly, so we can have one version */
				/* of imdump even if the Module struct has no */
				/* MaxCodeP field. */
				swap = swapword(*(((word *)(&mod->Init)) + 1));
				printf("MaxCodeP  = %#lx (%ld)\n",swap,swap);
			}

			if(type == T_Module)
				break;

			swap = swapword(((Program *)mod)->Stacksize);
			printf("Stacksize = %#lx (%ld)\n",swap,swap);

			swap = swapword(((Program *)mod)->Heapsize);
			printf("Heapsize  = %#lx (%ld)\n",swap,swap);

			swap = swapword(((Program *)mod)->Main);
			printf("Main RPTR = %#lx (%ld)\n",swap,swap);
			break;

		case T_ResRef:
			printf("Type      = ResRef\n");

			size = swapword(((ResRef *)mod)->Size);
			printf("Size      = %#lx (%ld)\n",size,size);

			printf("Require   = \"%s\"\n",((ResRef *)mod)->Name);

			swap = swapword(((ResRef *)mod)->Id);
			printf("Slot      = %#lx (%ld)\n",swap,swap);

			swap = swapword(((ResRef *)mod)->Version);
			printf("Version   = %#lx (%ld)\n",swap,swap);

			break;

 	        case T_Device:
			/* This relies on the "Module" structure and
			 * "Device" structure identity for the most part.
			 * (Since <device.h> has too many Helios definitions
			 * for a HOSTed version of this program)
			 */
                        printf("Type      = Device\n") ;

			size = swapword(mod->Size);
			printf("Size      = %#lx (%ld)\n",size,size) ;

			printf("Name      = \"%s\"\n",mod->Name) ;

			swap = swapword(mod->Version);
	                printf("Version   = %#lx (%ld)\n",swap,swap) ;

                	swap = swapword(mod->MaxData);
        	        printf("DevOpen   = %#lx (%ld)\n",swap,swap) ;
	                break ;

		case 0L:
			/* module 0 = last module */
			return;

		default:
			fprintf(stderr, "WARNING: Unknown module type %#lx - skipping\n",type);
			size = mod->Size; /* a definite maybe */
 			if (size <= 0) size = 4;
			break;
		}

		mod = (Module *)((char *)mod + size);
	}
	fprintf(stderr, "imdump exit - no last module indication\n");
}