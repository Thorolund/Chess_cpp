#include <iostream>
#include <string>
using namespace std;
class Board;
/** 
 * Абстракция Фигур
 * - Атрибуты: 
 * `string name` - K, R, P, ' '
 * `int pos[2]` - {x, y};
 * `int color` 1 - белый, -1 - черный, 0 - пустота
 * - Методы:
 * `string get_symb` - выдает имя, + воскл. знак если черный
 * `virtual bool move(string turn, Board &board) = 0;` - передвижение фигуры, если возможно
 * `virtual bool check_move(string turn, Board &board) = 0;` - проверка возможности хода*/
class Figure {
	protected:
	int pos[2]; ///`int pos[2]` - {x, y};
	string name; ///`string name` - K, R, P, ' '
	int color = 0; ///`int color` 1 - белый, -1 - черный, 0 - пустота
	public:
	Figure() {
	}
	/**
	 * `string get_symb` - выдает имя, воскл. знак если черный
	 */
	string get_symb() {
		if (color == 1) {
			return " " + name;
		} else if (color == -1) {
			return "!" + name;
		}
		return "  ";
	}
	/**
	 * `virtual bool move(string turn, Board &board) = 0;` - передвижение фигуры, если возможно
	 */
	virtual bool move(string turn, Board &board) = 0;
	/**
	 * `virtual bool check_move(string turn, Board &board) = 0;` - проверка возможности хода
	 */
	virtual bool check_move(string turn, Board &board) = 0;
};
/** 
 * Король
 * - Атрибуты: 
 * `string name` = "K"
 * `int pos[2]` - {x, y};
 * `int color` 1 - белый, -1 - черный
 * - Методы:
 * `string get_symb` - выдает `K`, + воскл. знак если черный
 * `bool move(string turn, Board &board) = 0;` - передвижение на одну клетку в восьми направлениях, если возможно
 * `bool check_move(string turn, Board &board) = 0;` - проверка возможности хода*/
class King: public Figure {
	public:
	King() {
	}
	King(int set_pos[2], int set_color) {
		name = "K";
		pos[0] = set_pos[0];
		pos[1] = pos[1];
		color = set_color;
	}
	bool move(string turn, Board &board) {
		return true;
	}
	bool check_move(string turn, Board &board) {
		return true;
	}
};
/** 
 * Король
 * - Атрибуты: 
 * `string name` = "R"
 * `int pos[2]` - {x, y};
 * `int color` 1 - белый, -1 - черный
 * - Методы:
 * `string get_symb` - выдает `R`, + воскл. знак если черный
 * `bool move(string turn, Board &board) = 0;` - передвижение на линию в четырех направлениях, если возможно
 * `bool check_move(string turn, Board &board) = 0;` - проверка возможности хода*/
class Rook: public Figure {
	public:
	Rook() {
	}
	Rook(int set_pos[2], int set_color) {
		name = "P";
		pos[0] = set_pos[0];
		pos[1] = pos[1];
		color = set_color;
	}
	bool move(string turn, Board &board) {
		return true;
	}
	bool check_move(string turn, Board &board) {
		return true;
	}
};
/** 
 * Пешка
 * - Атрибуты: 
 * `string name` = "P"
 * `int pos[2]` - {x, y};
 * `int color` 1 - белый, -1 - черный
 * - Методы:
 * `string get_symb` - выдает `P`, воскл. знак если черный
 * `bool move(string turn, Board &board) = 0;` - передвижение на одну клетку вперед(в частном случае - на две), если возможно, может превратиться
 * `bool check_move(string turn, Board &board) = 0;` - проверка возможности хода*/
class Pawn: public Figure {
	public:
	Pawn() {
	}
	Pawn(int set_pos[2], int set_color) {
		name = "P";
		pos[0] = set_pos[0];
		pos[1] = pos[1];
		color = set_color;
	}
	bool move(string turn, Board &board) {
		return true;
	}
	bool check_move(string turn, Board &board) {
		return true;
	}
};
int main() {
	int pos[2] = {0, 0};
	Pawn pawn(pos, -1);
	Figure * board[1] = {&pawn};
	cout << (*board[0]).get_symb();
}