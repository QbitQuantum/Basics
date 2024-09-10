already_AddRefed<Promise>
BluetoothGattCharacteristic::WriteValue(const ArrayBuffer& aValue,
                                        ErrorResult& aRv)
{
  nsCOMPtr<nsIGlobalObject> global = do_QueryInterface(GetParentObject());
  if (!global) {
    aRv.Throw(NS_ERROR_FAILURE);
    return nullptr;
  }

  nsRefPtr<Promise> promise = Promise::Create(global, aRv);
  NS_ENSURE_TRUE(!aRv.Failed(), nullptr);

  BT_ENSURE_TRUE_REJECT(mProperties &
                          (GATT_CHAR_PROP_BIT_WRITE_NO_RESPONSE |
                           GATT_CHAR_PROP_BIT_WRITE |
                           GATT_CHAR_PROP_BIT_SIGNED_WRITE),
                        promise,
                        NS_ERROR_NOT_AVAILABLE);

  aValue.ComputeLengthAndData();

  nsTArray<uint8_t> value;
  value.AppendElements(aValue.Data(), aValue.Length());

  BluetoothService* bs = BluetoothService::Get();
  BT_ENSURE_TRUE_REJECT(bs, promise, NS_ERROR_NOT_AVAILABLE);

  nsRefPtr<BluetoothReplyRunnable> result = new BluetoothVoidReplyRunnable(
    nullptr, promise, NS_LITERAL_STRING("GattClientWriteCharacteristicValue"));
  bs->GattClientWriteCharacteristicValueInternal(mService->GetAppUuid(),
                                                 mService->GetServiceId(),
                                                 mCharId,
                                                 mWriteType,
                                                 value,
                                                 result);

  return promise.forget();
}