#pragma comment(lib, "SDL2_mixer.lib")
#include <stdio.h>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "SDL_mixer.h"
#include "Menu.h"
#include "Rule.h"
#include "tableRecords.h"
#include "Settings.h"
#include "GameProcess.h"
int Width;
int Height;

void loadmusic(Mix_Music *fon)
{
	fon = Mix_LoadMUS("fon.wav");
	Mix_PlayMusic(fon, -1);
}
int main(int argc, char** argv)
{
	srand(time(NULL));
	Width= 500;
	Height = 500;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		printf("%s",SDL_GetError());
	else
	{
		SDL_Window* window = SDL_CreateWindow(u8"Три в ряд", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Width, Height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if(window==NULL)
			printf("%s", SDL_GetError());
		else
		{

			SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
			SDL_SetRenderDrawColor(renderer,0,0,0,0);
			SDL_RenderClear(renderer);
			TTF_Init();

			Mix_Init(0);
			Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
			Mix_Music* fonMusic = NULL;

			TTF_Font* game_font = TTF_OpenFont("font.ttf",100);
			//Меню
			SDL_Texture* titleTexture = get_text_texture(renderer, "Three in a row", game_font);
		    SDL_Texture* FonTexture = fon(renderer);
			SDL_Texture* playTexture= get_text_texture(renderer, "Play", game_font);
			SDL_Texture* ruleTexture = get_text_texture(renderer, "Rule Game", game_font);
			SDL_Texture* recordsTexture = get_text_texture(renderer, "Table of records", game_font);
			SDL_Texture* settingsTexture= get_text_texture(renderer, "Settings", game_font);
			SDL_Texture* exitTexture= get_text_texture(renderer, "Exit", game_font);
			
			//Правила
			SDL_Texture* Rule1 = get_text_texture(renderer, "After the game starts, the player is asked to choose the number", game_font);
			SDL_Texture* Rule2 = get_text_texture(renderer, "of attempts and the size of the field.The screen shows a field filled", game_font);
			SDL_Texture* Rule3 = get_text_texture(renderer, "with balls. It is necessary to collect a row of three or more balls of", game_font);
			SDL_Texture* Rule4 = get_text_texture(renderer, "the same color, changing any 2 adjacent balls in places. After that,", game_font);
			SDL_Texture* Rule5 = get_text_texture(renderer, "the row is removed, and the player is awarded points for each removed", game_font);
			SDL_Texture* Rule6 = get_text_texture(renderer, "ball. On the empty seats of the remote row, balls fall from above.", game_font);
			SDL_Texture* Rule7 = get_text_texture(renderer, "The goal of the game is to score the most points in a limited number ", game_font);
			SDL_Texture* Rule8 = get_text_texture(renderer, "of attempts.", game_font);

			//Таблица рекордов
			SDL_Texture* recordsTitle = get_text_texture(renderer, "Table of Records", game_font);
			SDL_Texture* attempsRecord = get_text_texture(renderer, "attemps", game_font);
			int masRecords[10];
			int nRecords=0;
			FILE* file=NULL;
			
			//Настройки
			SDL_Texture* style_texture = get_text_texture(renderer, "Style Balls", game_font);
			SDL_Texture* size_texture = get_text_texture(renderer, "Size", game_font);
			SDL_Texture* sounds_texture = get_text_texture(renderer, "Music", game_font);
			SDL_Texture* sounds_ON = get_text_texture(renderer, "ON", game_font);
			SDL_Texture* sounds_OFF = get_text_texture(renderer, "OFF", game_font);
			SDL_Texture* size_500x500 = get_text_texture(renderer, "500x500", game_font);
			SDL_Texture* size_600x600 = get_text_texture(renderer, "600x600", game_font);
			SDL_Texture* size_650x650 = get_text_texture(renderer, "650x650", game_font);
			int SizeFlag = 0;
			int StyleFlag = 1;
			int MusicFlag = 0;
			char style[3];
			_itoa_s(StyleFlag, style, 10);
			SDL_Texture* styletexture= get_text_texture(renderer, style, game_font);
			//Настройка игры		
			SDL_Texture* ChooseAttemps= get_text_texture(renderer, "Select the number of attempts", game_font);
			SDL_Texture* EnterTexture= get_text_texture(renderer, "Select and press F", game_font);
			SDL_Texture* SizePoleTexture= get_text_texture(renderer, "Pole size:", game_font);

			//Пауза во время игры
			SDL_Texture* PauseResumeTexture = get_text_texture(renderer, "Resume", game_font);
			SDL_Texture* PauseSettingsTexture = get_text_texture(renderer, "Settings", game_font);
			SDL_Texture* PauseExitTexture = get_text_texture(renderer, "Exit to menu", game_font);
			SDL_Texture* PauseSettingsSizeTexture = get_text_texture(renderer, "Size", game_font);
			SDL_Texture* PauseSettingsSoundsTexture = get_text_texture(renderer, "Sounds", game_font);

			//Игра
			Array pole;
			pole.n = 7;
			pole.m = pole.n*2;
			char text_pole[5];
			_itoa_s(pole.n, text_pole, 10);
			SDL_Texture* texture_pole= get_text_texture(renderer, text_pole, game_font);
			int points =0;	//Очки
			int attemps=10;	//Попытки
			int nAttemps=10;
			
			char text_points[10];	//Прямоугольник с очками
			_itoa_s(points, text_points, 10);
			SDL_Texture* texture_points = get_text_texture(renderer, text_points, game_font);

			char text_attemps[10];	//Прямоугольник с попытками
			_itoa_s(attemps, text_attemps, 10);
			SDL_Texture* texture_attemps = get_text_texture(renderer, text_attemps, game_font);

			SDL_Texture* texture_title_points = get_text_texture(renderer, "Points", game_font);
			SDL_Texture* texture_title_attemps = get_text_texture(renderer, "Attemps", game_font);
			//Шары
			SDL_Texture* FonForPointsTexture=get_texture_FonForPoints(renderer);
			SDL_Texture* Balls1Texture = get_texture_ball(renderer, "Ball1.bmp");
			SDL_Texture* Balls2Texture = get_texture_ball(renderer, "Ball2.bmp");
			SDL_Texture* Balls3Texture = get_texture_ball(renderer, "Ball3.bmp");
			SDL_Texture* Balls4Texture = get_texture_ball(renderer, "Ball4.bmp");
			SDL_Texture* Balls5Texture = get_texture_ball(renderer, "Ball5.bmp");
			
			SDL_Texture* Balls11Texture = get_texture_ball(renderer, "Ball11.bmp");
			SDL_Texture* Balls21Texture = get_texture_ball(renderer, "Ball21.bmp");
			SDL_Texture* Balls31Texture = get_texture_ball(renderer, "Ball31.bmp");
			SDL_Texture* Balls41Texture = get_texture_ball(renderer, "Ball41.bmp");
			SDL_Texture* Balls51Texture = get_texture_ball(renderer, "Ball51.bmp");
			SDL_Texture* BoomTexture = get_texture_ball(renderer, "boom.bmp");
			//Финал
			SDL_Texture* FinalTexture = get_text_texture(renderer, "Your result", game_font);
			SDL_Texture* PressToMenu= get_text_texture(renderer, "Press F", game_font);

			int initPole = 0; //Кол-во инициализаций поля с шарами
			int GameFlag = 0;	//что отрисовывать
			int numRender = 0;	//Кол-во отрисовок

			int moveFlag=0; 
			int tempBalls;
			int i1=-1,i2=-1,j1=-1,j2=-1;

			SDL_Event event;
			bool quit = false;

			loadmusic(fonMusic);

			while (!quit)
			{
				while (SDL_PollEvent(&event))
				{
					if (event.type == SDL_QUIT)
						quit = true;
					//Меню
					if (GameFlag == 0)
					{
						if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) //Кнопки меню
						{
							if (event.button.x >= Width / 2.4 && event.button.x <= Width - Width / 2.4 && event.button.y >= 4 * Height / 15
								&& event.button.y <= 4 * Height / 15 + Height / 8)//Играть
							{
								numRender = 0;
								GameFlag = 8;
								continue;

							}
							if (event.button.x >= Width / 3 && event.button.x <= Width - Width / 3 && event.button.y >= 6 * Height / 15
								&& event.button.y <= 6 * Height / 15 + Height / 10)//Правила
							{
								numRender = 0;
								GameFlag = 2;
							}
							if (event.button.x >= Width / 3.5 && event.button.x <= Width - Width / 3.5 && event.button.y >= 8 * Height / 15
								&& event.button.y <= 8 * Height / 15 + Height / 10)//Рекорды
							{
								numRender = 0;
								GameFlag = 3;
							}
							if (event.button.x >= Width / 2.6 && event.button.x <= Width - Width / 2.6 && event.button.y >= 10 * Height / 15
								&& event.button.y <= 10 * Height / 15 + Height / 10)//Настройки
							{
								numRender = 0;
								GameFlag = 4;
							}
							if (event.button.x >= Width / 2.3 && event.button.x <= Width - Width / 2.3 && event.button.y >= 12 * Height / 15
								&& event.button.y <= 12 * Height / 15 + Height / 10)//Выход
							{
								quit = true;
							}
						}
					}
					if (GameFlag == 0) //Меню
					{
						if (numRender == 0)
						{
							menu(renderer, FonTexture, titleTexture, playTexture, ruleTexture, recordsTexture,
								settingsTexture, exitTexture);
							numRender = 1;
						}
					}
					//Финал игры
					if (GameFlag == 1)
					{					
						if (numRender == 0)
						{
							draw_FinalGame(renderer, FinalTexture, texture_points, FonTexture, PressToMenu);
							numRender = 1;
						}
						if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_f)
						{
							numRender = 0;
							GameFlag = 0;
						}
					}					
					//Правила
					if (GameFlag == 2) 
					{
						if (numRender == 0)
						{
							RULE(renderer, FonTexture, ruleTexture, Rule1, Rule2, Rule3, Rule4, Rule5, Rule6, Rule7, Rule8);
							numRender = 1;
						}
						if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
						{
							GameFlag = 0;
							numRender = 0;
						}
					}
					//Рекорды
					if (GameFlag == 3) 
					{
						if (numRender == 0)
						{
							TABLE_RECORDS(renderer, game_font,FonTexture, recordsTitle, attempsRecord, file);
							numRender = 1;
						}
						if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
						{
							GameFlag = 0;
							numRender = 0;
						}
					}
					//Настройки
					if (GameFlag == 4) 
					{
						SETTINGS(renderer, FonTexture, settingsTexture, style_texture, size_texture, sounds_texture, styletexture,
							MusicFlag,sounds_ON,sounds_OFF,size_500x500,size_600x600,size_650x650);

						if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)	//Кнопки настроек
						{
							if (event.button.x >= Width / 3.5 && event.button.x <= Width / 3.5 + Width / 5 + Width / 70 + Width / 4.5
								&& event.button.y >= 7 * Height / 16 && event.button.y <= 7 * Height / 16 + Height / 15)
							{
								SizeFlag = (SizeFlag + 1) % 3;
								switch (SizeFlag)
								{
								case 0:Width = 500; Height = 500; break;
								case 1:Width = 600; Height = 600; break;
								case 2:Width = 650; Height = 650; break;
								}
								SDL_SetWindowSize(window, Width, Height);
								continue;
							}
							if (event.button.x >= Width / 2.8 && event.button.x <= Width / 2.8 + Width / 4 + Width / 70 + Width / 20 &&
								event.button.y >= 5 * Height / 16 && event.button.y <= 5 * Height / 16 + Height / 15)
							{
								StyleFlag = StyleFlag % 2 + 1;
								_itoa_s(StyleFlag, style, 10);
								SDL_DestroyTexture(styletexture);
								styletexture = get_text_texture(renderer, style, game_font);
							}
							if (event.button.x >= Width / 2.8 && event.button.x <= Width / 2.8 + Width / 6 + Width / 70 + Width / 10 &&
								event.button.y >= 9 * Height / 16 && event.button.y <= 9 * Height / 16 + Height / 15)
								{
									MusicFlag = (MusicFlag + 1) % 2;
									if (MusicFlag == 1) Mix_HaltMusic();
									else 
									if (MusicFlag == 0) loadmusic(fonMusic);
								}
							
						}
						if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
						{
							GameFlag = 0;
							numRender = 0;
						}
					}
					//Отрисовка игры и проверка событий
					if (GameFlag == 5)	
					{
						if (initPole == 0)
						{
							init_pole_balls(pole);
							initPole = 1;
						}
						if(StyleFlag==1)
						GamePlay( pole,renderer, FonTexture, FonForPointsTexture, Balls1Texture, Balls2Texture, Balls3Texture,Balls4Texture,
							Balls5Texture, BoomTexture, texture_title_points, texture_title_attemps, texture_points, texture_attemps, i1, j1);
						else 
						if(StyleFlag==2)
						GamePlay(pole, renderer, FonTexture, FonForPointsTexture, Balls11Texture, Balls21Texture, Balls31Texture, Balls41Texture,
							Balls51Texture, BoomTexture, texture_title_points, texture_title_attemps, texture_points, texture_attemps, i1, j1);
						
						SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_ENABLE);
						if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
						{
							for (int i = pole.n; i < pole.m; i++)
							{
								for (int j = 0; j < pole.n; j++)
								{
									
									if (event.button.x >= j * 4.0 * Width / (5 * pole.n) && event.button.x <= (j + 1) * 4.0 * Width / (5 * pole.n)
										&& event.button.y >= (i - pole.n) * Height * 1.0 / pole.n && event.button.y <= (i - pole.n + 1) * Height * 1.0 / pole.n)
									{
										if (moveFlag == 1 && !(fabs(i1 - i) == 1 && fabs(j1 - j) == 0 || fabs(i1 - i) == 0 && fabs(j1 - j) == 1))
											continue;
											
										moveFlag = (moveFlag + 1) % 3;

										if (moveFlag == 1) 
										{
											i1 = i;
											j1 = j;
										}
										if (moveFlag == 2) 
										{
											i2 = i;
											j2 = j;
										}
									}

								}
							}
						}
						if (moveFlag == 0) i1 = j1 = i2 = j2 = -1;
						if (moveFlag == 2 && (fabs(i1 - i2) == 1 && fabs(j1 - j2) == 0 || fabs(i1 - i2) == 0 && fabs(j1 - j2) == 1))
						{
							tempBalls = pole.arr[i1][j1].color;
							pole.arr[i1][j1].color = pole.arr[i2][j2].color;
							pole.arr[i2][j2].color = tempBalls;
							
							if (StyleFlag == 1)
								draw_pole_balls(renderer, pole, Balls1Texture, Balls2Texture, Balls3Texture, Balls4Texture, Balls5Texture,
									BoomTexture, i1, j1);
							else
								if (StyleFlag == 2)
									draw_pole_balls(renderer, pole, Balls11Texture, Balls21Texture, Balls31Texture, Balls41Texture, Balls51Texture,
										BoomTexture, i1, j1);
							SDL_RenderPresent(renderer);
							SDL_Delay(150);

							if (!search_three(pole, points))
							{								
								tempBalls = pole.arr[i1][j1].color;
								pole.arr[i1][j1].color = pole.arr[i2][j2].color;
								pole.arr[i2][j2].color = tempBalls;
								
								attemps--;
								_itoa_s(attemps, text_attemps, 10);
								SDL_DestroyTexture(texture_attemps);
								texture_attemps = get_text_texture(renderer, text_attemps, game_font);
							}
							else
							{
								SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_IGNORE);
								attemps--;
								_itoa_s(attemps, text_attemps, 10);
								SDL_DestroyTexture(texture_attemps);
								texture_attemps = get_text_texture(renderer, text_attemps, game_font);
								
								move_balls(pole, renderer, Balls1Texture, Balls2Texture, Balls3Texture, Balls4Texture, Balls5Texture, BoomTexture, points,
									StyleFlag, Balls11Texture, Balls21Texture, Balls31Texture, Balls41Texture, Balls51Texture);
								_itoa_s(points, text_points, 10);
								SDL_DestroyTexture(texture_points);
								texture_points = get_text_texture(renderer, text_points, game_font);
							}
							moveFlag = 0;
							i1 = j1 = i2 = j2 = -1;
						}
						if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) //Пауза
						{
							GameFlag = 6;
							SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_ENABLE);
						}
						if (attemps == 0)	//финал игры
						{
							_itoa_s(attemps, text_attemps, 10);
							SDL_DestroyTexture(texture_attemps);
							texture_attemps = get_text_texture(renderer, text_attemps, game_font);
							draw_text_attemps(renderer, texture_attemps);
							SDL_RenderPresent(renderer);
							SDL_Delay(150);

							if(pole.n==7 && nAttemps==10) inputRecords(file, masRecords,"10x7.txt");
							else
							if (pole.n == 8 && nAttemps == 10) inputRecords(file, masRecords ,"10x8.txt");
							else
							if (pole.n == 9 && nAttemps == 10) inputRecords(file, masRecords, "10x9.txt");
							else
							if (pole.n == 7 && nAttemps == 20) inputRecords(file, masRecords, "20x7.txt");
							else
							if (pole.n == 8 && nAttemps == 20) inputRecords(file, masRecords, "20x8.txt");
							else
							if (pole.n == 9 && nAttemps == 20) inputRecords(file, masRecords, "20x9.txt");
							else
							if (pole.n == 7 && nAttemps == 30) inputRecords(file, masRecords, "30x7.txt");
							else
							if (pole.n == 8 && nAttemps == 30) inputRecords(file, masRecords, "30x8.txt");
							else
							if (pole.n == 9 && nAttemps == 30) inputRecords(file, masRecords, "30x9.txt");														
							
							addRecord(masRecords, points);
							sort(masRecords);

							if (pole.n == 7 && nAttemps == 10) outputRecords(file, masRecords, "10x7.txt");
							else
							if (pole.n == 8 && nAttemps == 10) outputRecords(file, masRecords, "10x8.txt");
							else
							if (pole.n == 9 && nAttemps == 10) outputRecords(file, masRecords, "10x9.txt");
							else
							if (pole.n == 7 && nAttemps == 20) outputRecords(file, masRecords, "20x7.txt");
							else
							if (pole.n == 8 && nAttemps == 20) outputRecords(file, masRecords, "20x8.txt");
							else
							if (pole.n == 9 && nAttemps == 20) outputRecords(file, masRecords, "20x9.txt");
							else
							if (pole.n == 7 && nAttemps == 30) outputRecords(file, masRecords, "30x7.txt");
							else
							if (pole.n == 8 && nAttemps == 30) outputRecords(file, masRecords, "30x8.txt");
							else
							if (pole.n == 9 && nAttemps == 30) outputRecords(file, masRecords, "30x9.txt");

							GameFlag = 1;
							nAttemps=attemps = 10;
							points = 0;
							numRender = 0;
							initPole = 0;
							nRecords = 0;
							SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_ENABLE);
							continue;
						}
					}
					//Пауза
					if (GameFlag == 6)
					{
						if (numRender == 0)
						{
							Pause_Game(renderer, PauseResumeTexture, PauseSettingsTexture, PauseExitTexture, FonTexture);
							numRender = 1;
						}
						if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button)
						{
							if (event.button.x >= Width / 2.5 && event.button.x <= Width - Width / 2.5 && event.button.y >= 5 * Height / 16
								&& event.button.y <= 5 * Height / 16 + Height / 15)	//Продолжить игру
							{
								GameFlag = 5;
								numRender = 0;
							}
							if (event.button.x >= Width / 2.8 && event.button.x <= Width - Width / 2.8 && event.button.y >= 9 * Height / 16
								&& event.button.y <= 9 * Height / 16 + Height / 15)	//Выход в главное меню
							{
								GameFlag = 0;
								initPole = 0;
								points = 0;
								attemps = 10;
								numRender = 0;
							}
							if (event.button.x >= Width / 2.5 && event.button.x <= Width - Width / 2.5 && event.button.y >= 7 * Height / 16
								&& event.button.y <= 7 * Height / 16 + Height / 15)	//Настройки
							{
								SDL_Delay(100);
								GameFlag = 7;
								numRender = 0;
								continue;
							}

						}
					}
					if (GameFlag == 7)
					{
						SETTINGS(renderer, FonTexture, settingsTexture, style_texture, size_texture, sounds_texture, styletexture,
							MusicFlag, sounds_ON, sounds_OFF, size_500x500, size_600x600, size_650x650);

						if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)	//Кнопки настроек
						{
							if (event.button.x >= Width / 3.5 && event.button.x <= Width / 3.5 + Width / 5 + Width / 70+Width/4.5 
								&& event.button.y >= 7 * Height / 16 && event.button.y <= 7 * Height / 16 + Height / 15)
							{
								SizeFlag = (SizeFlag + 1) % 3;
								switch (SizeFlag)
								{
								case 0:Width = 500; Height = 500; break;
								case 1:Width = 600; Height = 600; break;
								case 2:Width = 650; Height = 650; break;
								}
								SDL_SetWindowSize(window, Width, Height);
								continue;
							}
							if (event.button.x >= Width / 2.8 && event.button.x <= Width / 2.8 + Width / 4 + Width / 70 +Width/20 && 
								event.button.y >= 5 * Height / 16 && event.button.y <= 5 * Height / 16 + Height / 15)
							{
								StyleFlag = StyleFlag % 2 + 1;
								_itoa_s(StyleFlag, style, 10);
								SDL_DestroyTexture(styletexture);
								styletexture = get_text_texture(renderer, style, game_font);
							}
							if (event.button.x >= Width / 2.8 && event.button.x <= Width / 2.8 + Width / 6 + Width / 70+Width/10 && 
								event.button.y >= 9 * Height / 16 && event.button.y <= 9 * Height / 16 + Height / 15)
							{
								MusicFlag = (MusicFlag + 1) % 2;
								if (MusicFlag == 1)
								{
									Mix_HaltMusic();
								}
								else 
									if (MusicFlag == 0)
									{
										loadmusic(fonMusic);
									}
							}
						}
						if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
						{
							GameFlag = 6;
							numRender = 0;
						}
					}
					//Окно настройки поля и ходов
					if (GameFlag == 8)
						{
							_itoa_s(attemps, text_attemps, 10);
							SDL_DestroyTexture(texture_attemps);
							texture_attemps = get_text_texture(renderer, text_attemps, game_font);

							_itoa_s(pole.n, text_pole, 10);
							SDL_DestroyTexture(texture_pole);
							texture_pole = get_text_texture(renderer, text_pole, game_font);

							draw_startGameWithAttemps(renderer, ChooseAttemps, EnterTexture, texture_attemps,texture_pole, SizePoleTexture);

							if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
							{
								if (event.button.x >= Width / 4 && event.button.x <= Width - Width / 4 && event.button.y >= Height / 3
									&& event.button.y <= Height / 3 + Height / 4)
								{
									attemps = attemps % 30+10;
									nAttemps = attemps;
								}
							}
							if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
							{
								if (event.button.x >= 3 * Width / 8 && event.button.x <= 3 * Width / 8+Width/10 && 
									event.button.y >= 2 * Height / 3 && event.button.y <= 2*Height / 3 + Height / 6)
								{
									pole.n = pole.n % 3 + 7;
									pole.m = 2 * pole.n;
								}
							}
							if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_f)
							{
								numRender = 0;
								GameFlag = 5;

								_itoa_s(points, text_points, 10);
								SDL_DestroyTexture(texture_points);
								texture_points = get_text_texture(renderer, text_points, game_font);
							}
							if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
							{
								GameFlag = 0;
								numRender = 0;
							}
						}
														
					SDL_RenderPresent(renderer);
				}
			}
			//Удаление текстур меню
			SDL_DestroyTexture(playTexture);
			SDL_DestroyTexture(ruleTexture);
			SDL_DestroyTexture(recordsTexture);
			SDL_DestroyTexture(settingsTexture);
			SDL_DestroyTexture(exitTexture);
			SDL_DestroyTexture(FonTexture);
			SDL_DestroyTexture(titleTexture);
			//Удаление текстур настроек
			SDL_DestroyTexture(style_texture);
			SDL_DestroyTexture(sounds_texture);
			SDL_DestroyTexture(size_texture);
			SDL_DestroyTexture(styletexture);
			SDL_DestroyTexture(size_500x500);
			SDL_DestroyTexture(size_600x600);
			SDL_DestroyTexture(size_650x650);
			SDL_DestroyTexture(sounds_ON);
			SDL_DestroyTexture(sounds_OFF);
			//Удаление текстур рекордов
			SDL_DestroyTexture(recordsTitle);
			SDL_DestroyTexture(attempsRecord);
			//Удаление текстур правил
			SDL_DestroyTexture(Rule1);
			SDL_DestroyTexture(Rule2);
			SDL_DestroyTexture(Rule3);
			SDL_DestroyTexture(Rule4);
			SDL_DestroyTexture(Rule5);
			SDL_DestroyTexture(Rule6);
			SDL_DestroyTexture(Rule7);
			SDL_DestroyTexture(Rule8);
			//Удание текстур выбора режима
			SDL_DestroyTexture(ChooseAttemps);
			SDL_DestroyTexture(EnterTexture);
			SDL_DestroyTexture(SizePoleTexture);
			//Пауза 
			SDL_DestroyTexture(PauseResumeTexture);
			SDL_DestroyTexture(PauseSettingsTexture);
			SDL_DestroyTexture(PauseExitTexture);
			SDL_DestroyTexture(PauseSettingsSizeTexture);
			SDL_DestroyTexture(PauseSettingsSoundsTexture);
			//Игра
			SDL_DestroyTexture(FinalTexture);
			SDL_DestroyTexture(texture_points);
			SDL_DestroyTexture(texture_attemps);
			SDL_DestroyTexture(texture_pole);
			SDL_DestroyTexture(texture_title_attemps);
			SDL_DestroyTexture(texture_title_points);
			SDL_DestroyTexture(FonForPointsTexture);
			SDL_DestroyTexture(Balls1Texture);
			SDL_DestroyTexture(Balls2Texture);
			SDL_DestroyTexture(Balls3Texture);
			SDL_DestroyTexture(Balls4Texture);
			SDL_DestroyTexture(Balls5Texture);
			SDL_DestroyTexture(Balls11Texture);
			SDL_DestroyTexture(Balls21Texture);
			SDL_DestroyTexture(Balls31Texture);
			SDL_DestroyTexture(Balls41Texture);
			SDL_DestroyTexture(Balls51Texture);
			SDL_DestroyTexture(BoomTexture);
			SDL_DestroyTexture(PressToMenu);

			Mix_FreeMusic(fonMusic);
			Mix_CloseAudio();
			TTF_CloseFont(game_font);
			TTF_Quit();
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
		}
		SDL_Quit();
	}

return 0;
}
