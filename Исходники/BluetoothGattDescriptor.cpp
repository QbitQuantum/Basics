// Constructor of BluetoothGattDescriptor in ATT server role
BluetoothGattDescriptor::BluetoothGattDescriptor(
  nsPIDOMWindow* aOwner,
  BluetoothGattCharacteristic* aCharacteristic,
  const nsAString& aDescriptorUuid,
  const GattPermissions& aPermissions,
  const ArrayBuffer& aValue)
  : mOwner(aOwner)
  , mCharacteristic(aCharacteristic)
  , mUuidStr(aDescriptorUuid)
  , mPermissions(BLUETOOTH_EMPTY_GATT_ATTR_PERM)
  , mAttRole(ATT_SERVER_ROLE)
  , mActive(false)
{
  MOZ_ASSERT(aOwner);
  MOZ_ASSERT(aCharacteristic);

  // UUID
  memset(&mDescriptorId, 0, sizeof(mDescriptorId));
  StringToUuid(aDescriptorUuid, mDescriptorId.mUuid);

  // permissions
  GattPermissionsToBits(aPermissions, mPermissions);

  // value
  aValue.ComputeLengthAndData();
  mValue.AppendElements(aValue.Data(), aValue.Length());
}