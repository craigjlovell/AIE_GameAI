#pragma once
#include <raylib.h>

#define ASSETS Assets::GetInstance()

class Assets
{
public:

	static Assets* GetInstance();
	static void CreateSingleton();
	static void DestroySingleton();

	void LoadAssets();
	void UnloadAssets();

	Texture2D imgGameMap;
	Texture2D imgGameMapInfo;
	Image imgGameMapInfoRaw;

	Texture2D player;
	Texture2D guard1;

protected:


private:

	static Assets* ms_singleton;

	Assets();
	~Assets();
};