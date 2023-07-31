#pragma once

#include "Hazel/Core.h"

namespace Hazel
{
	class HAZEL_API Input
	{
	public:
		inline static bool IsKeyPressed(int keycode) { return s_Instace->IsKeyPressedImpl(keycode); }
		inline static bool IsMouseButtonPressed(int button) { return s_Instace->IsMouseButtonPressedImpl(button); }
		inline static float GetMouseX() { return s_Instace->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instace->GetMouseYImpl(); }
		inline static std::pair<float,float> GetMousePosition() { return s_Instace->GetMousePositionImpl(); }
	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
	private:
		static Input* s_Instace;
	};
}