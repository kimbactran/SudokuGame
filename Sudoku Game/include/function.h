#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED
#include <SDL.h>
#include <SDL_ttf.h>
#include "Sudoku.h"
#include "draw.h"
#include "init.h"


//Chức năng trò chơi chính
void getGridPos(int x, int y, int * i, int * j);
void clearActiveStates(board board[][COLS]);
void checkMove(board board[][COLS], int row, int col);
int condition(board board[][COLS]);


int condition(board board[][COLS])//ham kiem tra xem da thang chua
{
    for(int i=0;i<ROWS;i++)
    {
        for(int j=0;j<COLS;j++)
            {
                if(board[i][j].value==0) return 0;
            }
    }
    return 1;
}

//Khởi tạo mảng 2d của cấu trúc lát bằng bảng đã tải, khởi tạo luôn cả kết cấu.
bool initBoard(board board1[][COLS],board board2[][COLS], TTF_Font * fontFam, Sudoku *matrix) {
	int i, j;	//Biến lặp
	bool success = true; //Gắn cờ để tạo thành công
	int boardVals1[ROWS][COLS];
	int boardVals2[ROWS][COLS];

	matrix->createSeed();
	matrix->genPuzzle();
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            boardVals1[i][j]=matrix->grid[i][j];
            boardVals2[i][j]=matrix->solnGrid[i][j];
        }
    }
		//printBoard(boardVals);
		//Lặp lại từng ô trong mảng struct.
		for (i = 0; i < ROWS; i++) {
			for (j = 0; j < COLS; j++) {
				//Đang tải các giá trị vào cấu trúc.
				board1[i][j].value = boardVals1[i][j];
				board2[i][j].value = boardVals2[i][j];

				//Đặt trạng thái hoạt động mặc định của ô thành false.
				board1[i][j].isActive = false;
				board2[i][j].isActive = false;

				// Đặt trạng thái lỗi mặc định thành false.
				board1[i][j].isError = false;
				board2[i][j].isError = false;

				//Đặt trạng thái đã thay đổi thành false vì chúng không bị thay đổi..
				board1[i][j].changed = false;
				board2[i][j].changed = false;

				// Nếu giá trị khác không, hãy đặt kết cấu
				if(board1[i][j].value) {
					// Đặt trạng thái ban đầu thành true để không thể sửa đổi
					board1[i][j].isInitial = true;
				}
				else {
					//Đặt trạng thái ban đầu
					board1[i][j].isInitial = false;
				}

				// Đặt kết cấu
				board1[i][j].numTexture = numToText(board1[i][j].value, fontFam);

				//Khởi tạo thành viên SDL_Rect trong mỗi phần tử
				board1[i][j].square.x = 640 * j / 9 + 1;
				board1[i][j].square.y = 640 * i / 9 + 1;
				board1[i][j].square.w = 640 / 9 - 1;
				board1[i][j].square.h = 640 / 9 - 1;
				// Nếu giá trị khác không, hãy đặt kết cấu
				if(board2[i][j].value) {
					// Đặt trạng thái ban đầu thành true để không thể sửa đổi
					board2[i][j].isInitial = true;
				}
				else {
					//Đặt trạng thái ban đầu
					board2[i][j].isInitial = false;
				}

				// Đặt kết cấu
				board2[i][j].numTexture = numToText(board2[i][j].value, fontFam);

				//Khởi tạo thành viên SDL_Rect trong mỗi phần tử
				board2[i][j].square.x = 640 * j / 9 + 1;
				board2[i][j].square.y = 640 * i / 9 + 1;
				board2[i][j].square.w = 640 / 9 - 1;
				board2[i][j].square.h = 640 / 9 - 1;
			}

	}
	return success;
}

//Xác định hàng / cột lưới từ vị trí x và y của chuột
void getGridPos(int x, int y, int * i, int * j) {
	int k;

	//Tìm hàng
	for (k = 0; k < 9; k++) {
		if (y >= (k * 640 / 9) && y < ((k + 1) * 640 / 9) )
			*i = k;
	}

	// Tìm cột
	for (k = 0; k < 9; k++) {
		if (x >= (k * 640 / 9) && x < ((k + 1) * 640 / 9) )
			*j = k;
	}
}

//Xóa tất cả các trạng thái đang hoạt động trên bảng.
void clearActiveStates(board board[][COLS]) {
	int i, j;
	for (i = 0; i < ROWS; i++) {
		for (j = 0; j < COLS; j++){
			board[i][j].isActive = false;
		}
	}
}

// Kiểm tra đúng hàng, cột và tiểu mục để xem chữ số có được lặp lại hay không.
//	Gắn cờ cho ô tại [row] [col] là KHÔNG ĐÚNG nếu vậy
void checkMove(board board[][COLS], int row, int col) {
	int i, j, subrow, subcol;
	bool isFine = true;

	//Kiểm tra xem giá trị có khác không
	if (board[row][col].value) {
		// Kiểm tra các giá trị trong hàng của hình vuông đã cho
		for (j = 0; j < ROWS; j++) {
			if (board[row][j].value == board[row][col].value && j != col) {
				board[row][col].isError = true;
				printf("Row confliction!\n");
				isFine = false;
			}
		}

		//Kiểm tra các giá trị trong cột của hình vuông đã cho
		for (i = 0; i < COLS; i++) {
			if (board[i][col].value == board[row][col].value && i != row) {
				board[row][col].isError = true;
				printf("Column confliction!\n");
				isFine = false;
			}
		}

		//Kiểm tra subquare chứa giá trị [row] [col].
		subrow = row / 3;
		subcol = col / 3;
		for (i = 0; i < 3; i++) {
			for (j = 0; j < 3; j++) {
				if (board[row][col].value == board[subrow*3 + i][subcol*3 + j].value && (subrow*3 + i != row) && (subcol*3 + j != col)) {
					board[row][col].isError = true;
					printf("Subsquare confliction!\n");
					isFine = false;
				}
			}
		}
	}
	// Nếu không có lỗi, hãy đặt lại trạng thái lỗi thành false.
	// Hữu ích khi sửa lỗi trong bảng.
	if (isFine) {
		board[row][col].isError = false;
	}
}


#endif // FUNCTION_H_INCLUDED
