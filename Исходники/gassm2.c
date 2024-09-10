int main(int argc, char *argv[])
{
	ERR_VALUE ret = ERR_INTERNAL_ERROR;

	utils_allocator_init(omp_get_num_procs());
	omp_init_lock(&_readCoverageLock);
#ifdef _MSC_VER
	uint64_t startTime = GetTickCount64();
#endif
	ret = options_module_init(37);
	if (ret == ERR_SUCCESS) {
		ret = _init_default_values();
		if (ret == ERR_SUCCESS) {
			ret = options_parse_command_line(argc - 2, argv + 2);
			if (ret == ERR_SUCCESS) {
				PROGRAM_OPTIONS po;
				PROGRAM_STATISTICS st;

				memset(&st, 0, sizeof(st));
				ret = _capture_program_options(&po);
				if (ret == ERR_SUCCESS) {
					omp_set_num_threads(po.OMPThreads);
					const char *cmd = argv[1];
					if (strncmp(cmd, "help", sizeof("help")) == 0) {
						options_print_help();
					} else if (strncmp(cmd, "repair", sizeof("repair")) == 0) {
						size_t refSeqLen = 0;
						FASTA_FILE seqFile;
						char *rsFasta = NULL;

						ret = fasta_load(po.RefSeqFile, &seqFile);
						if (ret == ERR_SUCCESS) {
							ret = fasta_read_seq(&seqFile, &rsFasta, &refSeqLen);
							po.ReferenceSequence = rsFasta;
							if (ret != ERR_SUCCESS)
								fasta_free(&seqFile);
						}

						if (ret == ERR_SUCCESS) {
							ret = utils_calloc(omp_get_num_procs(), sizeof(PUTILS_LOOKASIDE), &_vertexLAs);
							if (ret == ERR_SUCCESS)
								ret = utils_calloc(omp_get_num_procs(), sizeof(PUTILS_LOOKASIDE), &_edgeLAs);

							if (ret == ERR_SUCCESS) {
								ret = utils_calloc(omp_get_num_procs(), sizeof(GEN_ARRAY_ONE_READ), &po.ReadSubArrays);
								if (ret == ERR_SUCCESS) {
									const size_t numThreads = omp_get_num_procs();
									for (size_t i = 0; i < numThreads; ++i) {
										dym_array_init_ONE_READ(po.ReadSubArrays + i, 140);
										_vertexLAs[i] = NULL;
										_edgeLAs[i] = NULL;
									}

									size_t regionCount = 0;
									PACTIVE_REGION regions = NULL;

									ret = input_refseq_to_regions(po.ReferenceSequence, refSeqLen, &regions, &regionCount);
									if (ret == ERR_SUCCESS) {
										const ACTIVE_REGION *pa = NULL;

										pa = regions;
										for (size_t i = 0; i < regionCount; ++i) {
											if (pa->Type == artValid && pa->Length >= po.RegionLength)
												_activeRegionCount += (pa->Length / po.TestStep);

											++pa;
										}

										_activeRegionProcessed = 0;
										pa = regions;
										for (size_t i = 0; i < regionCount; ++i) {
											if (pa->Type == artValid && pa->Length >= po.RegionLength)
												repair_reads_in_parallel(pa, &po);
													
											++pa;
										}

										input_free_regions(regions, regionCount);
									}

									PONE_READ r = po.Reads;
									for (size_t i = 0; i < po.ReadCount; ++i) {
										if (r->NumberOfFixes * 100 / r->ReadSequenceLen <= po.ParseOptions.ReadMaxErrorRate) {
											read_quality_encode(r);
											read_write_sam(stdout, r);
											read_quality_decode(r);
										}

										++r;
									}

									utils_free(rsFasta);
									int i = 0;
#pragma omp parallel for shared (po)
									for (i = 0; i < numThreads; ++i)
										dym_array_finit_ONE_READ(po.ReadSubArrays + i);

									utils_free(po.ReadSubArrays);
								}
							}

							utils_free(_edgeLAs);
							utils_free(_vertexLAs);
							fasta_free(&seqFile);
						}
					} else if (strncmp(cmd, "rfreq", sizeof("rfreq")) == 0) {
						kmer_freq_distribution(&po, po.KMerSize, po.Reads, po.ReadCount);
					} else if (strncmp(cmd, "call", sizeof("call")) == 0) {
						fprintf(stderr, "K-mer size:                 %u\n", po.KMerSize);
						fprintf(stderr, "Active region length:       %u\n", po.RegionLength);
						fprintf(stderr, "Reference:                  %s\n", po.RefSeqFile);
						fprintf(stderr, "Reads:                      %u\n", po.ReadCount);
						fprintf(stderr, "Read coverage threshold:    %u\n", po.Threshold);
						fprintf(stderr, "Min. read position quality: %u\n", po.ReadPosQuality);
						fprintf(stderr, "OpenMP thread count:        %i\n", po.OMPThreads);
						fprintf(stderr, "Output VCF file:            %s\n", po.VCFFile);
						ret = paired_reads_init();
						if (ret == ERR_SUCCESS) {
							if (ret == ERR_SUCCESS) {
								size_t refSeqLen = 0;
								FASTA_FILE seqFile;
								char *rsFasta = NULL;

								ret = fasta_load(po.RefSeqFile, &seqFile);
								if (ret == ERR_SUCCESS) {
									ret = fasta_read_seq(&seqFile, &rsFasta, &refSeqLen);
									po.ReferenceSequence = rsFasta;
									if (ret != ERR_SUCCESS)
										fasta_free(&seqFile);
								}

								if (ret == ERR_SUCCESS) {
									po.VCFFileHandle = NULL;
									if (*po.VCFFile != '\0') {
										ret = utils_fopen(po.VCFFile, FOPEN_MODE_WRITE, &po.VCFFileHandle);
										if (ret == ERR_SUCCESS)
											dym_array_init_VARIANT_CALL(&po.VCArray, 140);
									}

									if (ret == ERR_SUCCESS) {
										ret = utils_calloc(omp_get_num_procs(), sizeof(PUTILS_LOOKASIDE), &_vertexLAs);
										if (ret == ERR_SUCCESS)
											ret = utils_calloc(omp_get_num_procs(), sizeof(PUTILS_LOOKASIDE), &_edgeLAs);
										
										ret = utils_calloc(omp_get_num_procs(), sizeof(GEN_ARRAY_VARIANT_CALL), &po.VCSubArrays);
										if (ret == ERR_SUCCESS) {
											ret = utils_calloc(omp_get_num_procs(), sizeof(GEN_ARRAY_ONE_READ), &po.ReadSubArrays);
											if (ret == ERR_SUCCESS) {
												const size_t numThreads = omp_get_num_procs();
												for (size_t i = 0; i < numThreads; ++i) {
													dym_array_init_VARIANT_CALL(po.VCSubArrays + i, 140);
													dym_array_init_ONE_READ(po.ReadSubArrays + i, 140);
													_vertexLAs[i] = NULL;
													_edgeLAs[i] = NULL;
												}

												size_t regionCount = 0;
												PACTIVE_REGION regions = NULL;

												ret = input_refseq_to_regions(po.ReferenceSequence, refSeqLen, &regions, &regionCount);
												if (ret == ERR_SUCCESS) {
													const ACTIVE_REGION *pa = NULL;

													pa = regions;
													for (size_t i = 0; i < regionCount; ++i) {
														if (pa->Type == artValid && pa->Length >= po.RegionLength)
															_activeRegionCount += (pa->Length / po.TestStep);

														++pa;
													}
														
													_activeRegionProcessed = 0;
													pa = regions;
													for (size_t i = 0; i < regionCount; ++i) {
														if (pa->Type == artValid && pa->Length >= po.RegionLength)
															process_active_region_in_parallel(pa, &po);
														
														++pa;
													}
														
													input_free_regions(regions, regionCount);
												}

												utils_free(rsFasta);
												ret = vc_array_merge(&po.VCArray, po.VCSubArrays, numThreads);
												int i = 0;
#pragma omp parallel for shared(po)
												for (i = 0; i <(int) numThreads; ++i) {
													dym_array_finit_ONE_READ(po.ReadSubArrays + i);
													vc_array_finit(po.VCSubArrays + i);
												}

												utils_free(po.ReadSubArrays);
											}

											utils_free(po.VCSubArrays);
										}

										utils_free(_edgeLAs);
										utils_free(_vertexLAs);

										if (po.VCFFileHandle != NULL) {
											if (ret == ERR_SUCCESS)
												vc_array_print(po.VCFFileHandle, &po.VCArray);

											vc_array_finit(&po.VCArray);
											utils_fclose(po.VCFFileHandle);
										}

									}

									fasta_free(&seqFile);
								}
							} else printf("fix_reads(): %u\n", ret);

							printf("Read coverage: %lf\n", _readBaseCount / _totalRegionLength );
							paired_reads_finit();
						}
					}
				}
			}
		}
	
		options_module_finit();
	}

#ifdef _MSC_VER
	uint64_t endTime = GetTickCount64();
	fprintf(stderr, "Time: %I64u s\n", (endTime - startTime) / 1000);
#endif
	omp_destroy_lock(&_readCoverageLock);

	return ret;
}