class EL_OpenVehicleStorageAction : SCR_OpenVehicleStorageAction
{
	//------------------------------------------------------------------------------------------------
	override bool CanBePerformedScript(IEntity user)
	{
		if (!super.CanBePerformedScript(user))
			return false;

		EL_VehicleLockComponent vehicleLock = EL_VehicleLockComponent.Cast(GetOwner().FindComponent(EL_VehicleLockComponent));
		if (!vehicleLock.IsVehicleLocked())
			return true;

		SCR_InventoryStorageManagerComponent inventoryManager = SCR_InventoryStorageManagerComponent.Cast(user.FindComponent(SCR_InventoryStorageManagerComponent));
		if (!inventoryManager)
		{
			SetCannotPerformReason("Locked");
			return false;
		}

		CharacterControllerComponent characterController = CharacterControllerComponent.Cast(user.FindComponent(CharacterControllerComponent));
		if (characterController && vehicleLock.IsValidKey(characterController.GetAttachedGadgetAtLeftHandSlot()))
			return true;

		array<IEntity> inventoryItems();
		inventoryManager.GetItems(inventoryItems);

		foreach (IEntity item : inventoryItems)
		{
			if (vehicleLock.IsValidKey(item))
				return true;
		}

		SetCannotPerformReason("Locked");
		return false;
	}
}
