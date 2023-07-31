#pragma once

#include "Hazel/Input.h"

namespace Hazel
{
	// Winodw平台下的输入类
	class WindowsInput :public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override; 
		bool IsMouseButtonPressedImpl(int button) override;
		float GetMouseXImpl() override;
		float GetMouseYImpl() override;
		std::pair<float, float> GetMousePositionImpl() override;
	};

}