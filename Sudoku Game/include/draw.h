#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED

#define ROWS 9
#define COLS 9
#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 640
#define UNASSIGNED 0
#include <SDL.h>
#include <SDL_ttf.h>
#include "init.h"

using namespace std;


//Các hàm kết xuất
void renderNums(board board[][COLS], TTF_Font * font);
void renderColors(board board[][COLS]);
void drawGrid(void);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);
SDL_Texture * loadString(char * message, TTF_Font * font);
SDL_Texture * numToText(int num, TTF_Font * font);
SDL_Texture* myloadTexture(const std::string &file, SDL_Renderer *ren);

// Trả về kết cấu chứa một chuỗi có phông chữ ttf
SDL_Texture * loadString(char * message, TTF_Font * font) {
	//Màu đen cho văn bản
	SDL_Color Black = { 0, 0, 0 };

	//Kết cấu chứa thông báo mà chúng ta muốn trả về
	SDL_Texture *textOut = NULL;

	//Tạo bề mặt chứa thông báo
	SDL_Surface *surfaceMsg = NULL;

	surfaceMsg = TTF_RenderText_Solid(font, message, Black);
	if (surfaceMsg == NULL) {
		printf("Surface message could not be loaded! TTF Error: %s\n", TTF_GetError());
	}
	else {
		//Biến bề mặt có thông báo thành kết cấu
		textOut = SDL_CreateTextureFromSurface(myRender, surfaceMsg);
		if (textOut == NULL) {
			printf("Texture could not be created.\n");
		}
		SDL_FreeSurface(surfaceMsg);
	}
	return textOut;
}

//Trả về kết cấu có chứa một số từ phông chữ TTF đã cho.
SDL_Texture * numToText(int num, TTF_Font * font) {
	//Chuỗi chứa số. 10 cho sự an toàn.
	char number[10];

	SDL_Texture * numTextOut = NULL;

	//Chuyển đổi số nguyên, num, thành một chuỗi trong 'number'
	if (sprintf(number, "%d", num) < 0) {
		printf("Failed sprintf for some reason.\n");
	}
	else {
		numTextOut = loadString(number, font);
		if (numTextOut == NULL) {
			printf("There were errors in numToText. Error: %s\n", SDL_GetError());
		}
	}
	return numTextOut;
}

// Cập nhật bảng với các ô
void renderNums(board board[][COLS], TTF_Font * font) {
		// Kết xuất các số ban đầu
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				//Nếu số tại ô vuông đó là giá trị khác không.
				if (board[i][j].value) {
					// Nếu giá trị bị thay đổi bởi một sự kiện
					if (board[i][j].changed) {
						//Hủy kết cấu cũ
						SDL_DestroyTexture(board[i][j].numTexture);

						// Tạo một kết cấu mới
						board[i][j].numTexture = numToText(board[i][j].value, font);

						// Kết cấu đã được cập nhật nên không cần thay đổi nữa.
						board[i][j].changed = false;
					}
					// Kết xuất kết cấu vào vùng đệm phía sau theo đúng ô.
					SDL_RenderCopy(myRender, board[i][j].numTexture, NULL, &(board[i][j].square));
				}
			}
		}
}

// Vẽ lưới đen trên bảng
void drawGrid(void) {
	int i;

	//Đặt màu của trình kết xuất thành màu đen
	SDL_SetRenderDrawColor(myRender, 0, 0, 0, 0xFF);

	// Vẽ các đường thẳng đứng
	for (i = 0; i <= 9; i++) {
		if (i % 3 == 0 && i != 0 && i != 9) {
			SDL_RenderDrawLine(myRender, 640 * i / 9 - 1, 0, 640 * i / 9 - 1, 640);
			SDL_RenderDrawLine(myRender, 640 * i / 9 + 1, 0, 640 * i / 9 + 1, 640);
		}
		else if (i == 9) {
			SDL_RenderDrawLine(myRender, 640 * i / 9 - 1, 0, 640 * i / 9 - 1, 640);
		}
		SDL_RenderDrawLine(myRender, 640 * i / 9, 0, 640 * i / 9, 640);
	}

	//Các đường ngang
	for (i = 0; i <= 9; i++) {
		if (i % 3 == 0 && i != 0 && i != 9) {
			SDL_RenderDrawLine(myRender, 0, 640 * i / 9 - 1, 640, 640 * i / 9 - 1);
			SDL_RenderDrawLine(myRender, 0, 640 * i / 9 + 1, 640, 640 * i / 9 + 1);
		}
		else if (i == 9) {
			SDL_RenderDrawLine(myRender, 0, 640 * i / 9 - 1, 640, 640 * i / 9 - 1);
		}
		SDL_RenderDrawLine(myRender, 0, 640 * i / 9, 640, 640 * i / 9);
	}
}
// Điền màu của mỗi ô bằng một color thích hợp dựa trên trạng thái của nó.
void renderColors(board board[][COLS]) {
	int i, j;	//Các biến lập chỉ mục

	//Vòng qua bảng và tô màu của hình chữ nhật dựa trên trạng thái của ô.
	for (i = 0; i < ROWS; i++) {
		for (j = 0; j < COLS; j++) {
			// Nếu ô là ô ban đầu, hãy tô màu xanh lam
			if (board[i][j].isInitial) {
				SDL_SetRenderDrawColor(myRender, 153, 187, 255, 255);
				SDL_RenderFillRect(myRender, &(board[i][j].square));
			}
			// Nếu ô đang hoạt động, hãy tô màu vàng
			else if (board[i][j].isActive) {
				if (board[i][j].isError) {
					SDL_SetRenderDrawColor(myRender, 232, 130, 99, 255);
				}
				else {
					SDL_SetRenderDrawColor(myRender, 232, 214, 99, 255);
				}
				SDL_RenderFillRect(myRender, &(board[i][j].square));
			}
			// Nếu ô bị lỗi, hãy tô màu đỏ
			else if (board[i][j].isError) {
				SDL_SetRenderDrawColor(myRender, 237, 87, 87, 255);
				SDL_RenderFillRect(myRender, &(board[i][j].square));
			}
			// Không có điều kiện nào khác vì trình kết xuất tự động xóa tất cả các lệnh thành màu trắng mỗi vòng lặp.
		}
	}
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y)
{
	//Thiết lập hình chữ nhật đích mà chúng ta muốn vẽ ảnh vào trong
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	//Truy vẫn texture để lấy chiều rộng và cao (vào chiều rộng và cao tương ứng của hình chữ nhật đích)
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    //Đưa toàn bộ ảnh trong texture vào hình chữ nhật đích
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h)
{
	//Thiết lập hình chữ nhật đích mà chúng ta muốn vẽ ảnh vào trong
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
    dst.w = w;
    dst.h = h;
    //Đưa toàn bộ ảnh trong texture vào hình chữ nhật đích
    //(ảnh sẽ co dãn cho khớp với kích cỡ mới)
	SDL_RenderCopy(ren, tex, NULL, &dst);
}
SDL_Texture* myloadTexture(const std::string &file, SDL_Renderer *ren)
{
	//Khởi tạo là nullptr để tránh lỗi 'dangling pointer'
	SDL_Texture *texture = nullptr;
	//Nạp ảnh từ tên file (với đường dẫn)
	SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());
	//Nếu không có lỗi, chuyển đổi về dạng texture and và trả về
	if (loadedImage != nullptr){
		texture = SDL_CreateTextureFromSurface(ren, loadedImage);
		SDL_FreeSurface(loadedImage);
		//Đảm bảo việc chuyển đổi không có lỗi
		if (texture == nullptr){
			logSDLError(std::cout, "CreateTextureFromSurface");
		}
	}
	else {
		logSDLError(std::cout, "LoadBMP");
	}
	return texture;
}

#endif // DRAW_H_INCLUDED
