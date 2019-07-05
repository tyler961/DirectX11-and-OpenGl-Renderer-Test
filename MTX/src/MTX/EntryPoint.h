#pragma once

#include "Application.h"
#include "Log.h"
#include "pch.h"

// If Windows AND using Direct3D use code to create a windows with Windows API
#/*if defined MTX_PLATFORM_WINDOWS && defined MTX_DIRECT3D11

extern MTX::Application* MTX::CreateApplication();

int CALLBACK WinMain(
	_In_	 HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_	 LPSTR	   lpCmdLine,
	_In_	 int	   nCmdShow )
{
	MTX::Log::Init();

	auto app = MTX::CreateApplication();
	app->Run();
	delete app;

	return 0;
}*/

//#else
//// If Windows AND OpenGL
//#if defined MTX_PLATFORM_WINDOWS && defined MTX_OPENGL
//extern MTX::Application* MTX::CreateApplication();
//
//int main(int argc, char** argv)
//{
//	MTX::Log::Init();
//
//	auto app = MTX::CreateApplication();
//	app->Run();
//	delete app;
//}
//#endif
//#endif

void EntryPoint()
{
	MTX::Log::Init();

	auto app = MTX::CreateApplication();
	app->Run();
	delete app;
}
