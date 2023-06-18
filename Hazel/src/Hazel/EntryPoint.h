#pragma once


#ifdef HZ_PLATFORM_WINDOWS

extern  Hazel::Application* Hazel::CreateApplicaiton();

int main(int argc, char** argv)
{
	printf("Hazel Engine");

	auto app = Hazel::CreateApplicaiton();
	app->Run();
	delete app;
}

#endif
