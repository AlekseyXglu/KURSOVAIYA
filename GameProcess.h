#ifndef GameProcess_H
#define GameProcess_H
struct ball {
	int color;
};
struct Array {
	ball arr[20][20];
	int n, m;
};
SDL_Texture* get_texture_FonForPoints(SDL_Renderer*& renderer);
SDL_Texture* get_texture_ball(SDL_Renderer*& renderer, const char* arr);

void draw_fonForPoints(SDL_Renderer* renderer, SDL_Texture* FonForPointsTexture);
void draw_title_points(SDL_Renderer* renderer, SDL_Texture* texture_title_points);
void draw_text_points(SDL_Renderer* renderer, SDL_Texture* texture_points);
void draw_title_attemps(SDL_Renderer* renderer, SDL_Texture* texture_title_attemps);
void draw_text_attemps(SDL_Renderer* renderer, SDL_Texture* texture_attemps);
void draw_FinalGame(SDL_Renderer* renderer, SDL_Texture* FinalTexture, SDL_Texture* texture_points, SDL_Texture* FonTexture, SDL_Texture* PressToMenu);

void draw_startGameWithAttemps(SDL_Renderer* renderer, SDL_Texture* StartTexture, SDL_Texture* EnterTexture, 
	SDL_Texture* Vibor, SDL_Texture* texture_pole, SDL_Texture* SizePoleTexture);

void draw_pole_balls(SDL_Renderer* renderer, Array& pole, SDL_Texture* Balls1Texture, SDL_Texture* Balls2Texture,
	SDL_Texture* Balls3Texture, SDL_Texture* Balls4Texture, SDL_Texture* Balls5Texture, SDL_Texture* BoomTexture,int i1, int j1);

int search_hod(Array& pole);
int search_three(Array& pole);
int search_three(Array& pole, int& points);

void move_balls(Array& pole, SDL_Renderer*& renderer, SDL_Texture* Balls1Texture, SDL_Texture* Balls2Texture,
	SDL_Texture* Balls3Texture, SDL_Texture* Balls4Texture, SDL_Texture* Balls5Texture, SDL_Texture* BoomTexture, int& points, int& StyleFlag,
	SDL_Texture* Balls11Texture, SDL_Texture* Balls21Texture, SDL_Texture* Balls31Texture, SDL_Texture* Balls41Texture, SDL_Texture* Balls51Texture);
void init_pole_balls(Array &pole);

void GamePlay( Array& arr,SDL_Renderer* renderer, SDL_Texture* FonTexture, SDL_Texture* FonForPointsTexture, SDL_Texture* Balls1Texture,
	SDL_Texture* Balls2Texture, SDL_Texture* Balls3Texture, SDL_Texture* Balls4Texture, SDL_Texture* Balls5Texture, SDL_Texture* BoomTexture,
	SDL_Texture* texture_title_points, SDL_Texture* texture_title_attemps, SDL_Texture* texture_points, SDL_Texture* texture_attemps,
	 int i1, int j1);

#endif