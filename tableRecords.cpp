#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Menu.h"
#include "tableRecords.h"
extern int Width;
extern int Height;
void inputRecords(FILE* f, int* mas, const char* arr)
{
	int i = 0;
	fopen_s(&f, arr, "r");
	while (!feof(f))
	{
		fscanf_s(f, "%d", &mas[i]);
		//if (mas[i] > 0) nRecords++;
		i++;
	}
	fclose(f);
}
void addRecord(int* mas, int& points)
{
	int min = mas[0];
	int k = 0;
	for (int i = 1; i < 5; i++)
		if (mas[i] <= min)
		{
			k = i;
			min = mas[i];
		}
	if (mas[k] < points) mas[k] = points;
	//if (nRecords < 5) nRecords++;
}
void sort(int* mas)
{
	int temp;
	for (int i = 0; i < 4; i++)
		for (int j = i + 1; j < 5; j++)
			if (mas[i] < mas[j])
			{
				temp = mas[i];
				mas[i] = mas[j];
				mas[j] = temp;
			}
}
void outputRecords(FILE* f, int* mas, const char* arr)
{
	fopen_s(&f, arr, "w");
	for (int i = 0; i < 5; i++)
	{
		fprintf_s(f, "%d\n", mas[i]);
	}
	fclose(f);
}

void draw_title_table_records(SDL_Renderer*& renderer, SDL_Texture* recordsTexture)
{
	SDL_Rect title_table_records_Rect = { Width / 3,Height / 20,Width / 3,Height / 10 };
	SDL_RenderCopy(renderer, recordsTexture, NULL, &title_table_records_Rect);
}

void TABLE_RECORDS(SDL_Renderer*& renderer,TTF_Font* game_font, SDL_Texture* FonTexture, SDL_Texture* title_recordsTexture, SDL_Texture* attempsRecords,FILE* f)
{
	SDL_RenderClear(renderer);
	draw_fon_menu(renderer, FonTexture);
	draw_title_table_records(renderer, title_recordsTexture);
	int mas[5];
	char text_record[10];
	
	SDL_Rect recordRect={ 0,0,0,0 };
	SDL_Texture* record=get_text_texture(renderer, "", game_font);;
	SDL_Texture* recordPole= get_text_texture(renderer, "", game_font);;
	SDL_Texture* recordAttemps= get_text_texture(renderer, "", game_font);;
	for (int j = 0; j < 9; j++)
	{
		switch (j)
		{
			case 0:inputRecords(f, mas, "10x7.txt"); recordPole= get_text_texture(renderer, "7x7", game_font);
				recordAttemps = get_text_texture(renderer, "10 att.", game_font);  break;
			case 1:inputRecords(f, mas, "20x7.txt"); recordPole = get_text_texture(renderer, "7x7", game_font);
				recordAttemps = get_text_texture(renderer, "20 att.", game_font);  break;
			case 2:inputRecords(f, mas, "30x7.txt"); recordPole = get_text_texture(renderer, "7x7", game_font);
				recordAttemps = get_text_texture(renderer, "30 att.", game_font);  break;
			case 3:inputRecords(f, mas, "10x8.txt"); recordPole = get_text_texture(renderer, "8x8", game_font);
				recordAttemps = get_text_texture(renderer, "10 att.", game_font);  break;
			case 4:inputRecords(f, mas, "20x8.txt"); recordPole = get_text_texture(renderer, "8x8", game_font);
				recordAttemps = get_text_texture(renderer, "20 att.", game_font);  break;
			case 5:inputRecords(f, mas, "30x8.txt"); recordPole = get_text_texture(renderer, "8x8", game_font);
				recordAttemps = get_text_texture(renderer, "30 att.", game_font);  break;
			case 6:inputRecords(f, mas, "10x9.txt"); recordPole = get_text_texture(renderer, "9x9", game_font);
				recordAttemps = get_text_texture(renderer, "10 att.", game_font);  break;
			case 7:inputRecords(f, mas, "20x9.txt"); recordPole = get_text_texture(renderer, "9x9", game_font);
				recordAttemps = get_text_texture(renderer, "20 att.", game_font);  break;
			case 8:inputRecords(f, mas, "30x9.txt"); recordPole = get_text_texture(renderer, "9x9", game_font);
				recordAttemps = get_text_texture(renderer, "30 att.", game_font);  break;
		}
		recordRect.x = Width / 9 * j;
		recordRect.y =3*Height/18 ;
		recordRect.w = Width / 12;
		recordRect.h = Height / 15;
		SDL_RenderCopy(renderer, recordPole, NULL, &recordRect);
		recordRect.x = Width / 9 * j;
		recordRect.y = 6 * Height / 25;
		recordRect.w = Width / 12;
		recordRect.h = Height / 15;
		SDL_RenderCopy(renderer, recordAttemps, NULL, &recordRect);
		
		for (int i = 0; i < 5; i++)
		{
			recordRect.x = Width / 9 * j;
			recordRect.y = 3*Height / 10 + 3 * Height / 25 * i;
			recordRect.w = Width / 15;
			recordRect.h = 3 * Height / 25;
			SDL_DestroyTexture(record);
			if (mas[i] != -1)
			{
				_itoa_s(mas[i], text_record, 10);
				record = get_text_texture(renderer, text_record, game_font);
			}
			else
			{
				record = get_text_texture(renderer, " - ", game_font);
			}
			SDL_RenderCopy(renderer, record, NULL, &recordRect);
		}
		SDL_DestroyTexture(record);
		SDL_DestroyTexture(recordPole);
		SDL_DestroyTexture(recordAttemps);
	}
}

