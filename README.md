# SudokuGame
# Sudoku game in c++ using SDL 2.0

## Requirments
- Code::Block 20.3
- SDL2.0, SDL_ttf cùng phiên bản với SDL2.0

## How to build and run
- Open Code::Block 20.3
- Click: Create a new project
- Add file main, init.h, draw.h,... in the project
- Compile and run in x86 mode in either Debug and Release
+ Note: copy all the .dll files in my project into your project

## Content files
- init.h: file này gồm các hàm khởi tạo SDL và gỡ lỗi như:
	-initSDL: khởi động SDL, thư viện SDL_ttf và vẽ cửa sổ SDL.
	-logSDLError: kiểm tra lỗi.
	-quitSDL: Kết thúc và xóa màn hình.
	-ngoài ra còn một struct có tên là board chứa giá trị của sudoku trạng thái của vị trí và kích thước hình vuông, 
	hình chữ nhật và kết cấu.
- draw,h: file này gồm các hàm vẽ ô, số, và bảng 9x9
	-loadString: Trả về kết cấu chứa một chuỗi có phông chữ ttf
	-numToText: Trả về kết cấu có chứa một số từ phông chữ TTF đã cho.
	-renderNums: vẽ các số lên cửa sổ.
	-drawGrid: Vẽ lưới đen trên bảng.
	-renderColors: Điền màu của mỗi ô bằng một màu thích hợp dựa trên trạng thái của nó
		+ nếu là ô có chữ số cho sẵn thì có màu xanh nhạt
		+ nếu là ô không có chữ số thì không có màu khi ta ấn chuột vào sẽ chuyển sang màu vàng, khi click chuột 
		ra khỏi chỗ đó thì ô lại trở lại trạng thái cũ dù có số hay không ( thường các ô này có màu của Background)
		+ nếu số trong ô không phù hợp với luật chơi của Sudoku thì sẽ có màu đỏ.
	-renderTexture: có hai hàm mang tên này nhưng tham số khác nhau nhưng cùng chung một mục đích là vẽ ảnh vào một vị 
	trí nhất định với những kích thước khác nhau
	-myloadTexture: hàm này tải ảnh lên
- function.h: file này chứa các chức năng của trò chơi chính
	-initBoard: Khởi tạo mảng hai chiều tải số các trạng thái từ hàm tạo câu đố Sudoku
	-getGridPos: Xác định hnagf cột từ vị trí của x và y của chuột
	-clearActiveStates: Xóa tất cả các trạng thái hoạt động trên bảng
	-checkMove: Kiểm tra các hàng các cột và ma trận 3x3 đã đúng luật của Sudoku chưa
	-condition: Kiểm tra xem dã thắng chưa
-Sudoku.h, Sudoku.cpp: class này để tạo câu đố của Sudoku, gồm các hàm như:
	-getGrid: Nhận chuỗi theo thứ tự đúng của hàng
	-genRandNum: tạo số ngẫu nhiên
	-createSeed: tạo lưới hạt giống
	-Sudoku(): khởi tạo Sudoku
	-Sudoku: khởi tạo điều chỉnh với lưới được truyền dưới dạng đối số
	-verifyGridStatus: xác minh của lưới tùy chỉnh đã được thông qua
	-FindUnassignedLocation: chức năng trợ giúp để giải quyết lưới
	-solveGrid: bộ giải Sudoku
	-countSoln: kiểm tra xem lưới có thể giải duy nhất không
	-genPuzzle: tạo câu đố

## Smooth Content
- Chương trình khởi tạo những chức năng chính của trò chơi.
- Khi chạy chương trình sẽ hiện ra menu chính gồm các menu như dễ trung bình khó và hướng dẫn
- Khi ấn chuột vào các item trên sễ hiện ra màn hình tương ứng
 + dễ :chơi sudoku với mức độ dễ
 + trung bình :chơi sudoku với mức độ trung bình
 + khó :chơi sudoku với mức độ khó
 + hướng dẫn sẽ hiện ra luật của Sudoku
- Khi chơi muốn điền số ở ô nào thì sẽ ấn chuột vào ô đó và nhập số từ màn hình nếu số đó sai ô sẽ chuyển thành màu đỏ,
Ngoài ra còn có chức năng xem đáp án khi bạn không nghĩ ra.<Mình khuyên là không nên dùng không thì chơi game không có ý nghĩa đâu.>



---------------------------------------Thank for reading-----------------------------------
 
