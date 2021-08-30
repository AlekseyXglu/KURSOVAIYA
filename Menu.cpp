#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>
#include "Menu.h"
#include "Rule.h"
extern int Width;
extern int Height;

SDL_Texture* get_text_texture(SDL_Renderer*& renderer, char* text, TTF_Font* font)
{
	SDL_Surface* textSurface = NULL;
	SDL_Color fore_color = { 255,255,255 };
	SDL_Color back_color = { 0,0,0 };
	textSurface = TTF_RenderText_Shaded(font, text, fore_color, back_color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	return texture;
}
SDL_Texture* get_text_texture(SDL_Renderer*& renderer, const char* text, TTF_Font* font)
{
	SDL_Surface* textSurface = NULL;
	SDL_Color fore_color = { 255,255,255 };
	SDL_Color back_color = { 0,0,0 };
	textSurface = TTF_RenderText_Shaded(font, text, fore_color, back_color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	return texture;
}
void draw_title_game(SDL_Renderer*& renderer,SDL_Texture* textTexture)
{
	SDL_Rect titleRect = {Width/3,Height/20,Width/3,Height/10};
	SDL_RenderCopy(renderer,textTexture,NULL,&titleRect);
}
SDL_Texture* fon(SDL_Renderer*& renderer)
{
	SDL_Surface* FonMenuImage = IMG_Load("FonMenu.bmp");
	SDL_SetColorKey(FonMenuImage, SDL_TRUE, SDL_MapRGB(FonMenuImage->format, 255, 255, 255));
	SDL_Texture* FonMenuTexture = SDL_CreateTextureFromSurface(renderer, FonMenuImage);
	SDL_FreeSurface(FonMenuImage);
	return FonMenuTexture;
}
void draw_fon_menu(SDL_Renderer* &renderer, SDL_Texture* FonMenuTexture)
{
	SDL_Rect FonMenuRect = { 0,0,Width,Height };
	SDL_RenderCopy(renderer, FonMenuTexture, NULL, &FonMenuRect);
}
void draw_play_menu(SDL_Renderer*& renderer,SDL_Texture* playTexture)
{
	SDL_Rect PlayMenuRect = { Width / 2.4,4*Height / 15,Width-2*Width/2.4,Height / 8 };
	SDL_RenderCopy(renderer, playTexture, NULL, &PlayMenuRect);
}
void draw_rule_menu(SDL_Renderer*& renderer, SDL_Texture* ruleTexture)
{
	SDL_Rect RuleMenuRect = { Width / 3,6*Height / 15,Width-2*Width/3,Height / 10 };
	SDL_RenderCopy(renderer, ruleTexture, NULL, &RuleMenuRect);
}
void draw_records_menu(SDL_Renderer*& renderer, SDL_Texture* recordsTexture)
{
	SDL_Rect RecordsMenuRect = { Width / 3.5,8*Height / 15,Width-2*Width/3.5,Height / 10 };
	SDL_RenderCopy(renderer, recordsTexture, NULL, &RecordsMenuRect);
}
void draw_settings_menu(SDL_Renderer*& renderer, SDL_Texture* settingsTexture)
{
	SDL_Rect SettingsMenuRect = { Width / 2.6,10*Height / 15,Width-2*Width/2.6,Height / 10 };
	SDL_RenderCopy(renderer, settingsTexture, NULL, &SettingsMenuRect);
}
void draw_exit_menu(SDL_Renderer*& renderer, SDL_Texture* exitTexture)
{
	SDL_Rect ExitMenuRect = { Width / 2.3,12*Height / 15,Width-2*Width/2.3,Height / 10 };
	SDL_RenderCopy(renderer, exitTexture, NULL, &ExitMenuRect);
}

void menu(SDL_Renderer* &renderer, SDL_Texture* FonMenuTexture, SDL_Texture* textTexture, SDL_Texture* playTexture,
	SDL_Texture* ruleTexture, SDL_Texture* recordsTexture, SDL_Texture* settingsTexture, SDL_Texture* exitTexture)
{
	SDL_RenderClear(renderer);
	draw_fon_menu(renderer,FonMenuTexture);
	draw_title_game(renderer, textTexture);
	draw_play_menu(renderer, playTexture);
	draw_records_menu(renderer, recordsTexture);
	draw_rule_menu(renderer,ruleTexture);
	draw_settings_menu(renderer, settingsTexture);
	draw_exit_menu(renderer,exitTexture);
}

void draw_PauseGame_Resume(SDL_Renderer*& renderer, SDL_Texture* ResumeTexture)
{
	SDL_Rect ResumeRect = { Width / 2.5,5 * Height / 16,Width - 2 * Width / 2.5,Height / 15 };
	SDL_RenderCopy(renderer, ResumeTexture, NULL, &ResumeRect);
}
void draw_PauseGame_Settings(SDL_Renderer*& renderer, SDL_Texture* SettingsTexture)
{
	SDL_Rect SettingsRect = { Width / 2.5,7 * Height / 16,Width - 2 * Width / 2.5,Height / 15 };
	SDL_RenderCopy(renderer, SettingsTexture, NULL, &SettingsRect);
}
void draw_PauseGame_Exit(SDL_Renderer*& renderer, SDL_Texture* ExitTexture)
{
	SDL_Rect ExitRect = { Width / 2.8,9 * Height / 16,Width-2*Width/2.8,Height / 15 };
	SDL_RenderCopy(renderer, ExitTexture, NULL, &ExitRect);
}

void Pause_Game(SDL_Renderer* &renderer,SDL_Texture* ResumeTexture,SDL_Texture* SettingsTexture,SDL_Texture* ExitTexture,SDL_Texture* FonTexture)
{
	SDL_RenderClear(renderer);
	draw_fon_menu(renderer, FonTexture);
	draw_PauseGame_Resume(renderer, ResumeTexture);
	draw_PauseGame_Settings(renderer, SettingsTexture);
	draw_PauseGame_Exit(renderer, ExitTexture);
}