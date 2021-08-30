#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "Menu.h"
#include "Rule.h"
extern int Width;
extern int Height;

void draw_title_rule(SDL_Renderer*& renderer, SDL_Texture* ruleTexture)
{
	SDL_Rect title_rule_Rect = { Width / 3,Height / 20,Width / 3,Height / 10 };
	SDL_RenderCopy(renderer, ruleTexture, NULL, &title_rule_Rect);
}
void draw_text_rule(SDL_Renderer*& renderer, SDL_Texture* ruleTexture)
{
	SDL_Rect title_rule_Rect = { 0,Height / 16,Width,Height-Height/16 };
	SDL_RenderCopy(renderer, ruleTexture, NULL, &title_rule_Rect);
}

void RULE(SDL_Renderer*&renderer,SDL_Texture* FonTexture,SDL_Texture* ruleTexture, SDL_Texture* Rule1,SDL_Texture* Rule2, SDL_Texture* Rule3,
	SDL_Texture* Rule4, SDL_Texture* Rule5, SDL_Texture* Rule6, SDL_Texture* Rule7, SDL_Texture* Rule8)
{
	SDL_RenderClear(renderer);
	draw_fon_menu(renderer,FonTexture);
	draw_title_rule(renderer, ruleTexture);

	SDL_Rect Rect1 = {Width/15,Height/5,Width-2*Width/15,Height/20};
	SDL_Rect Rect2 = { Width / 15 ,5*Height / 20 ,Width - 2 * Width / 15,Height / 20 };
	SDL_Rect Rect3 = { Width / 15 ,6*Height / 20 ,Width - 2 * Width / 15,Height / 20 };
	SDL_Rect Rect4 = { Width / 15 ,7 * Height / 20 ,Width - 2 * Width / 15,Height / 20 };
	SDL_Rect Rect5 = { Width / 15 ,8*Height / 20 ,Width - 2 * Width / 15,Height / 20 };
	SDL_Rect Rect6 = { Width / 15 ,9*Height / 20 ,Width - 2 * Width / 15,Height / 20 };
	SDL_Rect Rect7 = { Width / 15 ,10*Height / 20 ,Width - 2 * Width / 15,Height / 20 };
	SDL_Rect Rect8 = { Width / 15 ,11*Height / 20 ,Width/6,Height / 20 };
	SDL_RenderCopy(renderer, Rule1, NULL, &Rect1);
	SDL_RenderCopy(renderer, Rule2, NULL, &Rect2);
	SDL_RenderCopy(renderer, Rule3, NULL, &Rect3);
	SDL_RenderCopy(renderer, Rule4, NULL, &Rect4);
	SDL_RenderCopy(renderer, Rule5, NULL, &Rect5);
	SDL_RenderCopy(renderer, Rule6, NULL, &Rect6);
	SDL_RenderCopy(renderer, Rule7, NULL, &Rect7);
	SDL_RenderCopy(renderer, Rule8, NULL, &Rect8);
}