#pragma once
// 程序运行入口

#ifdef HZ_PLATFORM_WINDOWS

extern  Hazel::Application* Hazel::CreateApplicaiton();


/**
 * @brief 程序的入口函数
 *
 * @param argc 命令行参数的数量
 * @param argv 指向指针数组的指针，存储命令行参数
 *             argv[0] 存储程序的名称
 *             argv[1]、argv[2] 等存储传递给程序的实际参数
 * @return int 程序的退出状态码
 */
int main(int argc, char** argv)
{
	// 初始化日志系统
	Hazel::Log::Init();
	HZ_CORE_WARN("Initialized Log!");

	int a = 5;
	HZ_INFO("Hello! Var={0}",a);

	auto app = Hazel::CreateApplicaiton();
	app->Run();
	delete app;
}

#endif
