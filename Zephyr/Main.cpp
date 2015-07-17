#include "GameManager.h"


int main()
{
	GameManager* gameManager = &GameManager::Instance();
	gameManager->Initialization();
	gameManager->Run();
	GameManager::Destroy();

	return Context::ErrorCode;
}
