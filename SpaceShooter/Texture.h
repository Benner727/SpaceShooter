#ifndef TEXTURE_H
#define TEXTURE_H

#include "GameEntity.h"
#include "AssetManager.h"

class Texture : public GameEntity
{
protected:
	SDL_Texture* mTex;

	Graphics* mGraphics;

	int mWidth;
	int mHeight;

	bool mClipped;
	SDL_Rect mRenderRect;
	SDL_Rect mClipRect;

	SDL_Color mColor;
	SDL_Color mFlashColor;
	bool mFlash;
	int mFlashFrames;

	void Color(SDL_Color color);
public:
	Texture(std::string filename);
	Texture(std::string filename, int x, int y, int w, int h);
	Texture(std::string text, std::string fontpath, int size, SDL_Color);
	~Texture();

	Vector2 ScaledDimensions();

	void Color(Uint8 red, Uint8 green, Uint8 blue);
	void Flash(Uint8 red, Uint8 green, Uint8 blue);

	virtual void Render();
};

#endif