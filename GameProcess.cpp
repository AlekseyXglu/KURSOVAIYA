#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "Menu.h"
#include "GameProcess.h"
extern int Width;
extern int Height;
SDL_Texture* get_texture_FonForPoints(SDL_Renderer*& renderer)
{
	SDL_Surface* textureImage = IMG_Load("FonForPoints.bmp");
	SDL_SetColorKey(textureImage, SDL_TRUE, SDL_MapRGB(textureImage->format, 255, 255, 255));
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textureImage);
	SDL_FreeSurface(textureImage);
	return texture;
}
SDL_Texture* get_texture_ball(SDL_Renderer*& renderer, const char *arr)
{
	SDL_Surface* textureImage = IMG_Load(arr);
	SDL_SetColorKey(textureImage, SDL_TRUE, SDL_MapRGB(textureImage->format, 255, 255, 255));
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textureImage);
	SDL_FreeSurface(textureImage);
	return texture;
}

void draw_fonForPoints(SDL_Renderer* renderer, SDL_Texture* FonForPointsTexture)
{
	SDL_Rect FonForPointsRect;
	FonForPointsRect = { 4*Width/5, 0,Width / 5,Height};
	SDL_RenderCopy(renderer, FonForPointsTexture, NULL, &FonForPointsRect);
}
void draw_title_points(SDL_Renderer* renderer, SDL_Texture* texture_title_points)
{
	SDL_Rect title_pointsRect;
	title_pointsRect = { 4 * Width / 5+Width/25, Height/15,Width/5-2*Width/25,Height/10 };
	SDL_RenderCopy(renderer, texture_title_points, NULL, &title_pointsRect);
}
void draw_text_points(SDL_Renderer* renderer, SDL_Texture* texture_points)
{
	SDL_Rect text_pointsRect;
	text_pointsRect = { 4 * Width / 5 + Width / 25, Height / 15+Height/10,Width / 5 - 2*Width / 25,Height / 10 };
	SDL_RenderCopy(renderer, texture_points, NULL, &text_pointsRect);
}
void draw_title_attemps(SDL_Renderer* renderer, SDL_Texture* texture_title_attemps)
{
	SDL_Rect title_attempsRect;
	title_attempsRect = { 4 * Width / 5 + Width / 25, Height / 15+2*Height/10,Width / 5 - 2*Width / 25,Height / 10 };
	SDL_RenderCopy(renderer, texture_title_attemps, NULL, &title_attempsRect);
}
void draw_text_attemps(SDL_Renderer* renderer, SDL_Texture* texture_attemps)
{
	SDL_Rect text_attempsRect;
	text_attempsRect = { 4 * Width / 5 + Width / 25, Height / 15+3*Height/10,Width / 5 - 2*Width / 25,Height / 10 };
	SDL_RenderCopy(renderer, texture_attemps, NULL, &text_attempsRect);
}
void draw_FinalGame(SDL_Renderer* renderer, SDL_Texture* FinalTexture, SDL_Texture* texture_points,SDL_Texture* FonTexture,
	SDL_Texture *PressToMenu)
{
	SDL_Rect Fon = { 0,0,Width,Height };
	SDL_RenderCopy(renderer, FonTexture, NULL, &Fon);
	SDL_Rect FinalRect;
	FinalRect = { Width/4, Height/10,Width-2*Width/4,Height/16};
	SDL_RenderCopy(renderer, FinalTexture, NULL, &FinalRect);
	SDL_Rect pointsRect;
	pointsRect = {Width/3,Height/4,Width-2*Width/3,Height/5};
	SDL_RenderCopy(renderer, texture_points, NULL, &pointsRect);
	SDL_Rect pressF;
	pressF = { 3*Width / 8,3*Height / 4,Width - 2 * 3*Width / 8,Height / 20 };
	SDL_RenderCopy(renderer, PressToMenu, NULL, &pressF);
}

void draw_startGameWithAttemps(SDL_Renderer* renderer, SDL_Texture* StartTexture, SDL_Texture* EnterTexture,
	SDL_Texture* Vibor,SDL_Texture* texture_pole,SDL_Texture* SizePoleTexture)
{
	SDL_RenderClear(renderer);
	SDL_Rect Rect1;
	Rect1 = { Width / 6,Height / 20,Width-2*Width/6,Height / 5 };
	SDL_RenderCopy(renderer, StartTexture, NULL, &Rect1);
	SDL_Rect Rect2;
	Rect2 = { Width/4, Height/3,Width-2*Width/4,Height/4 };
	SDL_RenderCopy(renderer, Vibor, NULL, &Rect2);
	SDL_Rect Rect3;
	Rect3 = { Width/8,5*Height/6,Width-2*Width/8,Height/6 };
	SDL_RenderCopy(renderer, EnterTexture, NULL, &Rect3);
	SDL_Rect Rect4;
	Rect4 = { Width / 8,2 * Height / 3,Width/6,Height / 6 };
	SDL_RenderCopy(renderer, SizePoleTexture, NULL, &Rect4);
	SDL_Rect Rect5;
	Rect5 = { 3*Width / 8,2 * Height / 3,Width/10,Height / 6 };
	SDL_RenderCopy(renderer, texture_pole, NULL, &Rect5);
}

void draw_pole_balls(SDL_Renderer* renderer, Array& pole, SDL_Texture* Balls1Texture, SDL_Texture* Balls2Texture,
	SDL_Texture* Balls3Texture, SDL_Texture* Balls4Texture, SDL_Texture* Balls5Texture, SDL_Texture* BoomTexture, int i1, int j1)
{
	SDL_Rect ball;
	for (int i = pole.n; i < pole.m; i++)
		for (int j = 0; j < pole.n; j++)
		{
			if (i1 == i && j1 == j)
				ball = { int(j * 4.0 * Width / (5 * pole.n) + 10),int((i - pole.n) * Height * 1.0 / pole.n + 10),int(4.0 * Width / (5 * pole.n) - 20),int(Height * 1.0 / pole.n - 20) };
			else ball = { int(j * 4.0 * Width / (5 * pole.n)),int((i - pole.n) * Height * 1.0 / pole.n),int(4.0 * Width / (5 * pole.n)),int(Height * 1.0 / pole.n) };
			if (pole.arr[i][j].color == 1) SDL_RenderCopy(renderer, Balls1Texture, NULL, &ball);
			if (pole.arr[i][j].color == 2) SDL_RenderCopy(renderer, Balls2Texture, NULL, &ball);
			if (pole.arr[i][j].color == 3) SDL_RenderCopy(renderer, Balls3Texture, NULL, &ball);
			if (pole.arr[i][j].color == 4) SDL_RenderCopy(renderer, Balls4Texture, NULL, &ball);
			if (pole.arr[i][j].color == 5) SDL_RenderCopy(renderer, Balls5Texture, NULL, &ball);
			if (pole.arr[i][j].color == -1) SDL_RenderCopy(renderer, BoomTexture, NULL, &ball);
		}
}

int search_hod(Array& pole)
{
	int flag = 0;
	for (int i = pole.n; i < pole.m; i++)
	{
		for (int j = 0; j < pole.n - 3; j++)
		{
			if (i == pole.n)
			{
				if (pole.arr[i][j].color == pole.arr[i][j + 1].color)
				{
					if (pole.arr[i][j + 1].color == pole.arr[i + 1][j + 2].color || pole.arr[i][j+1].color == pole.arr[i][j + 3].color) flag = 1;
				}
				
				if (pole.arr[i][j].color != pole.arr[i][j + 1].color)
				{
					if (pole.arr[i][j].color == pole.arr[i + 1][j + 1].color && pole.arr[i][j].color == pole.arr[i][j + 2].color 
						|| pole.arr[i][j].color == pole.arr[i][j + 2].color && pole.arr[i][j].color == pole.arr[i][j + 3].color) flag = 1;
				}
			}
			else
				if (i == pole.m - 1)
				{
					if (pole.arr[i][j].color == pole.arr[i][j + 1].color)
					{
						if (pole.arr[i][j + 1].color == pole.arr[i - 1][j + 2].color || pole.arr[i][j + 1].color == pole.arr[i][j + 3].color) flag = 1;
					}

					if (pole.arr[i][j].color != pole.arr[i][j + 1].color)
					{
						if (pole.arr[i][j].color == pole.arr[i - 1][j + 1].color && pole.arr[i][j].color == pole.arr[i][j + 2].color
							|| pole.arr[i][j].color == pole.arr[i][j + 2].color && pole.arr[i][j].color == pole.arr[i][j + 3].color) flag = 1;
					}
				}
			else
			{
					if (pole.arr[i][j].color == pole.arr[i][j + 1].color)
					{
						if (pole.arr[i][j + 1].color == pole.arr[i + 1][j + 2].color || pole.arr[i][j + 1].color == pole.arr[i - 1][j + 2].color 
							|| pole.arr[i][j + 1].color == pole.arr[i][j + 3].color) flag = 1;
					}

					if (pole.arr[i][j].color != pole.arr[i][j + 1].color)
					{
						if ((pole.arr[i][j].color == pole.arr[i + 1][j + 1].color || pole.arr[i][j].color == pole.arr[i - 1][j + 1].color)
							&& pole.arr[i][j].color == pole.arr[i][j + 2].color
							|| pole.arr[i][j].color == pole.arr[i][j + 2].color && pole.arr[i][j].color == pole.arr[i][j + 3].color) flag = 1;
					}
			}
		}
	}
	
	for (int i = 0; i < pole.n; i++)
	{
		for (int j = pole.n; j < pole.m - 3; j++)
		{
			if (i == 0)
			{
				if (pole.arr[j][i].color == pole.arr[j+1][i].color)
				{
					if (pole.arr[j+1][i].color == pole.arr[j + 2][i + 1].color || pole.arr[j+1][i].color == pole.arr[j+3][i].color) flag = 1;
				}

				if (pole.arr[j][i].color != pole.arr[j][i + 1].color)
				{
					if (pole.arr[j][i].color == pole.arr[j + 1][i + 1].color && pole.arr[j][i].color == pole.arr[j+2][i].color
						|| pole.arr[j][i].color == pole.arr[j+2][i].color && pole.arr[j][i].color == pole.arr[j+3][i].color) flag = 1;
				}
			}
			else
				if (i == pole.n - 1)
				{
					if (pole.arr[j][i].color == pole.arr[j+1][i].color)
					{
						if (pole.arr[j+1][i].color == pole.arr[j+2][i-1].color || pole.arr[j+1][i].color == pole.arr[j+3][i].color) flag = 1;
					}

					if (pole.arr[j][i].color != pole.arr[j][i + 1].color)
					{
						if (pole.arr[j][i].color == pole.arr[j+1][i-1].color && pole.arr[j][i].color == pole.arr[j+2][i].color
							|| pole.arr[j][i].color == pole.arr[j+2][i].color && pole.arr[j][i].color == pole.arr[j+3][i].color) flag = 1;
					}
				}
				else
				{
					if (pole.arr[j][i].color == pole.arr[j+1][i].color)
					{
						if (pole.arr[j+1][i].color == pole.arr[j +2][i + 1].color || pole.arr[j+1][i].color == pole.arr[j+2][i-1].color
							|| pole.arr[j+1][i].color == pole.arr[j+3][i].color) flag = 1;
					}

					if (pole.arr[j][i].color != pole.arr[j+1][i].color)
					{
						if ((pole.arr[j][i].color == pole.arr[j + 1][i + 1].color || pole.arr[j][i].color == pole.arr[j+1][i-1].color)
							&& pole.arr[j][i].color == pole.arr[j+2][i].color
							|| pole.arr[j][i].color == pole.arr[j+2][i].color && pole.arr[j][i].color == pole.arr[j+3][i].color) flag = 1;
					}
				}
		}
	}
	return flag;
}
int search_three(Array& pole)
{
	int flag = 0;
	int k = 1;
	for (int i = pole.n; i < pole.m; i++)
	{
		for (int j = 0; j < pole.n - 1; j++)
		{
			if (pole.arr[i][j].color != -1)
			{
				if (pole.arr[i][j].color == pole.arr[i][j + 1].color) k++;
				else k = 1;
				if ((pole.arr[i][j + 1].color != pole.arr[i][j + 2].color || j == pole.n - 2) && k == 3)
				{
					flag = 1;
					for (int l = j + 1; l >= j - k + 2; l--)
					{
						pole.arr[i][l].color = -1;
					}
					k = 1;
				}
				if ((pole.arr[i][j + 1].color != pole.arr[i][j + 2].color || j == pole.n - 2) && k == 4)
				{
					flag = 1;
					for (int a = 0; a < pole.n; a++)
						pole.arr[i][a].color = -1;
					k = 1;
				}
				if ((pole.arr[i][j + 1].color != pole.arr[i][j + 2].color || j == pole.n - 2) && k == 5)
				{
					flag = 1;
					for (int a = 0; a < pole.n; a++)
						pole.arr[i][a].color = -1;
					for (int b = pole.n; b < pole.n; b++)
						pole.arr[b][j - 1].color = -1;
					k = 1;
				}
				if ((pole.arr[i][j + 1].color != pole.arr[i][j + 2].color || j == pole.n - 2) && k == 6)
				{
					flag = 1;
					for (int a = 0; a < pole.n; a++)
						for (int b = pole.n; b < pole.n; b++)
							pole.arr[a][b].color = -1;
					k = 1;
				}
			}
		}
		k = 1;
	}

	k = 1;
	for (int i = 0; i < pole.n; i++)
	{
		for (int j = pole.n; j < pole.m - 1; j++)
		{
			if (pole.arr[j][i].color != -1)
			{
				if (pole.arr[j][i].color == pole.arr[j + 1][i].color) k++;
				else k = 1;
				if ((pole.arr[j + 1][i].color != pole.arr[j + 2][i].color || j == pole.m - 2) && k == 3)
				{
					flag = 1;
					for (int l = j + 1; l >= j - k + 2; l--)
					{
						pole.arr[l][i].color = -1;
					}
					k = 1;
				}
				if ((pole.arr[j + 1][i].color != pole.arr[j + 2][i].color || j == pole.m - 2) && k == 4)
				{
					flag = 1;
					for (int a = pole.n; a < pole.m; a++)
						pole.arr[a][i].color = -1;
					k = 1;
				}
				if ((pole.arr[j + 1][i].color != pole.arr[j + 2][i].color || j == pole.m - 2) && k == 5)
				{
					flag = 1;
					for (int a = pole.n; a < pole.m; a++)
						pole.arr[a][i].color = -1;
					for (int b = 0; b < pole.n; b++)
						pole.arr[j - 1][b].color = -1;
					k = 1;
				}
				if ((pole.arr[j + 1][i].color != pole.arr[j + 2][i].color || j == pole.m - 2) && k >= 6)
				{
					flag = 1;
					for (int a = pole.n; a < pole.m; a++)
						for (int b = 0; b < pole.n; b++)
							pole.arr[a][b].color = -1;
					k = 1;
				}
			}
		}
		k = 1;
	}
	return flag;
}
int search_three(Array& pole,int& points)
{
	int flag = 0;
	int k = 1;
	for (int i = pole.n; i < pole.m; i++)
	{
		for (int j = 0; j < pole.n - 1; j++)
		{
			if (pole.arr[i][j].color != -1)
			{
				if (pole.arr[i][j].color == pole.arr[i][j + 1].color) k++;
				else k = 1;
				if ((pole.arr[i][j + 1].color != pole.arr[i][j + 2].color || j == pole.n - 2) && k == 3)
				{
					flag = 1;
					for (int l = j + 1; l >= j - k + 2; l--)
					{
						pole.arr[i][l].color = -1;
					}
					k = 1;
					points += 3;
				}
				if ((pole.arr[i][j + 1].color != pole.arr[i][j + 2].color || j == pole.n - 2) && k == 4)
				{
					flag = 1;
					for (int a = 0; a < pole.n; a++)
						pole.arr[i][a].color = -1;
					k = 1;
					points += pole.n;
				}
				if ((pole.arr[i][j + 1].color != pole.arr[i][j + 2].color || j == pole.n - 2) && k == 5)
				{
					flag = 1;
					for (int a = 0; a < pole.n; a++)
						pole.arr[i][a].color = -1;
					for (int b = pole.n; b < pole.m; b++)
						pole.arr[b][j-1].color = -1;
					k = 1;
					points += 2*pole.n-1;
				}
				if ((pole.arr[i][j + 1].color != pole.arr[i][j + 2].color || j == pole.n - 2) && k == 6)
				{
					flag = 1;
					for (int a = 0; a < pole.n; a++)
						for (int b = pole.n; b < pole.n; b++)
							pole.arr[a][b].color = -1;
					k = 1;
					points += pole.n * pole.n;
				}
			}
		}
		k = 1;
	}
	
	k = 1;
	for (int i = 0; i < pole.n; i++)
	{
		for (int j = pole.n; j < pole.m - 1; j++)
		{
			if (pole.arr[j][i].color != -1)
			{
				if (pole.arr[j][i].color == pole.arr[j + 1][i].color) k++;
				else k = 1;
				if ((pole.arr[j + 1][i].color != pole.arr[j + 2][i].color || j == pole.m - 2) && k == 3)
				{
					flag = 1;
					for (int l = j + 1; l >= j - k + 2; l--)
					{
						pole.arr[l][i].color = -1;
					}
					k = 1;
					points += 3;
				}
				if ((pole.arr[j + 1][i].color != pole.arr[j + 2][i].color || j == pole.m - 2) && k ==4)
				{
					flag = 1;
					for (int a = pole.n; a < pole.m; a++)
						pole.arr[a][i].color = -1;
					k = 1;
					points += pole.n;
				}
				if ((pole.arr[j + 1][i].color != pole.arr[j + 2][i].color || j == pole.m - 2) && k == 5)
				{
					flag = 1;
					for (int a = pole.n; a < pole.m; a++)
						pole.arr[a][i].color = -1;
					for (int b = 0; b < pole.n; b++)
						pole.arr[j-1][b].color = -1;
					k = 1;
					points += 2 * pole.n - 1;
				}
				if ((pole.arr[j + 1][i].color != pole.arr[j + 2][i].color || j == pole.m - 2) && k >=6)
				{
					flag = 1;
					for (int a = pole.n; a < pole.m; a++)
						for (int b = 0; b < pole.n; b++)
							pole.arr[a][b].color = -1;
					k = 1;
					points += pole.n*pole.n;
				}
			}
		}
		k = 1;
	}
	return flag;
}

void move_balls(Array& pole, SDL_Renderer* &renderer, SDL_Texture* Balls1Texture, SDL_Texture* Balls2Texture,
	SDL_Texture* Balls3Texture, SDL_Texture* Balls4Texture, SDL_Texture* Balls5Texture, SDL_Texture* BoomTexture,int &points,int &StyleFlag,
	SDL_Texture* Balls11Texture, SDL_Texture* Balls21Texture, SDL_Texture* Balls31Texture, SDL_Texture* Balls41Texture, SDL_Texture* Balls51Texture)
{
	int k = 1;
	int temp;
	Array Mas;
	Mas.n = pole.n;
	Mas.m = pole.m;
	do{
		if (StyleFlag == 1)
			draw_pole_balls(renderer, pole, Balls1Texture, Balls2Texture, Balls3Texture, Balls4Texture, Balls5Texture,
				BoomTexture, -1, -1);
		else
			if (StyleFlag == 2)
				draw_pole_balls(renderer, pole, Balls11Texture, Balls21Texture, Balls31Texture, Balls41Texture, Balls51Texture,
					BoomTexture, -1, -1);

		SDL_RenderPresent(renderer);
		SDL_Delay(150);
		do{
			for (int i = pole.n; i < pole.m; i++)
				for (int j = 0; j < pole.n; j++)
					Mas.arr[i][j].color = pole.arr[i][j].color;

			for (int i = 0; i < pole.n; i++)
				for (int j = 0; j < pole.n; j++)
					Mas.arr[i][j].color = pole.arr[i][j].color = rand() % 5 + 1;

			//пробуем с Mas
			for (int x = 0; x < pole.n; x++)
			{
				for (int i = 0; i < pole.n; i++)	//столбец
				{
					for (int j = pole.n; j <= pole.m; j++)	//строка
					{
						if (Mas.arr[j][i].color == -1)
						{
							for (int a = j; a >= 1; a--)
							{
								Mas.arr[a][i].color = Mas.arr[a-1][i].color;
							}
							temp=Mas.arr[0][i].color = rand()%5+1;
							break;
						}
					}
				}
			}
		}while (!search_hod(Mas));
			
		for (int x = 0; x < pole.n; x++)
		{
			for (int i = 0; i < pole.n; i++)	//столбец
			{
				for (int j = pole.n; j <= pole.m; j++)	//строка
				{
					if (pole.arr[j][i].color == -1)
					{
						for (int a = j; a >= 1; a--)
						{
							pole.arr[a][i].color = pole.arr[a-1][i].color;
						}
						pole.arr[0][i].color = temp;
						break;
					}
				}
			}
			if(StyleFlag==1)
			draw_pole_balls(renderer, pole, Balls1Texture, Balls2Texture, Balls3Texture, Balls4Texture, Balls5Texture,
				BoomTexture, -1, -1);
			else 
			if(StyleFlag==2)
			draw_pole_balls(renderer, pole, Balls11Texture, Balls21Texture, Balls31Texture, Balls41Texture, Balls51Texture,
				BoomTexture, -1, -1);
			SDL_RenderPresent(renderer);
			SDL_Delay(80);
		}

	}while(search_three(pole,points));
}

void init_pole_balls(Array &pole)
{
	do {
		for (int i = pole.n; i < pole.m; i++)
			for (int j = 0; j < pole.n; j++)
			{
				pole.arr[i][j].color = rand() % 5 + 1;
			}
	} while (search_three(pole) || !search_hod(pole));
}

void GamePlay(Array &arr, SDL_Renderer* renderer,SDL_Texture* FonTexture, SDL_Texture* FonForPointsTexture,SDL_Texture* Balls1Texture, 
	SDL_Texture* Balls2Texture, SDL_Texture* Balls3Texture, SDL_Texture* Balls4Texture, SDL_Texture* Balls5Texture, SDL_Texture* BoomTexture,
	SDL_Texture* texture_title_points,SDL_Texture* texture_title_attemps,SDL_Texture* texture_points,
	SDL_Texture* texture_attemps, int i1, int j1)
{
	draw_fon_menu(renderer,FonTexture);
	draw_pole_balls(renderer,arr,Balls1Texture,Balls2Texture,Balls3Texture,Balls4Texture, Balls5Texture,BoomTexture, i1,j1);
	draw_fonForPoints(renderer, FonForPointsTexture);
	draw_title_points(renderer, texture_title_points);
	draw_text_points(renderer, texture_points);
	
	draw_title_attemps(renderer, texture_title_attemps);
	draw_text_attemps(renderer, texture_attemps);	
}