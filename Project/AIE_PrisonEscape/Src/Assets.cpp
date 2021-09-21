#include "Assets.h"

Assets* Assets::ms_singleton = nullptr;

Assets* Assets::GetInstance()
{
	return ms_singleton;
}

void Assets::CreateSingleton()
{
	ms_singleton = new Assets();
}

void Assets::DestroySingleton()
{
	delete ms_singleton;
	ms_singleton = nullptr;
}

Assets::Assets()
{

}

Assets::~Assets()
{

}

void Assets::LoadAssets()
{
	player = LoadTexture("./assets/the-escapists-png-6-png-image-escapists-png-342_399.png");
	
	guard1 = LoadTexture("./assets/the-escapists-png-6-png-image-escapists-png-342_3992.png");

	imgGameMap = LoadTexture("./assets/Prison.png");
	imgGameMapInfo = LoadTexture("./assets/PrisonInfo.png");
	imgGameMapInfoRaw = LoadImage("./assets/PrisonInfo.png");
	
}

void Assets::UnloadAssets()
{
	UnloadTexture(imgGameMap);
	UnloadTexture(imgGameMapInfo);
	UnloadImage(imgGameMapInfoRaw);

	UnloadTexture(player);
	UnloadTexture(guard1);
}