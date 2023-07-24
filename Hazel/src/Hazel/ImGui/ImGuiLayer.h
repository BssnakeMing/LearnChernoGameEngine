#pragma once
#include "Hazel/Layer.h"

namespace Hazel
{
	class HAZEL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() override;
		void OnAttach() override;
		void OnDetach() override;
		void OnUpdata() override;
		void OnEvent(Event& event) override;

	private:
		float m_time = 0.0f;


	};


}
