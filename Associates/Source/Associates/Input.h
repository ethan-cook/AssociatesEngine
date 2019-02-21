#pragma once

#include "Associates/Core.h"

namespace Associates
{
	class ASSOC_API Input
	{
	public:
		inline static bool IsKeyPressed(int KeyCode) { return s_Instance->IsKeyPressedImpl(KeyCode); }
		inline static bool IsMouseButtonPressed(int Button) { return s_Instance->IsMouseButtonPressedImpl(Button); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }

	protected:
		//Implement per platform
		virtual bool IsKeyPressedImpl(int KeyCode) = 0;

		virtual bool IsMouseButtonPressedImpl(int Button) = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
		
		virtual std::pair<float, float> GetMousePositionImpl() = 0;

	private:
		static Input* s_Instance;
	};
}
