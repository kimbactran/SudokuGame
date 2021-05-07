#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

#include "Sudoku.h"

using namespace std;
//Các biến toàn cục được truy cập phổ biến
//	Các biến bắt đầu bằng 'my' có thể truy cập được trên toàn cầu.
SDL_Window * myWindow = NULL;	//Cửa sổ chúng ta sẽ sử dụng
SDL_Renderer * myRender = NULL;	//Trình kết xuất cửa sổ
const string WINDOW_TITLE = "Game Sudoku";

// Kiểu dữ liệu xếp lớp. Chứa giá trị sudoku, trạng thái của vị trí và kích thước hình vuông, hình chữ nhật và kết cấu
typedef struct {
	int value;		//giá trị số được lưu trữ trong ô
	bool isInitial;	//Cái này đã được tải ban đầu chưa? Nó có thể được sửa đổi?
	bool isActive;	//Ô có hoạt động không, tức là nó đã được nhấp vào chưa?
	bool isError;	//Có đúng ô không? Có xung đột luật chơi không?
	bool changed;	//Thay đổi cờ để cập nhật kết cấu số
	SDL_Rect square;	//Hình chữ nhật chứa vị trí và kích thước của mỗi ô
	SDL_Texture * numTexture;	//Con trỏ đến kết cấu cho số trong ô
} board;

bool initSDL();
bool initBoard(board board[][COLS], TTF_Font * fontFam);
void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);


//Khởi tạo SDL và các thư viện
bool initSDL() {
	bool success = true; //Init cờ

	//Initalize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL failed to initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		//Tạo cửa sổ
		myWindow = SDL_CreateWindow( "Sudoku Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

		if (myWindow == NULL) {
			printf("Window couldn't be created! SDL error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			//Tạo trình kết xuất cửa sổ
			myRender = SDL_CreateRenderer(myWindow, -1, SDL_RENDERER_ACCELERATED);
			if (myRender == NULL) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else {
				//Khởi tạo màu của trình kết xuất
				SDL_SetRenderDrawColor(myRender, 0xFF, 0xFF, 0xFF, 0xFF);

				//Khởi tạo SDL_ttf
				if (TTF_Init() == -1) {
					printf("SDL_ttf failed to initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}
	return success;
}



void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
}


#endif // INIT_H_INCLUDED
