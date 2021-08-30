#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "Menu.h"
#include "Settings.h"
extern int Width;
extern int Height;

void draw_title_settings(SDL_Renderer*& renderer, SDL_Texture* settingsTexture)
{
	SDL_Rect title_rule_Rect = { Width / 3,Height / 20,Width / 3,Height / 10 };
	SDL_RenderCopy(renderer, settingsTexture, NULL, &title_rule_Rect);
}
void draw_text_styleSettings(SDL_Renderer*& renderer, SDL_Texture* styleTexture, SDL_Texture* styletexture)
{
	SDL_Rect title_rule_Rect = { Width / 2.8,5*Height / 16,Width / 4,Height / 15 };
	SDL_RenderCopy(renderer, styleTexture, NULL, &title_rule_Rect);
	SDL_Rect numberStyle = { Width / 2.8+Width/4+Width/70,5 * Height / 16,Width / 20,Height / 15 };
	SDL_RenderCopy(renderer, styletexture, NULL, &numberStyle);
}
void draw_text_sizeSettings(SDL_Renderer*& renderer, SDL_Texture* sizeTexture, SDL_Texture* size_500x500,
	SDL_Texture* size_600x600, SDL_Texture* size_650x650)
{
	SDL_Rect title_rule_Rect = { Width / 3.5,7*Height / 16,Width/5,Height / 15 };
	SDL_RenderCopy(renderer, sizeTexture, NULL, &title_rule_Rect);
	SDL_Rect size = { Width / 3.5+Width/5+Width/70,7 * Height / 16,Width/4.5,Height / 15 };
	if(Width==500)
		SDL_RenderCopy(renderer, size_500x500, NULL, &size);
	else
	if(Width == 600)
		SDL_RenderCopy(renderer, size_600x600, NULL, &size);
	else
	if(Width == 650)
		SDL_RenderCopy(renderer, size_650x650, NULL, &size);
}
void draw_text_soundsSettings(SDL_Renderer*& renderer, SDL_Texture* soundsTexture,int &musicflag,SDL_Texture* sounds_ON,SDL_Texture* sounds_OFF)
{
	SDL_Rect title_rule_Rect = { Width / 2.8,9*Height / 16,Width/6,Height / 15 };
	SDL_RenderCopy(renderer, soundsTexture, NULL, &title_rule_Rect);
	SDL_Rect music = { Width/2.8+Width/6+Width/70,9 * Height / 16,Width/10,Height / 15 };
	if(musicflag==0)
		SDL_RenderCopy(renderer, sounds_ON, NULL, &music);
	else 
	if(musicflag==1)
		SDL_RenderCopy(renderer, sounds_OFF, NULL, &music);
}
void SETTINGS(SDL_Renderer*& renderer, SDL_Texture* FonTexture, SDL_Texture* settingsTexture, SDL_Texture* color_texture,
	SDL_Texture* size_texture, SDL_Texture* sounds_texture, SDL_Texture* styletexture, int& musicflag, SDL_Texture* sounds_ON,
	SDL_Texture* sounds_OFF, SDL_Texture* size_500x500, SDL_Texture* size_600x600, SDL_Texture* size_650x650)
{
	SDL_RenderClear(renderer);
	draw_fon_menu(renderer, FonTexture);
	draw_title_settings(renderer,settingsTexture);
	draw_text_styleSettings(renderer,color_texture,styletexture);
	draw_text_sizeSettings(renderer,size_texture,  size_500x500,  size_600x600,  size_650x650);
	draw_text_soundsSettings(renderer,sounds_texture,musicflag,sounds_ON,sounds_OFF);
}