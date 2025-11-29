#include <iostream>
#include <string>
using namespace std;
/**
* `int char_to_int(char n)` - переводит char обозначение Oy в int
*/
int char_to_int(char n) {
    string letters = "12345678";
    int res = -1;
	for (int i = 0; i < 8; i++) {
	    if (letters[i] == n) {
	        res = i;
	        break;
	        }
	    }
	return res;
}
/**
* `int lettet_to_int(char a)` - переводит буквенное обозначение Ox в int
*/
int lettet_to_int(char a) {
	string letters = "abcdefgh";
	int res = -1;
	for (int i = 0; i < 8; i++) {
        if (letters[i] == a) {
            res = i;
	        break;
	    }
	}
	return res;
}

class Board;

/** 
 * Абстракция Фигур
 * - Атрибуты: 
 * `string name` - K, R, P, ' '
 * `int color` 1 - белый, -1 - черный, 0 - пустота
 * - Методы:
 * `string get_symb` - выдает имя, + минус если черный
 * `virtual  bool check_move(int turn[2][2], Board &board) = 0;` - проверка возможности хода*/
class Figure {
	protected:
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
		return "   ";
	}
	/**
	 * `virtual bool move(int turn[2], Board &board)` - проверка возможности хода
	 */
	virtual  bool check_move(int turn[2][2], Board &board) = 0;
};
/** 
 * Король
 * - Атрибуты: 
 * `string name` = "K"
 * `int color` 1 - белый, -1 - черный
 * - Методы:
 * `string get_symb` - выдает `K`, + минус если черный
 * ` bool check_move(int turn[2][2], Board &board)` - проверка возможности хода*/
class King: public Figure {
	public:
	King() {
	}
	King(int set_color) {
		name = "K";
		color = set_color;
	}
	 bool check_move(int turn[2][2], Board &board) {
		return true;
	}
};
/** 
 * Ладья
 * - Атрибуты: 
 * `string name` = "R"
 * `int color` 1 - белый, -1 - черный
 * - Методы:
 * `string get_symb` - выдает `R`, + минус если черный
 * ` bool check_move(int turn[2][2], Board &board)` - проверка возможности хода*/
class Rook: public Figure {
	public:
	Rook() {
	}
	Rook(int set_color) {
		name = "R";
		color = set_color;
	}
	 bool check_move(int turn[2][2], Board &board) {
		return true;
	}
};
/** 
 * Пешка
 * - Атрибуты: 
 * `string name` = "P"
 * `int color` 1 - белый, -1 - черный
 * - Методы:
 * `string get_symb` - выдает `P`, + минус если черный
 * `bool move(int turn[2], Board &board)` - проверка возможности хода*/
class Pawn: public Figure {
	public:
	Pawn() {
	}
	Pawn(int set_color) {
		name = "P";
		color = set_color;
	}
	bool check_move(int turn[2][2], Board &board) {
		return true;
	}
};
/** 
 * Пустота
 * - Атрибуты: 
 * `string name` = " "
 * `int color = 0`
 * - Методы:
 * `string get_symb` - выдает ` `*/
class Empty: public Figure {
	public:
	Empty() {
		name = " ";
		color = 0;
	}
	/**
	 * Заглушка -> `false`
	 */
	virtual  bool check_move(int turn[2][2], Board &board) {
		return false;
	}
};

/**
 * Доска
 * - Атрибуты:
 * `Figure * cells[8][8]` - двумерный массив фигур, Ox: 0 -> 'a', 1 -> 'b'..., Oy: 0 -> 1, 1 -> 2...
 * `int player_color` - цвет игрока, творящего ход, `1` - белый, `-1` - черный
 * `int turn[2][2]` - {{x1, y1}, {x2, y2}} совершаемый ход
 * - Методы:
 * `string render()` - возвращает отрисованое поле одной строкой, с отображением букв и разделений
 * `void set_turn(string str_turn)` - принимает ход, на его основе изменяет `turn`
 * `bool try_move(Board &board)` - пытается совершить ход, `true` - если ход совершен
 * `bool is_check()` - проверка на шах, `1` - если шах белому, `-1` - если шах черному, `0` - нет шаха
 * `bool is_mate()` - проверка на мат, `1` - если мат белому, `-1` - если мат черному, `0` - нет мата
 */
class Board {
	private:
	Figure * cells[8][8]; ///`Figure * cells[8][8]` - двумерный массив фигур, Ox: 0 -> 'a', 1 -> 'b'..., Oy: 0 -> 1, 1 -> 2...
	int player_color = 1; ///`int player_color` - цвет игрока, творящего ход, `1` - белый, `-1` - черный
	int turn[2][2]; ///`int turn[2][2]` - {{x1, y1}, {x2, y2}} совершаемый ход
	public:
	Board() {
		int pos[2];
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (i == 0 && (j == 0 || j == 7)) {
					Rook * figure = new Rook(1);
					cells[i][j] = figure;
				} else if (i == 7 && (j == 0 || j == 7)) {
					Rook * figure = new Rook(-1);
					cells[i][j] = figure;
				} else if (i == 1) {
					Pawn * figure = new Pawn(1);
					cells[i][j] = figure;
				} else if (i == 6) {
					Pawn * figure = new Pawn(-1);
					cells[i][j] = figure;
				} else if (i == 0 && j == 4) {
					King * figure = new King(1);
					cells[i][j] = figure;
				} else if (i == 7 && j == 4) {
					King * figure = new King(-1);
					cells[i][j] = figure;
				} else {
					Empty * figure = new Empty();
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
	int get_color() {
		return player_color;
	}
	/**
	*`string render()` - возвращает отрисованое поле одной строкой, с отображением букв и разделений
	*/
	string render() {
		string rend = "";
		string letter_mark = "    | a | b | c | d | e | f | g | h |   ";
		rend += letter_mark + '\n';
		string numb_mark = "12345678";
		string row;
		for (int i = 7; i > -1; i--) {
		    rend += "-----------------------------------------\n";
			row = "  ";
			row += numb_mark[i];
			row += " ";
			for (int j = 0; j < 8; j++) {
				row += ("|" + cells[i][j]->get_symb());
			}
			row += "| ";
			row += numb_mark[i];
			row += " \n";
			rend += row;
		}
		rend += "-----------------------------------------\n";
		rend += letter_mark;
		return rend;
	}
	/**
	 * `void set_turn(string str_turn)` - принимает ход, на его основе изменяет `turn`, считаем корректным по записи (!= правильный ход, просто гарантированно не кракозябра)
	 */
	void set_turn(string str_turn) {
		if (str_turn[1] == 'x') { //cxd4
			turn[1][0] = lettet_to_int(str_turn[2]);
			turn[1][1] = char_to_int(str_turn[3]);
			turn[0][0] = lettet_to_int(str_turn[0]);
			turn[0][1] = turn[1][1] - player_color;
		} else if (str_turn[2] == '-') { //e5-e7
			turn[0][0] = lettet_to_int(str_turn[0]);
			turn[0][1] = char_to_int(str_turn[1]);
			turn[1][0] = lettet_to_int(str_turn[3]);
			turn[1][1] = char_to_int(str_turn[4]);
		} else { //Re1-e4
			turn[0][0] = lettet_to_int(str_turn[1]);
			turn[0][1] = char_to_int(str_turn[2]);
			turn[1][0] = lettet_to_int(str_turn[4]);
			turn[1][1] = char_to_int(str_turn[5]);
		}
	}
	/**
	 * `bool try_move(Board &board)` - пытается совершить ход, `true` - если ход совершен
	 */
	bool try_move(Board &board) {
		if (cells[turn[0][1]][turn[0][0]]->check_move(turn, board)) {
			swap(cells[turn[0][1]][turn[0][0]], cells[turn[1][1]][turn[1][0]]);
			delete cells[turn[0][1]][turn[0][0]];
			Empty * new_empty = new Empty();
			cells[turn[0][1]][turn[0][0]] = new_empty;
			player_color = -player_color;
			return true;
		}
		return false;
	}
	/**
	 * `bool is_check()` - проверка на шах, `1` - если шах белому, `-1` - если шах черному, `0` - нет шаха
	 */
	int is_check() {
		return 0;
	}
	/**
	 * `bool is_mate()` - проверка на мат, `1` - если мат белому, `-1` - если мат черному, `0` - нет мат
	 */
	int is_mate() {
		return 0;
	}
};
int main() {
	Board * board = new Board;
	string turn;
	int color;
	while (board->is_mate() == 0) {
		cout << board->render() << endl;
		color = board->get_color();
		if (board->is_check() != 0) {
			cout << "Check!" << endl;
		}
		if (color == 1) {
			cout << "White:    ";
		} else {
			cout << "Black:	   ";
		}
		cin >> turn;
		board->set_turn(turn);
		while(!board->try_move(*board)) {
			cout << "Incorrect move" << endl;
			if (color == 1) {
				cout << "White:    ";
			} else {
				cout << "Black:	   ";
			}
			cin >> turn;
			board->set_turn(turn);
		}
	}
	delete board;
	return 0;
}
