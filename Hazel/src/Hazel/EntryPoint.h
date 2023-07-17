#pragma once
// �����������

#ifdef HZ_PLATFORM_WINDOWS

extern  Hazel::Application* Hazel::CreateApplicaiton();


/**
 * @brief �������ں���
 *
 * @param argc �����в���������
 * @param argv ָ��ָ�������ָ�룬�洢�����в���
 *             argv[0] �洢���������
 *             argv[1]��argv[2] �ȴ洢���ݸ������ʵ�ʲ���
 * @return int ������˳�״̬��
 */
int main(int argc, char** argv)
{
	// ��ʼ����־ϵͳ
	Hazel::Log::Init();
	HZ_CORE_WARN("Initialized Log!");

	int a = 5;
	HZ_INFO("Hello! Var={0}",a);

	auto app = Hazel::CreateApplicaiton();
	app->Run();
	delete app;
}

#endif
