#include "MemoryLeakDetector.h"
#define GLEW_STATIC
#include <glew.h>

#include "GameManager.h"

int main()
{
	GameManager* gameManager = &GameManager::Instance();
	gameManager->Run();
	GameManager::Destroy();

#ifdef _DEBUG
	std::cout << CurrentMemoryUsage() << std::endl;
	DumpUnfreed();
#endif

	return Context::ErrorCode;
}