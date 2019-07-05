#include <MTX.h>
#include <io.h>
#include <fcntl.h>

class Sandbox : public MTX::Application
{
public:
	Sandbox()
	{}

	~Sandbox()
	{}
};

MTX::Application* MTX::CreateApplication()
{
	return new Sandbox();
}



//TODO: FIGURE OUT HOW TO HIDE THIS IN ENTRYPOINT.H
int CALLBACK WinMain(
	_In_	 HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_	 LPSTR	   lpCmdLine,
	_In_	 int	   nCmdShow)
{
	// Creates a console to log to
	AllocConsole();

	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	int hCrt = _open_osfhandle((long)handle_out, _O_TEXT);
	FILE* hf_out = _fdopen(hCrt, "w");
	setvbuf(hf_out, NULL, _IONBF, 1);
	*stdout = *hf_out;

	HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
	hCrt = _open_osfhandle((long)handle_in, _O_TEXT);
	FILE* hf_in = _fdopen(hCrt, "r");
	setvbuf(hf_in, NULL, _IONBF, 128);
	*stdin = *hf_in;


	// Sends it on into MTX Engine
	EntryPoint();
}