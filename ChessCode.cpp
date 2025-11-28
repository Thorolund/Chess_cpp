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
 * `string get_symb` - выдает имя, + минус если черный
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
	virtual ~Figure() {
	}
	/**
	 * `string get_symb` - выдает имя, минус если черный
	 */
	string get_symb() {
		if (color == 1) {
			return " " + name + " ";
		} else if (color == -1) {
			return "-" + name + " ";
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
 * `string get_symb` - выдает `K`, + минус если черный
 * `bool move(string turn, Board &board) = 0;` - передвижение на одну клетку в восьми направлениях, если возможно
 * `bool check_move(string turn, Board &board) = 0;` - проверка возможности хода*/
class King: public Figure {
	public:
	King() {
	}
	King(int set_pos[2], int set_color) {
		name = "K";
		pos[0] = set_pos[0];
		pos[1] = set_pos[1];
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
 * `string get_symb` - выдает `R`, + минус если черный
 * `bool move(string turn, Board &board) = 0;` - передвижение на линию в четырех направлениях, если возможно
 * `bool check_move(string turn, Board &board) = 0;` - проверка возможности хода*/
class Rook: public Figure {
	public:
	Rook() {
	}
	Rook(int set_pos[2], int set_color) {
		name = "R";
		pos[0] = set_pos[0];
		pos[1] = set_pos[1];
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
 * `string get_symb` - выдает `P`, + минус если черный
 * `bool move(string turn, Board &board) = 0;` - передвижение на одну клетку вперед(в частном случае - на две), если возможно, может превратиться
 * `bool check_move(string turn, Board &board) = 0;` - проверка возможности хода*/
class Pawn: public Figure {
	public:
	Pawn() {
	}
	Pawn(int set_pos[2], int set_color) {
		name = "P";
		pos[0] = set_pos[0];
		pos[1] = set_pos[1];
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
 * Пустота
 * - Атрибуты: 
 * `string name` = " "
 * `int pos[2]` - {x, y};
 * `int color = 0`
 * - Методы:
 * `string get_symb` - выдает ` `*/
class Empty: public Figure {
	public:
	Empty() {
	}
	Empty(int set_pos[2]) {
		name = " ";
		pos[0] = set_pos[0];
		pos[1] = set_pos[1];
		color = 0;
	}
	/**
	 * Заглушка -> `false`
	 */
	bool move(string turn, Board &board) {
		return false;
	}
	/**
	 * Заглушка -> `false`
	 */
	virtual bool check_move(string turn, Board &board) {
		return false;
	}
};

/**
 * Доска
 * -Атрибуты:
 * `Figure * *cells[8][8]` - двумерный массив фигур, Ox: 0 -> 'a', 1 -> 'b'..., Oy: 0 -> 1, 1 -> 2...
 * -Методы:
 * `string render()` - возвращает отрисованое поле одной строкой, с отображением букв и разделений
 */
class Board {
	private:
	Figure * cells[8][8];
	public:
	Board() {
		int pos[2];
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				pos[0] = j;
				pos[1] = i;
				if (i == 0 && (j == 0 || j == 7)) {
					Rook * figure = new Rook(pos, 1);
					cells[i][j] = figure;
				} else if (i == 7 && (j == 0 || j == 7)) {
					Rook * figure = new Rook(pos, -1);
					cells[i][j] = figure;
				} else if (i == 1) {
					Pawn * figure = new Pawn(pos, 1);
					cells[i][j] = figure;
				} else if (i == 6) {
					Pawn * figure = new Pawn(pos, -1);
					cells[i][j] = figure;
				} else if (i == 0 && j == 4) {
					King * figure = new King(pos, 1);
					cells[i][j] = figure;
				} else if (i == 7 && j == 4) {
					King * figure = new King(pos, -1);
					cells[i][j] = figure;
				} else {
					Empty * figure = new Empty(pos);
					cells[i][j] = figure;
				}
			}
		}
	}
	~Board() {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				delete cells[i][j];
			}
		}
	}
	string render() {
		string rend = "";
		string liter_mark = "|   | a | b | c | d | e | f | g | h |   |";
		rend += liter_mark + '\n';
		string numb_mark = "12345678";
		string row;
		for (int i = 7; i > -1; i--) {
			row = "| ";
			row += numb_mark[i];
			row += " ";
			for (int j = 0; j < 8; j++) {
				row += ("|" + cells[i][j]->get_symb());
			}
			row += "| ";
			row += numb_mark[i];
			row += " |\n";
			rend += row;
		}
		rend += liter_mark;
		return rend;
	}
};
int main() {
	Board * board = new(Board);
	cout << board->render();
	delete board;
	return 0;
}
