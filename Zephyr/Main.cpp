#include "GameManager.h"


int main()
{
	GameManager* gameManager = &GameManager::Instance();
	gameManager->Run();
	GameManager::Destroy();

	return Context::ErrorCode;
}
