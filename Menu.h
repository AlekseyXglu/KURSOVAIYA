#ifndef MENU_H
#define MENU_H
SDL_Texture* get_text_texture(SDL_Renderer*& renderer, char* text, TTF_Font* font);
SDL_Texture* get_text_texture(SDL_Renderer*& renderer, const char* text, TTF_Font* font);
void draw_title_game(SDL_Renderer*& renderer,  SDL_Texture* textTexture);
SDL_Texture* fon(SDL_Renderer*& renderer);
void draw_fon_menu(SDL_Renderer*& renderer, SDL_Texture* FonMenuTexture);
void draw_play_menu(SDL_Renderer*& renderer, SDL_Texture* FonMenuTexture);
void draw_rule_menu(SDL_Renderer*& renderer, SDL_Texture* ruleTexture);
void draw_records_menu(SDL_Renderer*& renderer, SDL_Texture* recordsTexture);
void draw_settings_menu(SDL_Renderer*& renderer, SDL_Texture* settingsTexture);
void draw_exit_menu(SDL_Renderer*& renderer, SDL_Texture* exitTexture);
void menu(SDL_Renderer*& renderer, SDL_Texture* FonMenuTexture, SDL_Texture* textTexture, SDL_Texture* playTexture,
	SDL_Texture* ruleTexture, SDL_Texture* recordsTexture, SDL_Texture* settingsTexture, SDL_Texture* exitTexture);

void draw_PauseGame_Resume(SDL_Renderer*& renderer, SDL_Texture* ResumeTexture);
void draw_PauseGame_Settings(SDL_Renderer*& renderer, SDL_Texture* SettingsTexture);
void draw_PauseGame_Exit(SDL_Renderer*& renderer, SDL_Texture* ExitTexture);
void Pause_Game(SDL_Renderer*& renderer, SDL_Texture* ResumeTexture, SDL_Texture* SettingsTexture, SDL_Texture* ExitTexture, SDL_Texture* FonTexture);
#endif
