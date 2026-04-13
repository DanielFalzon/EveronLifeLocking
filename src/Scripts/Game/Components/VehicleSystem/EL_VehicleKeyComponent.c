class EL_VehicleKeyComponentClass : ScriptComponentClass {

}

class EL_VehicleKeyComponent : ScriptComponent {
	
	[Attribute("Debug Identifier")]
	string m_DebugIdentifier;
	
	[RplProp()]
	string m_VehicleIdentifier;
	
	override void EOnInit(IEntity owner)
    {
        super.EOnInit(owner);
        
        if (m_DebugIdentifier != "")
			m_VehicleIdentifier = m_DebugIdentifier;
    }
}

