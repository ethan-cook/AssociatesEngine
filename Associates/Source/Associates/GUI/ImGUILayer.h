#pragma once

#include "Associates/Layer.h"
#include "Associates/Events/ApplicationEvent.h"
#include "Associates/Events/KeyEvent.h"
#include "Associates/Events/MouseEvent.h"

namespace Associates
{
	class ASSOC_API ImGUILayer : public Layer
	{
	public:
		ImGUILayer();
		~ImGUILayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& Event);
		
	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& Event);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& Event);
		bool OnMouseMovedEvent(MouseMovedEvent& Event);
		bool OnMouseScrolledEvent(MouseScrolledEvent& Event);
		bool OnKeyPressedEvent(KeyPressedEvent& Event);
		bool OnKeyReleasedEvent(KeyReleasedEvent& Event);
		bool OnKeyTypedEvent(KeyTypedEvent& Event);
		bool OnWindowResizedEvent(WindowResizeEvent& Event);

		float m_Time = 0.0f;
	};
}

