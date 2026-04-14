[ComponentEditorProps(category: "EveronLife/Feature/Vehicles", description: "Locks a vehicle to players with a matching key.")]
class EL_VehicleLockComponentClass : SCR_BaseLockComponentClass
{
}

class EL_VehicleLockComponent : SCR_BaseLockComponent
{
	[Attribute("")]
	protected string m_sDebugIdentifier;

	[RplProp()]
	protected string m_sVehicleIdentifier;

	//------------------------------------------------------------------------------------------------
	override void EOnInit(IEntity owner)
	{
		super.EOnInit(owner);

		if (m_sDebugIdentifier != "")
			m_sVehicleIdentifier = m_sDebugIdentifier;

		SetLocked(true);
	}

	//------------------------------------------------------------------------------------------------
	void ToggleLocked()
	{
		SetLocked(!m_bIsLocked);
	}

	//------------------------------------------------------------------------------------------------
	bool IsVehicleLocked()
	{
		return m_bIsLocked;
	}

	//------------------------------------------------------------------------------------------------
	override bool IsLocked(IEntity user, BaseCompartmentSlot compartmentSlot)
	{
		CharacterControllerComponent characterController = CharacterControllerComponent.Cast(user.FindComponent(CharacterControllerComponent));
		if (characterController && IsValidKey(characterController.GetAttachedGadgetAtLeftHandSlot()))
			return false;

		SCR_InventoryStorageManagerComponent inventoryManager = SCR_InventoryStorageManagerComponent.Cast(user.FindComponent(SCR_InventoryStorageManagerComponent));
		if (!inventoryManager)
			return true;

		array<IEntity> inventoryItems();
		inventoryManager.GetItems(inventoryItems);

		foreach (IEntity item : inventoryItems)
		{
			if (IsValidKey(item))
				return false;
		}

		// Spawn protection always takes precedence
		if (compartmentSlot && m_pVehicleSpawnProtection && m_pVehicleSpawnProtection.IsProtected(user, compartmentSlot))
			return true;

		if (!m_bIsLocked)
			return false;

		if (!user)
			return true;

		return true;
	}

	//------------------------------------------------------------------------------------------------
	bool IsValidKey(IEntity key)
	{
		EL_VehicleKeyComponent keyComp = EL_VehicleKeyComponent.Cast(key.FindComponent(EL_VehicleKeyComponent));
		if (!keyComp)
			return false;

		return keyComp.GetVehicleIdentifier() == m_sVehicleIdentifier;
	}

	//------------------------------------------------------------------------------------------------
	override LocalizedString GetCannotPerformReason(IEntity user)
	{
		if (m_bIsLocked)
			return "Locked";

		return super.GetCannotPerformReason(user);
	}
}
