#include "Hazel.h"



class Sandbox :public Hazel::Application
{
public:
	Sandbox() {};
	~Sandbox() {};

};


Hazel::Application* Hazel::CreateApplicaiton()
{
	return new Sandbox(); 
}
