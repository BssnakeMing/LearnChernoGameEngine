#pragma once



#ifdef HZ_PLATFORM_WINDOWS

extern Hazel::Application* CreateApplication();

int main()
{
	printf("Hazel Engine");

	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;

	return 0;
}


#endif
