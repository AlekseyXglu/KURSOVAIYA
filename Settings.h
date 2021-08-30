#ifndef Settings_H
#define Settings_H
void draw_title_settings(SDL_Renderer*& renderer, SDL_Texture* settingsTexture);
void draw_text_styleSettings(SDL_Renderer*& renderer, SDL_Texture* styleTexture, SDL_Texture* styletexture);
void draw_text_sizeSettings(SDL_Renderer*& renderer, SDL_Texture* sizeTexture,  SDL_Texture* size_500x500,
	SDL_Texture* size_600x600, SDL_Texture* size_650x650);
void draw_text_soundsSettings(SDL_Renderer*& renderer, SDL_Texture* soundsTexture, int& musicflag, SDL_Texture* sounds_ON,
	SDL_Texture* sounds_OFF);
void SETTINGS(SDL_Renderer*& renderer, SDL_Texture* FonTexture, SDL_Texture* settingsTexture, SDL_Texture* color_texture,
	SDL_Texture* size_texture, SDL_Texture* sounds_texture, SDL_Texture* styletexture, int& musicflag, SDL_Texture* sounds_ON,
	SDL_Texture* sounds_OFF, SDL_Texture* size_500x500, SDL_Texture* size_600x600, SDL_Texture* size_650x650);

#endif