#include "function.h"
#include "draw.h"
#include "init.h"

int main(int argc, char * argv[])
{
   //Bảng Sudoku, được lưu trữ dưới dạng mảng 2d của cấu trúc ô.
	board mainboard[ROWS][COLS];
	board extraboard[ROWS][COLS];

	//Cờ vòng lặp chính
	bool quit = false;

	// Trình xử lý sự kiện
	SDL_Event e;

	//Phông chữ TTF được sử dụng để hiển thị văn bản và số
	//sudoku maxtrix;
	TTF_Font *myFont = NULL;

    if (!initSDL()) {
		printf("Error! Failed to initialize!\n");
	}
	else {
		//Biến chỉ mục cho các sự kiện chuột và bàn phím.
		int i = 100, j = 100;

		//Gắn cờ cho một ô đang hoạt động.
		bool tileActive = false;

		//Đang tải một phông chữ được chỉ định vào biến TTF_Font.
		myFont = TTF_OpenFont("FontNumber.ttf", 100);

		if (myFont == NULL) {
			printf("Font could not be located! TTF error: %s", TTF_GetError());
			quit = true;
		}
		SDL_Texture *background1 = myloadTexture("image\\bautroi.bmp", myRender);
		SDL_Texture *background2 = myloadTexture("image\\man_hinh_game_chinh.bmp", myRender);
		SDL_Texture *background3 = myloadTexture("image\\chuc_mung.bmp", myRender);
        SDL_Texture *image1 = myloadTexture("image\\menu_de.bmp", myRender);
        SDL_Texture *image2 = myloadTexture("image\\menu_trung_binh.bmp", myRender);
        SDL_Texture *image3 = myloadTexture("image\\menu_kho.bmp", myRender);
        SDL_Texture *image4 = myloadTexture("image\\menu_huong_dan.bmp", myRender);
        SDL_Texture *image5 = myloadTexture("image\\menu_thoat.bmp", myRender);
        SDL_Texture *image6 = myloadTexture("image\\menu_game_moi.bmp", myRender);
        SDL_Texture *image7 = myloadTexture("image\\menu_dap_an.bmp", myRender);
        SDL_Texture *huongdan = myloadTexture("image\\huong_dan_choi.bmp", myRender);

        if (background1 == nullptr ||background2 == nullptr || image1 == nullptr|| huongdan == nullptr
             || image2 == nullptr ||image3 == nullptr|| image4 == nullptr|| image5 == nullptr||image6 == nullptr||image7 == nullptr){
            SDL_DestroyTexture(background1);
            SDL_DestroyTexture(background2);
            SDL_DestroyTexture(image1);
            SDL_DestroyTexture(image2);
            SDL_DestroyTexture(image3);
            SDL_DestroyTexture(image4);
            SDL_DestroyTexture(image5);
            SDL_DestroyTexture(image6);
            SDL_DestroyTexture(image7);
            SDL_DestroyTexture(huongdan);
            quitSDL(myWindow, myRender);
        }
		// Vòng lặp chính
		while (!quit)
        {
            SDL_RenderClear(myRender);
            renderTexture(background2, myRender, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
            int iW, iH;
            SDL_QueryTexture(image1, NULL, NULL, &iW, &iH);
            int x1 = SCREEN_WIDTH / 2 - iW / 2;
            int y1 = 150;
            renderTexture(image1, myRender, x1, y1);
            int y2=y1+iH;
            renderTexture(image2, myRender, x1, y2);
            int y3=y2+iH;
            renderTexture(image3, myRender, x1, y3);
            int y4=y3+iH;
            renderTexture(image4, myRender, x1, y4);
            SDL_RenderPresent(myRender);
            int tutorial=1;
            int easy=1;
            int medium=1;
            int hard=1;
            int a1 = 770- iW / 2;;
            int b1 =250;
            int b2=b1+iH;
            int b3=b2+iH;
            SDL_Delay(10);
            if ( SDL_WaitEvent(&e) == 0) continue;
            if (e.type == SDL_QUIT) break;
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) break;
            if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
            {
                int x,y;
                SDL_GetMouseState(&x, &y);
                if((x>=(SCREEN_WIDTH / 2 - iW / 2)&&x<=(SCREEN_WIDTH / 2 + iW / 2))&&(y>=y4&& y<=y4+iH))
                {
                    while(tutorial)
                    {
                        renderTexture(huongdan, myRender, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                        renderTexture(image5, myRender, 400, 500);
                        SDL_RenderPresent(myRender);
                        SDL_Delay(10);
                        if ( SDL_WaitEvent(&e) == 0) continue;
                        if (e.type == SDL_QUIT) break;
                        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) break;
                        if (e.type == SDL_MOUSEBUTTONDOWN)
                        {
                            int m,n;
                            SDL_GetMouseState(&m, &n);
                            if(m>=400&&m<=400+iW&&n>=500&&n<=500+iH) tutorial=0;
                            if(tutorial==0 ) break;
                            else continue;
                        }
                    }
                }
                else if((x>=(SCREEN_WIDTH / 2 - iW / 2)&&x<=(SCREEN_WIDTH / 2 + iW / 2))&&(y>=y1&& y<=y1+iH))
                {
                    Sudoku *maxtrix = new Sudoku();
                    maxtrix->level=1;
                    if ( !initBoard(mainboard, extraboard, myFont, maxtrix) ) {
                        printf("Error! Failed to initialize board!\n");
                        quit = true;
                    }

                    while(easy){
                    // Bỏ phiếu cho các sự kiện trong bộ đệm sự kiện
                        while (SDL_PollEvent(&e) != 0) {
                            // Nếu ứng dụng bị đóng
                            if (e.type == SDL_QUIT) break;
                            // Nếu một phím chuột được nhấp vào
                            else if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
                                int x, y;

                                //Lấy vị trí chuột x và y
                                SDL_GetMouseState(&x, &y);

                                //Chuyển vị trí chuột thành các chỉ báo lưới.
                                getGridPos(x, y, &i, &j);

                                //Đặt tất cả các ô thành không hoạt động
                                clearActiveStates(mainboard);

                                //Thay đổi ô hiện tại thành trạng thái hoạt động để ô này được đánh dấu sau này
                                if (e.button.button == SDL_BUTTON_LEFT){
                                    mainboard[i][j].isActive = true;
                                    tileActive = true;
                                }
                                //Nhấp chuột phải làm cho ô không hoạt động
                                else {
                                    //Loại bỏ câu lệnh if này
                                    if (mainboard[i][j].isActive) {
                                        mainboard[i][j].isActive = false;
                                    }
                                    tileActive = false;
                                }
                                if (tileActive) {
                                    checkMove(mainboard, i, j);
                                }
                            }
                            //Một phím được nhấn và một ô trước đó đã được chọn
                            else if (e.type == SDL_KEYDOWN && tileActive) {
                                //Thay đổi số dựa trên phím bấm
                                for (int k = 0; k < 10; k++) {
                                    //Nếu khóa là một chữ số
                                    if ( (e.key.keysym.sym == SDLK_0 + k) || (e.key.keysym.sym == SDLK_DELETE) || (e.key.keysym.sym == SDLK_SPACE) || (e.key.keysym.sym == SDLK_BACKSPACE) ) {
                                        // Nếu nó không phải là trạng thái ban đầu
                                        if (mainboard[i][j].isInitial == false) {
                                            mainboard[i][j].value = k;

                                            //Cập nhật cờ cho renderNums
                                            mainboard[i][j].changed = true;

                                            //Kiểm tra xem việc di chuyển có hợp lệ không và đặt trạng thái của ô cho phù hợp
                                            checkMove(mainboard, i, j);
                                            break;
                                        }
                                    }
                                }
                            }
                        }

                    //Xóa màn hình
                    SDL_SetRenderDrawColor(myRender, 255, 255, 255, 255);
                    SDL_RenderClear(myRender);



                    //Hiển thị màu của từng ô dựa trên trạng thái của nó
                    renderTexture(background1, myRender, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                    renderTexture(image6, myRender, a1, b1);
                    renderTexture(image7, myRender, a1, b2);
                    renderTexture(image5, myRender, a1, b3);

                    renderColors(mainboard);

                    // Hiển thị trạng thái bảng hiện tại
                    renderNums(mainboard, myFont);
                                //Vẽ lưới
                    drawGrid();

                    //Cập nhật màn hình
                    SDL_RenderPresent(myRender);
                    int easy_answer=1;
                    if (e.type == SDL_MOUSEBUTTONDOWN)
                    {
                        int m,n;
                        SDL_GetMouseState(&m, &n);
                        if((m>=a1&&m<=a1+iW&&n>=b1&&n<=b1+iH)||(m>=a1&&m<=a1+iW&&n>=b3&&n<=b3+iH))
                        {
                            easy=0;
                        }
                        if((m>=a1&&m<=a1+iW&&n>=b2&&n<=b2+iH))
                        {

                            while(easy_answer){

                            renderTexture(background1, myRender, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                            renderTexture(image5, myRender, a1, b3);
                            renderColors(extraboard);
                            renderNums(extraboard, myFont);
                            drawGrid();
                            SDL_RenderPresent(myRender);
                            SDL_Delay(10);
                            if ( SDL_WaitEvent(&e) == 0) continue;
                            if (e.type == SDL_QUIT) break;
                            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) break;
                            if (e.type == SDL_MOUSEBUTTONDOWN)
                            {
                                int p, q;
                                SDL_GetMouseState(&p, &q);
                                if((p>=a1&&p<=a1+iW&&q>=b3&&q<=b3+iH))
                                {
                                    easy_answer=0;
                                    break;

                                }
                            }
                            }
                        }

                    }
                    if(condition(mainboard)==1)
                    {
                        renderTexture(background3, myRender, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                        renderTexture(image6, myRender, 600, 400);
                        SDL_RenderPresent(myRender);
                        while(true)
                        {
                            SDL_Delay(10);
                            if ( SDL_WaitEvent(&e) == 0) continue;
                            if (e.type == SDL_QUIT) break;
                            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) break;
                            if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
                            {
                                int p, q;
                                SDL_GetMouseState(&p, &q);
                                if((p>=600&&p<=600+iW&&q>=400&&q<=400+iH))
                                {
                                    break;

                                }
                            }
                        }
                    }
                    if(easy==0) break;
                    }
                }
                else if((x>=(SCREEN_WIDTH / 2 - iW / 2)&&x<=(SCREEN_WIDTH / 2 + iW / 2))&&(y>=y2&& y<=y2+iH))
                {
                    Sudoku *maxtrix = new Sudoku();
                    maxtrix->level=2;
                    if ( !initBoard(mainboard, extraboard, myFont, maxtrix) ) {
                        printf("Error! Failed to initialize board!\n");
                        quit = true;
                    }
                    while(medium){
                        // Bỏ phiếu cho các sự kiện trong bộ đệm sự kiện
                        while (SDL_PollEvent(&e) != 0) {
                            // Nếu ứng dụng bị đóng
                            if (e.type == SDL_QUIT) break;
                            // Nếu một phím chuột được nhấp vào
                            else if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
                                int x, y;

                                //Lấy vị trí chuột x và y
                                SDL_GetMouseState(&x, &y);

                                //Chuyển vị trí chuột thành các chỉ báo lưới.
                                getGridPos(x, y, &i, &j);

                                //Đặt tất cả các ô thành không hoạt động
                                clearActiveStates(mainboard);

                                //Thay đổi ô hiện tại thành trạng thái hoạt động để ô này được đánh dấu sau này
                                if (e.button.button == SDL_BUTTON_LEFT){
                                    mainboard[i][j].isActive = true;
                                    tileActive = true;
                                }
                                //Nhấp chuột phải làm cho ô không hoạt động
                                else {
                                    //Loại bỏ câu lệnh if này
                                    if (mainboard[i][j].isActive) {
                                        mainboard[i][j].isActive = false;
                                    }
                                    tileActive = false;
                                }
                                if (tileActive) {
                                    checkMove(mainboard, i, j);
                                }
                            }
                            //Một phím được nhấn và một ô trước đó đã được chọn
                            else if (e.type == SDL_KEYDOWN && tileActive) {
                                //Thay đổi số dựa trên phím bấm
                                for (int k = 0; k < 10; k++) {
                                    //Nếu khóa là một chữ số
                                    if ( (e.key.keysym.sym == SDLK_0 + k) || (e.key.keysym.sym == SDLK_DELETE) || (e.key.keysym.sym == SDLK_SPACE) || (e.key.keysym.sym == SDLK_BACKSPACE) ) {
                                        // Nếu nó không phải là trạng thái ban đầu
                                        if (mainboard[i][j].isInitial == false) {
                                            mainboard[i][j].value = k;

                                            //Cập nhật cờ cho renderNums
                                            mainboard[i][j].changed = true;

                                            //Kiểm tra xem việc di chuyển có hợp lệ không và đặt trạng thái của ô cho phù hợp
                                            checkMove(mainboard, i, j);
                                            break;
                                        }
                                    }
                                }
                            }
                        }

                    //Xóa màn hình
                    SDL_SetRenderDrawColor(myRender, 255, 255, 255, 255);
                    SDL_RenderClear(myRender);
                    //Hiển thị màu của từng ô dựa trên trạng thái của nó
                    renderTexture(background1, myRender, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                    renderTexture(image6, myRender, a1, b1);
                    renderTexture(image7, myRender, a1, b2);
                    renderTexture(image5, myRender, a1, b3);

                    renderColors(mainboard);
                    // Hiển thị trạng thái bảng hiện tại
                    renderNums(mainboard, myFont);
                                //Vẽ lưới
                    drawGrid();

                    //Cập nhật màn hình
                    SDL_RenderPresent(myRender);
                    int average_answer=1;
                    if (e.type == SDL_MOUSEBUTTONDOWN)
                    {
                        int m,n;
                        SDL_GetMouseState(&m, &n);
                        if((m>=a1&&m<=a1+iW&&n>=b1&&n<=b1+iH)||(m>=a1&&m<=a1+iW&&n>=b3&&n<=b3+iH))
                        {
                            medium=0;
                        }
                        if((m>=a1&&m<=a1+iW&&n>=b2&&n<=b2+iH))
                        {

                            while(average_answer){

                            renderTexture(background1, myRender, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                            renderTexture(image5, myRender, a1, b3);
                            renderColors(extraboard);
                            renderNums(extraboard, myFont);
                            drawGrid();
                            SDL_RenderPresent(myRender);
                            SDL_Delay(10);
                            if ( SDL_WaitEvent(&e) == 0) continue;
                            if (e.type == SDL_QUIT) break;
                            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) break;
                            if (e.type == SDL_MOUSEBUTTONDOWN)
                            {
                                int p, q;
                                SDL_GetMouseState(&p, &q);
                                if((p>=a1&&p<=a1+iW&&q>=b3&&q<=b3+iH))
                                {
                                    average_answer=0;
                                    break;
                                }
                            }
                            }
                        }

                    }
                    if(condition(mainboard)==1)
                    {
                        renderTexture(background3, myRender, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                        renderTexture(image6, myRender, 600, 400);
                        SDL_RenderPresent(myRender);
                        while(true)
                        {
                            SDL_Delay(10);
                            if ( SDL_WaitEvent(&e) == 0) continue;
                            if (e.type == SDL_QUIT) break;
                            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) break;
                            if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
                            {
                                int p, q;
                                SDL_GetMouseState(&p, &q);
                                if((p>=600&&p<=600+iW&&q>=400&&q<=400+iH))
                                {
                                    break;

                                }
                            }
                        }
                    }
                    if(medium==0) break;
                    }
                }
                else if((x>=(SCREEN_WIDTH / 2 - iW / 2)&&x<=(SCREEN_WIDTH / 2 + iW / 2))&&(y>=y3&& y<=y3+iH))
                {
                    Sudoku *maxtrix = new Sudoku();
                    maxtrix->level=3;
                    if ( !initBoard(mainboard, extraboard, myFont, maxtrix) ) {
                        printf("Error! Failed to initialize board!\n");
                        quit = true;
                    }
                    while(hard){
                        // Bỏ phiếu cho các sự kiện trong bộ đệm sự kiện
                        while (SDL_PollEvent(&e) != 0) {
                            // Nếu ứng dụng bị đóng
                            if (e.type == SDL_QUIT) break;

                            // Nếu một phím chuột được nhấp vào
                            else if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
                                int x, y;

                                //Lấy vị trí chuột x và y
                                SDL_GetMouseState(&x, &y);

                                //Chuyển vị trí chuột thành các chỉ báo lưới.
                                getGridPos(x, y, &i, &j);

                                //Đặt tất cả các ô thành không hoạt động
                                clearActiveStates(mainboard);

                                //Thay đổi ô hiện tại thành trạng thái hoạt động để ô này được đánh dấu sau này
                                if (e.button.button == SDL_BUTTON_LEFT){
                                    mainboard[i][j].isActive = true;
                                    tileActive = true;
                                }
                                //Nhấp chuột phải làm cho ô không hoạt động
                                else {
                                    //Loại bỏ câu lệnh if này
                                    if (mainboard[i][j].isActive) {
                                        mainboard[i][j].isActive = false;
                                    }
                                    tileActive = false;
                                }
                                if (tileActive) {
                                    checkMove(mainboard, i, j);
                                }
                            }
                            //Một phím được nhấn và một ô trước đó đã được chọn
                            else if (e.type == SDL_KEYDOWN && tileActive) {
                                //Thay đổi số dựa trên phím bấm
                                for (int k = 0; k < 10; k++) {
                                    //Nếu khóa là một chữ số
                                    if ( (e.key.keysym.sym == SDLK_0 + k) || (e.key.keysym.sym == SDLK_DELETE) || (e.key.keysym.sym == SDLK_SPACE) || (e.key.keysym.sym == SDLK_BACKSPACE) ) {
                                        // Nếu nó không phải là trạng thái ban đầu
                                        if (mainboard[i][j].isInitial == false) {
                                            mainboard[i][j].value = k;

                                            //Cập nhật cờ cho renderNums
                                            mainboard[i][j].changed = true;

                                            //Kiểm tra xem việc di chuyển có hợp lệ không và đặt trạng thái của ô cho phù hợp
                                            checkMove(mainboard, i, j);
                                            break;
                                        }
                                    }
                                }
                            }
                        }

                    //Xóa màn hình
                    SDL_SetRenderDrawColor(myRender, 255, 255, 255, 255);
                    SDL_RenderClear(myRender);



                    //Hiển thị màu của từng ô dựa trên trạng thái của nó
                    renderTexture(background1, myRender, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                    renderTexture(image6, myRender, a1, b1);
                    renderTexture(image7, myRender, a1, b2);
                    renderTexture(image5, myRender, a1, b3);

                    renderColors(mainboard);

                    // Hiển thị trạng thái bảng hiện tại
                    renderNums(mainboard, myFont);
                                //Vẽ lưới
                    drawGrid();

                    //Cập nhật màn hình
                    SDL_RenderPresent(myRender);
                    int difficult_answer=1;
                    //if (e.type == SDL_QUIT) break;
                    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) break;
                    if (e.type == SDL_MOUSEBUTTONDOWN)
                    {

                        int m,n;
                        SDL_GetMouseState(&m, &n);
                        if((m>=a1&&m<=a1+iW&&n>=b1&&n<=b1+iH)||(m>=a1&&m<=a1+iW&&n>=b3&&n<=b3+iH))
                        {
                            hard=0;
                        }

                        if((m>=a1&&m<=a1+iW&&n>=b2&&n<=b2+iH))
                        {

                            while(difficult_answer){

                            renderTexture(background1, myRender, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                            renderTexture(image5, myRender, a1, b3);
                            renderColors(extraboard);
                            renderNums(extraboard, myFont);
                            drawGrid();
                            SDL_RenderPresent(myRender);
                            SDL_Delay(10);
                            if ( SDL_WaitEvent(&e) == 0) continue;
                            if (e.type == SDL_QUIT) break;
                            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) break;
                            if (e.type == SDL_MOUSEBUTTONDOWN)
                            {
                                int p, q;
                                SDL_GetMouseState(&p, &q);
                                if((p>=a1&&p<=a1+iW&&q>=b3&&q<=b3+iH))
                                {
                                    difficult_answer=0;
                                    break;

                                }
                            }
                            }
                        }

                    }
                    if(hard==0) break;
                    if(condition(mainboard)==1)
                    {
                        renderTexture(background3, myRender, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                        renderTexture(image6, myRender, 600, 400);
                        SDL_RenderPresent(myRender);
                        while(true)
                        {
                            SDL_Delay(10);
                            if ( SDL_WaitEvent(&e) == 0) continue;
                            if (e.type == SDL_QUIT) break;
                            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) break;
                            if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
                            {
                                int p, q;
                                SDL_GetMouseState(&p, &q);
                                if((p>=600&&p<=600+iW&&q>=400&&q<=400+iH))
                                {
                                    break;

                                }
                            }
                        }
                    }
                    }
                }
            }
        }
        SDL_DestroyTexture(background1);
        SDL_DestroyTexture(background2);
        SDL_DestroyTexture(background3);
        SDL_DestroyTexture(image1);
        SDL_DestroyTexture(image2);
        SDL_DestroyTexture(image3);
        SDL_DestroyTexture(image4);
        SDL_DestroyTexture(image5);
        SDL_DestroyTexture(image6);
        SDL_DestroyTexture(image7);
        SDL_DestroyTexture(huongdan);
	}
	quitSDL(myWindow, myRender);
    return 0;
}
