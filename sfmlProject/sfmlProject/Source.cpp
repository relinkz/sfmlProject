
#include "Engine.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Engine eng = Engine();
	
	eng.Init();
	eng.Run();
	eng.Shutdown();

	return 0;
}