/***********************************************************************
 *             RpcEpRegisterA (RPCRT4.@)
 */
RPC_STATUS WINAPI RpcEpRegisterA( RPC_IF_HANDLE IfSpec, RPC_BINDING_VECTOR *BindingVector,
                                  UUID_VECTOR *UuidVector, RPC_CSTR Annotation )
{
  PRPC_SERVER_INTERFACE If = IfSpec;
  ULONG i;
  RPC_STATUS status = RPC_S_OK;
  error_status_t status2;
  ept_entry_t *entries;
  handle_t handle;

  TRACE("(%p,%p,%p,%s)\n", IfSpec, BindingVector, UuidVector, debugstr_a((char*)Annotation));
  TRACE(" ifid=%s\n", debugstr_guid(&If->InterfaceId.SyntaxGUID));
  for (i=0; i<BindingVector->Count; i++) {
    RpcBinding* bind = BindingVector->BindingH[i];
    TRACE(" protseq[%d]=%s\n", i, debugstr_a(bind->Protseq));
    TRACE(" endpoint[%d]=%s\n", i, debugstr_a(bind->Endpoint));
  }
  if (UuidVector) {
    for (i=0; i<UuidVector->Count; i++)
      TRACE(" obj[%d]=%s\n", i, debugstr_guid(UuidVector->Uuid[i]));
  }

  if (!BindingVector->Count) return RPC_S_OK;

  entries = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*entries) * BindingVector->Count * (UuidVector ? UuidVector->Count : 1));
  if (!entries)
      return RPC_S_OUT_OF_MEMORY;

  status = get_epm_handle_server(&handle);
  if (status != RPC_S_OK)
  {
    HeapFree(GetProcessHeap(), 0, entries);
    return status;
  }

  for (i = 0; i < BindingVector->Count; i++)
  {
      unsigned j;
      RpcBinding* bind = BindingVector->BindingH[i];
      for (j = 0; j < (UuidVector ? UuidVector->Count : 1); j++)
      {
          status = TowerConstruct(&If->InterfaceId, &If->TransferSyntax,
                                  bind->Protseq, bind->Endpoint,
                                  bind->NetworkAddr,
                                  &entries[i*(UuidVector ? UuidVector->Count : 1) + j].tower);
          if (status != RPC_S_OK) break;

          if (UuidVector)
              memcpy(&entries[i * UuidVector->Count].object, &UuidVector->Uuid[j], sizeof(GUID));
          else
              memset(&entries[i].object, 0, sizeof(entries[i].object));
          if (Annotation)
              memcpy(entries[i].annotation, Annotation,
                     min(strlen((char *)Annotation) + 1, ept_max_annotation_size));
      }
  }

  if (status == RPC_S_OK)
  {
      while (TRUE)
      {
          __TRY
          {
              ept_insert(handle, BindingVector->Count * (UuidVector ? UuidVector->Count : 1),
                         entries, TRUE, &status2);
          }
          __EXCEPT(rpc_filter)
          {
              status2 = GetExceptionCode();
          }
          __ENDTRY
          if (status2 == RPC_S_SERVER_UNAVAILABLE &&
              is_epm_destination_local(handle))
          {
              if (start_rpcss())
                  continue;
          }
          if (status2 != RPC_S_OK)
              ERR("ept_insert failed with error %d\n", status2);
          status = status2; /* FIXME: convert status? */
          break;
      }
  }
  RpcBindingFree(&handle);

  for (i = 0; i < BindingVector->Count; i++)
  {
      unsigned j;
      for (j = 0; j < (UuidVector ? UuidVector->Count : 1); j++)
          I_RpcFree(entries[i*(UuidVector ? UuidVector->Count : 1) + j].tower);
  }

  HeapFree(GetProcessHeap(), 0, entries);

  return status;
}