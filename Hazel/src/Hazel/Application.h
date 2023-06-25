#pragma once

#include "Core.h"
#include "Event/Event.h"

namespace Hazel
{
	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();


	};

	// TO be define in Client
	Application* CreateApplicaiton();
}
