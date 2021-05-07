#include "Sudoku.h"


Sudoku::~Sudoku()
{
    //dtor
}
//  Nhận lưới dưới dạng chuỗi theo thứ tự chính của hàng
string Sudoku::getGrid()
{
  string s = "";
  for(int row_num=0; row_num<9; ++row_num)
  {
    for(int col_num=0; col_num<9; ++col_num)
    {
      s = s + to_string(grid[row_num][col_num]);
    }
  }

  return s;
}



//  Tạo số ngẫu nhiên
int genRandNum(int maxLimit)
{
  return rand()%maxLimit;
}



//  Tạo lưới hạt giống
void Sudoku::createSeed()
{
  this->solveGrid();

  // Lưu lưới giải pháp
  for(int i=0;i<9;i++)
  {
    for(int j=0;j<9;j++)
    {
      this->solnGrid[i][j] = this->grid[i][j];
    }
  }
}



// Khởi tạo
Sudoku::Sudoku()
{
  //Trộn ngẫu nhiên mảng xóa các vị trí lưới
  for(int i=0;i<81;i++)
  {
    this->gridPos[i] = i;
  }

  random_shuffle(this->gridPos, (this->gridPos) + 81, genRandNum);

  // Xáo trộn ngẫu nhiên mảng số đoán
  for(int i=0;i<9;i++)
  {
    this->guessNum[i]=i+1;
  }

  random_shuffle(this->guessNum, (this->guessNum) + 9, genRandNum);

  //Khởi tạo lưới
  for(int i=0;i<9;i++)
  {
    for(int j=0;j<9;j++)
    {
      this->grid[i][j]=0;
    }
  }

  grid_status = true;
}



// Khởi tạo tùy chỉnh với lưới được truyền dưới dạng đối số
Sudoku::Sudoku(string grid_str, bool row_major)
{
  if(grid_str.length() != 81)
  {
    grid_status=false;
    return;
  }

  // Lần vượt qua đầu tiên: Kiểm tra xem tất cả các ô có hợp lệ không
  for(int i=0; i<81; ++i)
  {
    int curr_num = grid_str[i]-'0';
    if(!((curr_num == UNASSIGNED) || (curr_num > 0 && curr_num < 10)))
    {
      grid_status=false;
      return;
    }

    if(row_major) grid[i/9][i%9] = curr_num;
    else          grid[i%9][i/9] = curr_num;
  }

  // Vượt qua thứ hai: Kiểm tra xem tất cả các cột có hợp lệ không
  for (int col_num=0; col_num<9; ++col_num)
  {
    bool nums[10]={false};
    for (int row_num=0; row_num<9; ++row_num)
    {
      int curr_num = grid[row_num][col_num];
      if(curr_num!=UNASSIGNED && nums[curr_num]==true)
      {
        grid_status=false;
        return;
      }
      nums[curr_num] = true;
    }
  }

  // Thẻ thứ ba: Kiểm tra xem tất cả các hàng có hợp lệ không
  for (int row_num=0; row_num<9; ++row_num)
  {
    bool nums[10]={false};
    for (int col_num=0; col_num<9; ++col_num)
    {
      int curr_num = grid[row_num][col_num];
      if(curr_num!=UNASSIGNED && nums[curr_num]==true)
      {
        grid_status=false;
        return;
      }
      nums[curr_num] = true;
    }
  }

  // Lần thứ tư: Kiểm tra xem tất cả các khối có hợp lệ không
  for (int block_num=0; block_num<9; ++block_num)
  {
    bool nums[10]={false};
    for (int cell_num=0; cell_num<9; ++cell_num)
    {
      int curr_num = grid[((int)(block_num/3))*3 + (cell_num/3)][((int)(block_num%3))*3 + (cell_num%3)];
      if(curr_num!=UNASSIGNED && nums[curr_num]==true)
      {
        grid_status=false;
        return;
      }
      nums[curr_num] = true;
    }
  }

  // Xáo trộn ngẫu nhiên mảng số đoán
  for(int i=0;i<9;i++)
  {
    this->guessNum[i]=i+1;
  }

  random_shuffle(this->guessNum, (this->guessNum) + 9, genRandNum);

  grid_status = true;
}


//Trạng thái xác minh của lưới tùy chỉnh đã được thông qua
bool Sudoku::verifyGridStatus()
{
  return grid_status;
}

// Chức năng trợ giúp để giải quyết lưới
bool FindUnassignedLocation(int grid[9][9], int &row, int &col)
{
    for (row = 0; row < 9; row++)
    {
        for (col = 0; col < 9; col++)
        {
            if (grid[row][col] == UNASSIGNED)
                return true;
        }
    }

    return false;
}

bool UsedInRow(int grid[9][9], int row, int num)
{
    for (int col = 0; col < 9; col++)
    {
        if (grid[row][col] == num)
            return true;
    }

    return false;
}

bool UsedInCol(int grid[9][9], int col, int num)
{
    for (int row = 0; row < 9; row++)
    {
        if (grid[row][col] == num)
            return true;
    }

    return false;
}

bool UsedInBox(int grid[9][9], int boxStartRow, int boxStartCol, int num)
{
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (grid[row+boxStartRow][col+boxStartCol] == num)
                return true;
        }
    }

    return false;
}

bool isSafe(int grid[9][9], int row, int col, int num)
{
    return !UsedInRow(grid, row, num) && !UsedInCol(grid, col, num) && !UsedInBox(grid, row - row%3 , col - col%3, num);
}


// Bộ giải Sudoku
bool Sudoku::solveGrid()
{
    int row, col;

    // Nếu không có vị trí chưa được chỉ định, chúng tôi đã hoàn thành
    if (!FindUnassignedLocation(this->grid, row, col))
       return true; // success!

    // Xem xét các chữ số từ 1 đến 9
    for (int num = 0; num < 9; num++)
    {
        //nếu có vẻ hứa hẹn
        if (isSafe(this->grid, row, col, this->guessNum[num]))
        {
            // thực hiện bài tập dự kiến
            this->grid[row][col] = this->guessNum[num];

            // trở lại, nếu thành công, yay!
            if (solveGrid())
                return true;

            // thất bại, hủy bỏ và thử lại
            this->grid[row][col] = UNASSIGNED;
        }
    }

    return false; // điều này kích hoạt backtracking

}


//Kiểm tra xem lưới có thể giải được duy nhất hay không
void Sudoku::countSoln(int &number)
{
  int row, col;

  if(!FindUnassignedLocation(this->grid, row, col))
  {
    number++;
    return ;
  }


  for(int i=0;i<9 && number<2;i++)
  {
      if( isSafe(this->grid, row, col, this->guessNum[i]) )
      {
        this->grid[row][col] = this->guessNum[i];
        countSoln(number);
      }

      this->grid[row][col] = UNASSIGNED;
  }

}

// Tạo câu đố
void Sudoku::genPuzzle()
{
    if(level==1)
    {
        int countnumber1=0;
        for(int i=0;i<81;i++)
          {
                int x = (this->gridPos[i])/9;
                int y = (this->gridPos[i])%9;
                int temp = this->grid[x][y];
                this->grid[x][y] = UNASSIGNED;

                // Nếu bây giờ có nhiều hơn 1 giải pháp, hãy thay thế ô đã loại bỏ trở lại.
                int check=0;
                countSoln(check);
                if(check!=1)
                {
                  this->grid[x][y] = temp;
                }
                countnumber1++;
                if(countnumber1==40) break;
                else continue;
          }
    }
    if(level==2)
    {
        int countnumber2=0;
        for(int i=0;i<81;i++)
          {
                int x = (this->gridPos[i])/9;
                int y = (this->gridPos[i])%9;
                int temp = this->grid[x][y];
                this->grid[x][y] = UNASSIGNED;

                // Nếu bây giờ có nhiều hơn 1 giải pháp, hãy thay thế ô đã loại bỏ trở lại.
                int check=0;
                countSoln(check);
                if(check!=1)
                {
                  this->grid[x][y] = temp;
                }
                countnumber2++;
                if(countnumber2==45) break;
                else continue;
          }
    }
    if(level==3)
    {
        int countnumber3=0;
        for(int i=0;i<81;i++)
          {
                int x = (this->gridPos[i])/9;
                int y = (this->gridPos[i])%9;
                int temp = this->grid[x][y];
                this->grid[x][y] = UNASSIGNED;

                // Nếu bây giờ có nhiều hơn 1 giải pháp, hãy thay thế ô đã loại bỏ trở lại.
                int check=0;
                countSoln(check);
                if(check!=1)
                {
                  this->grid[x][y] = temp;
                }
                countnumber3++;
                if(countnumber3==50) break;
                else continue;
          }
    }
}

