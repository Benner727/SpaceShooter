#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "MathHelper.h"
#include <iostream>
#include <string>

class Graphics
{
public:
	static const int SCREEN_WIDTH = 1024;
	static const int SCREEN_HEIGHT = 896;
	const char* WINDOW_TITLE = "Space Shooter";

private:
	static Graphics* sInstance;
	static bool sInitialized;

	SDL_Window* mWindow;
	SDL_Surface* mBackBuffer;

	SDL_Renderer* mRenderer;

	Graphics();
	~Graphics();

	bool Init();
public:
	static Graphics* Instance();
	static void Release();
	static bool Initialized();

	SDL_Texture* LoadTexture(std::string path);
	SDL_Texture* CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color);

	void ClearBackBuffer();

	void DrawTexture(SDL_Texture* tex, SDL_Rect* clip = nullptr, SDL_Rect* rend = nullptr, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void DrawLine(Vector2 start, Vector2 end);
	void DrawCircle(Vector2 center, float radius);

	void Render();
};

#endif