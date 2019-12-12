#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
class chessboard;
class chessman
{
	public:
		chessman(chessboard* _belongboard, int _pos_x, int _pos_y, int _side, string _kind);
		bool moveto(int x, int y);
		virtual bool isableto(int x, int y) = 0;
		~chessman();
	private:
		int pos_x = 0;
		int pos_y = 0;
		int side = 0;
		string kind;
		chessboard* belongboard;
		void go(int x, int y);
		friend class marshal;
		friend class bodyguard;
		friend class minister;
		friend class horse;
		friend class chariot;
		friend class cannon;
		friend class soldier;
};
class marshal :public chessman//将（帅）
{
	public:
		marshal(chessboard* _belongboard, int _pos_x, int _pos_y, int _side, string _kind)
			:chessman(_belongboard, _pos_x, _pos_y, _side, _kind) {};
		virtual bool isableto(int x, int y);
};
class bodyguard :public chessman//士（仕）
{
	public:
		bodyguard(chessboard* _belongboard, int _pos_x, int _pos_y, int _side, string _kind)
			:chessman(_belongboard, _pos_x, _pos_y, _side, _kind) {};
		virtual bool isableto(int x, int y);
};
class minister :public chessman//象（相）
{
	public:
		minister(chessboard* _belongboard, int _pos_x, int _pos_y, int _side, string _kind)
			:chessman(_belongboard, _pos_x, _pos_y, _side, _kind) {};
		virtual bool isableto(int x, int y);
};
class horse :public chessman//马
{
	public:
		horse(chessboard* _belongboard, int _pos_x, int _pos_y, int _side, string _kind)
			:chessman(_belongboard, _pos_x, _pos_y, _side, _kind) {};
		virtual bool isableto(int x, int y);
};
class chariot :public chessman//车
{
	public:
		chariot(chessboard* _belongboard, int _pos_x, int _pos_y, int _side, string _kind)
			:chessman(_belongboard, _pos_x, _pos_y, _side, _kind) {};
		virtual bool isableto(int x, int y);
};
class cannon :public chessman//炮
{
	public:
		cannon(chessboard* _belongboard, int _pos_x, int _pos_y, int _side, string _kind)
			:chessman(_belongboard, _pos_x, _pos_y, _side, _kind) {};
		virtual bool isableto(int x, int y);
};
class soldier :public chessman//卒（兵）
{
	public:
		soldier(chessboard* _belongboard, int _pos_x, int _pos_y, int _side, string _kind)
			:chessman(_belongboard, _pos_x, _pos_y, _side, _kind) {};
		virtual bool isableto(int x, int y);
};
class chessboard
{
	public:
		chessboard();
		bool move(int x1, int y1, int x2, int y2);
		bool isabletomove(int x1, int y1, int x2, int y2);
		int elementnum(int x1, int y1, int x2, int y2);
		~chessboard();
	private:
		chessman* board[11][10];
		int chessnumber1 = 0;
		int chessnumber2 = 0;
		friend class chessman;
		friend class marshal;
		friend class bodyguard;
		friend class minister;
		friend class horse;
		friend class chariot;
		friend class cannon;
		friend class soldier;
};

chessman::chessman(chessboard* _belongboard, int _pos_x, int _pos_y, int _side, string _kind)
{
	belongboard = _belongboard;
	pos_x = _pos_x;
	pos_y = _pos_y;
	side = _side;
	kind = _kind;
	if (_side == 1)
		belongboard->chessnumber1++;
	else if (_side == 2)
		belongboard->chessnumber2++;
}
chessman::~chessman()
{
	if (side == 1)
		belongboard->chessnumber1--;
	else if (side == 2)
		belongboard->chessnumber2--;
}
bool chessman::moveto(int x, int y)
{
	if (this->isableto(x, y))
	{
		this->go(x, y);
		return true;
	}
	else
	{
		return false;
	}
}
void chessman::go(int x, int y)
{
	if (belongboard->board[x][y] == NULL)
	{
		belongboard->board[x][y] = belongboard->board[pos_x][pos_y];
		belongboard->board[pos_x][pos_y] = NULL;
		pos_x = x, pos_x = y;
	}
	else
	{
		delete belongboard->board[x][y];
		belongboard->board[x][y] = belongboard->board[pos_x][pos_y];
		belongboard->board[pos_x][pos_y] = NULL;
		pos_x = x, pos_x = y;
	}
}
bool marshal::isableto(int x, int y)
{
	if (this->belongboard->board[x][y] != NULL)
	{
		if (this->belongboard->board[x][y]->side == this->side)
			return false;
	}
	if ((x >= 1 && x <= 3 && y >= 4 && y <= 6 && this->side == 1) || (x >= 8 && x <= 10 && y >= 4 && y <= 6 && this->side == 2))
	{
		if ((this->pos_x == x && abs(y - this->pos_x) == 1) || (abs(y - this->pos_y) == 1 && y == this->pos_x))
			return true;
		return false;
	}
	return false;
}
bool bodyguard::isableto(int x, int y)
{
	if (this->belongboard->board[x][y] != NULL)
	{
		if (this->belongboard->board[x][y]->side == this->side)
			return false;
	}
	if ((x >= 1 && x <= 3 && y >= 4 && y <= 6 && this->side == 1) || (x >= 8 && x <= 10 && y >= 4 && y <= 6 && this->side == 2))
	{
		if (abs(this->pos_x - x) == 1 && abs(this->pos_y - y) == 1)
			return true;
		return false;
	}
	return false;
}
bool minister::isableto(int x, int y)
{
	if (this->belongboard->board[x][y] != NULL)
	{
		if (this->belongboard->board[x][y]->side == this->side)
			return false;
	}
	if ((x >= 1 && x <= 5 && this->side == 1) || (x >= 6 && x <= 10 && this->side == 2))
	{
		if (abs(this->pos_x - x) == 2 && abs(this->pos_y - y) == 2 && this->belongboard->board[(this->pos_x + x) / 2][(this->pos_y + y) / 2] == NULL)
			return true;
		return false;
	}
	return false;
}
bool horse::isableto(int x, int y)
{
	if (this->belongboard->board[x][y] != NULL)
	{
		if (this->belongboard->board[x][y]->side == this->side)
			return false;
	}
	if (abs(this->pos_x - x) == 2 && abs(this->pos_y - y) == 1 && this->belongboard->board[this->pos_x][(this->pos_y + y) / 2] == NULL)
		return true;
	else if (abs(this->pos_x - x) == 1 && abs(this->pos_y - y) == 2 && this->belongboard->board[(this->pos_x + x) / 2][this->pos_y] == NULL)
		return true;
	return false;
}
bool chariot::isableto(int x, int y)
{
	if (this->belongboard->board[x][y] != NULL)
	{
		if (this->belongboard->board[x][y]->side == this->side)
			return false;
	}
	if (this->pos_x == x && this->belongboard->elementnum(this->pos_x, this->pos_y, x, y) == 2)
		return true;
	if (this->pos_y == y && this->belongboard->elementnum(this->pos_x, this->pos_y, x, y) == 2)
		return true;
	return false;
}
bool cannon::isableto(int x, int y)
{
	if (this->belongboard->board[x][y] != NULL)
	{
		if (this->belongboard->board[x][y]->side == this->side)
			return false;
	}
	if (this->pos_x == x && this->belongboard->elementnum(this->pos_x, this->pos_y, x, y) == 3)
		return true;
	if (this->pos_y == y && this->belongboard->elementnum(this->pos_x, this->pos_y, x, y) == 3)
		return true;
	return false;
}
bool soldier::isableto(int x, int y)
{
	if (this->belongboard->board[x][y] != NULL)
	{
		if (this->belongboard->board[x][y]->side == this->side)
			return false;
	}
	if (this->side == 1)
	{
		if (x <= 5 && this->pos_y == y && x - this->pos_x == 1)
			return true;
		if (x >= 6 && ((abs(this->pos_y - y) == 1 && this->pos_x == x) || (x - this->pos_x == 1 && this->pos_y == y)))
			return true;
		return false;
	}
	else if (this->side == 2)
	{
		if (x >= 6 && this->pos_y == y && this->pos_x - x == 1)
			return true;
		if (x <= 5 && ((abs(this->pos_y - y) == 1 && this->pos_x == x) || (this->pos_x - x == 1 && this->pos_y == y)))
			return true;
		return false;
	}
	return false;
}

bool chessboard::isabletomove(int x1, int y1, int x2, int y2)
{
	if (x1 < 1 || x1>10 || y1 < 1 || y1>9)
		return false;
	if (x2 < 1 || x2>10 || y2 < 1 || y2>9)
		return false;
	if (board[x1][y1] == NULL)
		return false;
	if (board[x1][y1]->isableto(x2, y2))
		return true;
	return false;
}
chessboard::chessboard()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 11; j++)
		{
			board[i][j] = NULL;
		}
	board[1][1] = new chariot(this, 1, 1, 1, "车");
	board[1][2] = new horse(this, 1, 2, 1, "马");
	board[1][3] = new minister(this, 1, 3, 1, "象");
	board[1][4] = new bodyguard(this, 1, 4, 1, "士");
	board[1][5] = new marshal(this, 1, 5, 1, "将");
	board[1][6] = new bodyguard(this, 1, 6, 1, "士");
	board[1][7] = new minister(this, 1, 7, 1, "象");
	board[1][8] = new horse(this, 1, 8, 1, "马");
	board[1][9] = new chariot(this, 1, 9, 1, "车");
	board[3][2] = new cannon(this, 3, 2, 1, "炮");
	board[3][8] = new cannon(this, 3, 8, 1, "炮");
	board[4][1] = new soldier(this, 4, 1, 1, "卒");
	board[4][3] = new soldier(this, 4, 3, 1, "卒");
	board[4][5] = new soldier(this, 4, 5, 1, "卒");
	board[4][7] = new soldier(this, 4, 7, 1, "卒");
	board[4][9] = new soldier(this, 4, 9, 1, "卒");

	board[7][1] = new soldier(this, 7, 1, 2, "兵");
	board[7][3] = new soldier(this, 7, 3, 2, "兵");
	board[7][5] = new soldier(this, 7, 5, 2, "兵");
	board[7][7] = new soldier(this, 7, 7, 2, "兵");
	board[7][9] = new soldier(this, 7, 9, 2, "兵");
	board[8][2] = new cannon(this, 8, 2, 2, "炮");
	board[8][8] = new cannon(this, 8, 8, 2, "炮");
	board[10][1] = new chariot(this, 10, 1, 2, "车");
	board[10][2] = new horse(this, 10, 2, 2, "马");
	board[10][3] = new minister(this, 10, 3, 2, "相");
	board[10][4] = new bodyguard(this, 10, 4, 2, "仕");
	board[10][5] = new marshal(this, 10, 5, 2, "帅");
	board[10][6] = new bodyguard(this, 10, 6, 2, "仕");
	board[10][7] = new minister(this, 10, 7, 2, "相");
	board[10][8] = new horse(this, 10, 8, 2, "马");
	board[10][9] = new chariot(this, 10, 9, 2, "车");
}
bool chessboard::move(int x1, int y1, int x2, int y2)
{
	if (this->isabletomove(x1, y1, x2, y2)) {
		board[x1][y1]->moveto(x2, y2);
		return true;
	}
	return false;
};
int chessboard::elementnum(int x1, int y1, int x2, int y2)
{
	int left = min(x1, x2), right = max(x1, x2);
	int top = min(y1, y2), bottom = max(y1, y2);
	int number = 0;
	for (int i = left; i <= right; i++)
		for (int j = top; j <= bottom; j++)
			if (this->board[i][j] != NULL)
				number++;
	return number;
}
chessboard::~chessboard()
{
	for (int i = 1; i <= 10; i++)
	{
		for (int j = 1; j <= 9; j++)
		{
			if (board[i][j] != NULL)
				delete board[i][j];
		}
	}
}
