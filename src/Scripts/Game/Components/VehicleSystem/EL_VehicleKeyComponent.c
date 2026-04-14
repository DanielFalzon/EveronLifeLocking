[ComponentEditorProps(category: "EveronLife/Feature/Vehicles", description: "Identifies which vehicle this key belongs to.")]
class EL_VehicleKeyComponentClass : ScriptComponentClass
{
}

class EL_VehicleKeyComponent : ScriptComponent
{
	[Attribute("")]
	protected string m_sDebugIdentifier;

	[RplProp()]
	protected string m_sVehicleIdentifier;

	//------------------------------------------------------------------------------------------------
	string GetVehicleIdentifier()
	{
		return m_sVehicleIdentifier;
	}

	//------------------------------------------------------------------------------------------------
	override void EOnInit(IEntity owner)
	{
		super.EOnInit(owner);


		if (m_sDebugIdentifier != "")
			m_sVehicleIdentifier = m_sDebugIdentifier;
	}
}
