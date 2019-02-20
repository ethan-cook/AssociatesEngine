#pragma once

#include "Associates/Core.h"
#include "Associates/Events/Event.h"

namespace Associates
{
	class ASSOC_API Layer
	{
	public:
		Layer(const std::string& Name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& Event) {}
		
		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}