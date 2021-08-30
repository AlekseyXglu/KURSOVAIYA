#ifndef tableRecords_H
#define tableRecords_H
void inputRecords(FILE* f, int* mas, const char* arr);
void addRecord(int* mas, int& points);
void sort(int* mas);
void outputRecords(FILE* f, int* mas, const char* arr);
void draw_title_table_records(SDL_Renderer*& renderer, SDL_Texture* recordsTexture);
void TABLE_RECORDS(SDL_Renderer*& renderer, TTF_Font* game_font,SDL_Texture* FonTexture, SDL_Texture* title_recordsTexture, SDL_Texture* attempsRecords, FILE* f);


#endif
