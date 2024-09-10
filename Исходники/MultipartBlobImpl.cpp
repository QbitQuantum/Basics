void
MultipartBlobImpl::InitializeBlob(const Sequence<Blob::BlobPart>& aData,
                                  const nsAString& aContentType,
                                  bool aNativeEOL,
                                  ErrorResult& aRv)
{
  mContentType = aContentType;
  BlobSet blobSet;

  for (uint32_t i = 0, len = aData.Length(); i < len; ++i) {
    const Blob::BlobPart& data = aData[i];

    if (data.IsBlob()) {
      RefPtr<Blob> blob = data.GetAsBlob().get();
      blobSet.AppendBlobImpl(blob->Impl());
    }

    else if (data.IsUSVString()) {
      aRv = blobSet.AppendString(data.GetAsUSVString(), aNativeEOL);
      if (aRv.Failed()) {
        return;
      }
    }

    else if (data.IsArrayBuffer()) {
      const ArrayBuffer& buffer = data.GetAsArrayBuffer();
      buffer.ComputeLengthAndData();
      aRv = blobSet.AppendVoidPtr(buffer.Data(), buffer.Length());
      if (aRv.Failed()) {
        return;
      }
    }

    else if (data.IsArrayBufferView()) {
      const ArrayBufferView& buffer = data.GetAsArrayBufferView();
      buffer.ComputeLengthAndData();
      aRv = blobSet.AppendVoidPtr(buffer.Data(), buffer.Length());
      if (aRv.Failed()) {
        return;
      }
    }

    else {
      MOZ_CRASH("Impossible blob data type.");
    }
  }


  mBlobImpls = blobSet.GetBlobImpls();
  SetLengthAndModifiedDate(aRv);
  NS_WARNING_ASSERTION(!aRv.Failed(), "SetLengthAndModifiedDate failed");
}