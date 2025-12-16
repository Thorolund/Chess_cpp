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
 * `string get_symb` - выдает имя, + `-` если черный
 * `int get_color` - выдает цвет
 * `virtual  bool check_move(int turn[2][2], Figure * cells[8][8]) = 0;` - проверка возможности хода
 * */
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
	 * `string get_symb` - выдает имя, минус если черный (` R `/`-K `)
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
	 * `int get_color` - выдает цвет
	 */
	int get_color() {
		return color;
	}
	/**
	 * `virtual bool move(int turn[2], Board &board)` - проверка возможности хода
	 */
	virtual  bool check_move(int turn[2][2], Figure * cells[8][8]) = 0;
};
/** 
 * Король
 * - Атрибуты: 
 * `string name` = "K"
 * `int color` 1 - белый, -1 - черный
 * - Методы:
 * `string get_symb` - выдает `K`, + минус если черный
 * `int get_color` - выдает цвет
 * `bool check_move(int turn[2][2], Figure * cells[8][8])` - проверка возможности хода (в восьми напрвлениях на 1 клетку)
 * */
class King: public Figure {
	public:
	King() {
	}
	King(int set_color) {
		name = "K";
		color = set_color;
	}
	bool check_move(int turn[2][2], Figure * cells[8][8]) {
		bool res = true;
		if ((turn[1][0] - turn[0][0])*(turn[1][0] - turn[0][0]) > 1 ||
			(turn[1][1] - turn[0][1])*(turn[1][1] - turn[0][1]) > 1) {
				res = false;
			}
		if (cells[turn[1][1]][turn[1][0]]->get_color() == color) {
			res = false;
		}
		return res;
	}
};
/** 
 * Ладья
 * - Атрибуты:
 * `string name` = `R`
 * `int color` 1 - белый, -1 - черный
 * - Методы:
 * `string get_symb` - выдает `R`, + `-` если черный
 * `int get_color` - выдает цвет
 * `bool check_move(int turn[2][2], Figure * cells[8][8])` - проверка возможности хода
 * */
class Rook: public Figure {
	public:
	Rook() {
	}
	Rook(int set_color) {
		name = "R";
		color = set_color;
	}
	bool check_move(int turn[2][2], Figure * cells[8][8]) {
		bool res = true;
		if (turn[1][0] != turn[0][0] && turn[1][1] != turn[0][1]) {
			res = false;
		}
		if (cells[turn[1][1]][turn[1][0]]->get_color() == color) {
			res = false;
		}
		if (turn[1][0] != turn[0][0] && res) {
			int i = turn[1][1];
			for (int j = min(turn[1][0], turn[0][0]) + 1; j < max(turn[1][0], turn[0][0]); j++) {
				if (!cells[i][j]->get_color() == 0) {
					res = false;
					break;
				}
			}
		} else if (turn[0][1] != turn[1][1] && res) {
			int j = turn[0][0];
			for (int i = min(turn[1][1], turn[0][1]) + 1; i < max(turn[1][1], turn[0][1]); i++) {
				if (!cells[i][j]->get_color() == 0) {
					res = false;
					break;
				}
			}
		}
		return res;
	}
};
/** 
 * Пешка
 * - Атрибуты: 
 * `string name` = `P`
 * `int color` 1 - белый, -1 - черный
 * - Методы:
 * `string get_symb` - выдает `P`, + `-` если черный
 * `int get_color` - выдает цвет
 * `bool move(int turn[2], Board &board)` - проверка возможности хода*/
class Pawn: public Figure {
	public:
	Pawn() {
	}
	Pawn(int set_color) {
		name = "P";
		color = set_color;
	}
	bool check_move(int turn[2][2], Figure * cells[8][8]) {
		bool res = false;
		int empty_pos[2];
		if (turn[1][1] - turn[0][1] == color && turn[0][0] == turn[1][0]) {
			empty_pos[0] = turn[1][0];
			empty_pos[1] = turn[1][1];
			res = cells[empty_pos[1]][empty_pos[0]]->get_color() == 0;
		} else if (turn[1][1] - turn[0][1] == 2*color && turn[0][0] == turn[1][0]) {
			empty_pos[0] = turn[1][0];
			empty_pos[1] = turn[1][1] - color;
			if (color == 1 && turn[0][1] == 1) {
				res = cells[turn[1][1]][turn[1][0]]->get_color() == 0;
				if (res) {
					res = cells[empty_pos[1]][empty_pos[0]]->get_color() == 0;
				}
			} else if (color == -1 && turn[0][1] == 6) {
				res = cells[turn[1][1]][turn[1][0]]->get_color() == 0;
				if (res) {
					res = cells[empty_pos[1]][empty_pos[0]]->get_color() == 0;
				}
			}
		} else if (turn[1][1] - turn[0][1] == color && (turn[0][0] - turn[1][0] == 1 || turn[0][0] - turn[1][0] == -1)) {
			res = cells[turn[1][1]][turn[1][0]]->get_color() == -color;
		}
		return res;
	}
};
/** 
 * Пустота
 * - Атрибуты: 
 * `string name` = " "
 * `int color = 0`
 * - Методы:
 * `string get_symb` - выдает ` `
 * `int get_color` - выдает `0`
 * */
class Empty: public Figure {
	public:
	Empty() {
		name = " ";
		color = 0;
	}
	/**
	 * Заглушка -> `false`
	 */
	virtual  bool check_move(int turn[2][2], Figure * cells[8][8]) {
		return false;
	}
};

/**
 * Доска
 * - Атрибуты:
 * `Figure * cells[8][8]` - двумерный массив фигур, Ox: 0 -> 'a', 1 -> 'b'..., Oy: 0 -> 1, 1 -> 2...
 * `int player_color` - цвет игрока, творящего ход, `1` - белый, `-1` - черный
 * `int turn[2][2]` - {{x1, y1}, {x2, y2}} совершаемый ход
 * `string turn_figure` - фигура, указанная в ходе
 * - Методы:
 * `string render()` - возвращает отрисованое поле одной строкой, с отображением букв и разделений
 * `void set_turn(string str_turn)` - принимает ход, на его основе изменяет `turn`
 * `bool try_move(Board &board)` - пытается совершить ход, `true` - если ход совершен
 * `bool is_check(Board &board)` - проверка на шах, `1` - если шах белым, `-1` - если шах черным, `0` - нет шаха
 * `bool is_check()` - перегрузка для инкапсуляции
 * `bool is_mate(Board &board)` - проверка на мат, `1` - если мат белым, `-1` - если мат черным, `0` - нет мата
 */
class Board {
	private:
	int player_color = 1; ///`int player_color` - цвет игрока, творящего ход, `1` - белый, `-1` - черный
	string turn_figure; ///`string turne_figure` - фигура, указанная в ходе
	Figure * cells[8][8]; ///`Figure * cells[8][8]` - двумерный массив фигур, Ox: 0 -> 'a', 1 -> 'b'..., Oy: 0 -> 1, 1 -> 2...
	public:
	int turn[2][2]; ///`int turn[2][2]` - {{x1, y1}, {x2, y2}} совершаемый ход
	Board() {
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
					cells[i][j] = new Empty();
				}
			}
		}
	}
	Board(Board &board) {
		turn[0][0] = board.turn[0][0];
		turn[0][1] = board.turn[0][1];
		turn[1][0] = board.turn[1][0];
		turn[1][1] = board.turn[1][1];
		player_color = board.player_color;
		turn_figure = board.turn_figure;
		
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				string type_figure = board.cells[i][j]->get_symb();
				int color_figure = board.cells[i][j]->get_color();
				
				if (type_figure[1] == 'P') {
					cells[i][j] = new Pawn(color_figure);
				} else if (type_figure[1] == 'R') {
					cells[i][j] = new Rook(color_figure);
				} else if (type_figure[1] == 'K') {
					cells[i][j] = new King(color_figure);
				} else {
					cells[i][j] = new Empty();
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
	int get_figure_color(int pos[2]) {
		return cells[pos[1]][pos[0]]->get_color();
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
		turn[0][0] = -1;
		if (str_turn.size() >= 4 && str_turn[1] == 'x') { //cxd4
			turn[1][0] = lettet_to_int(str_turn[2]);
			turn[1][1] = char_to_int(str_turn[3]);
			turn[0][0] = lettet_to_int(str_turn[0]);
			turn[0][1] = turn[1][1] - player_color;
			turn_figure = " P";
			if (player_color == -1) {
				turn_figure[0] = '!';
			}
		} else if (str_turn.size() >= 5 && str_turn[2] == '-') { //e5-e7
			turn[0][0] = lettet_to_int(str_turn[0]);
			turn[0][1] = char_to_int(str_turn[1]);
			turn[1][0] = lettet_to_int(str_turn[3]);
			turn[1][1] = char_to_int(str_turn[4]);
			turn_figure = " P";
			if (player_color == -1) {
				turn_figure[0] = '!';
			}
		} else if (str_turn.size() >= 6) { //Re1-e4
			turn[0][0] = lettet_to_int(str_turn[1]);
			turn[0][1] = char_to_int(str_turn[2]);
			turn[1][0] = lettet_to_int(str_turn[4]);
			turn[1][1] = char_to_int(str_turn[5]);
			turn_figure = " K";
			if (player_color == -1) {
				turn_figure[0] = '!';
			}
		}
	}
	void set_turn(int int_turn[2][2]) {
		turn[0][0] = int_turn[0][0];
		turn[1][0] = int_turn[1][0];
		turn[0][1] = int_turn[0][1];
		turn[1][1] = int_turn[1][1];
	}
	/**
	* `bool try_move(Board &board)` - пытается совершить ход, `true` - если ход совершен
	*/
	bool try_move(Board &board) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				if (turn[i][j] == -1) {
					return false;
				}
			}
		}
		
		// Проверяем, что фигура, которую хотим двигать, принадлежит текущему игроку
		if (cells[turn[0][1]][turn[0][0]]->get_color() != player_color) {
			return false;
		}
		
		if (cells[turn[0][1]][turn[0][0]]->check_move(turn, cells)) {
			// Создаем копию доски для проверки
			Board * try_board = new Board(board);
			
			// Делаем ход на пробной доске
			swap(try_board->cells[turn[0][1]][turn[0][0]], try_board->cells[turn[1][1]][turn[1][0]]);
			
			// Удаляем пустую клетку на старом месте
			delete try_board->cells[turn[0][1]][turn[0][0]];
			try_board->cells[turn[0][1]][turn[0][0]] = new Empty();
			
			// Проверяем, не будет ли шах королю того, кто делает ход
			if (try_board->is_check(player_color)) {
				delete try_board;
				return false; // Ход оставляет короля под шахом
			}
			
			// Если проверка прошла, делаем ход на реальной доске
			swap(cells[turn[0][1]][turn[0][0]], cells[turn[1][1]][turn[1][0]]);
			
			// Превращение пешки в ладью (у вас здесь ошибка - не присваиваете new_rook клетке)
			if (cells[turn[1][1]][turn[1][0]]->get_symb() == " P " && turn[1][1] == 7) {
				delete cells[turn[1][1]][turn[1][0]];
				cells[turn[1][1]][turn[1][0]] = new Rook(1);
			}
			if (cells[turn[1][1]][turn[1][0]]->get_symb() == "-P " && turn[1][1] == 0) {
				delete cells[turn[1][1]][turn[1][0]];
				cells[turn[1][1]][turn[1][0]] = new Rook(-1);
			}
			
			// Удаляем пустую клетку на старом месте
			delete cells[turn[0][1]][turn[0][0]];
			cells[turn[0][1]][turn[0][0]] = new Empty();
			
			player_color = -player_color; // Меняем игрока
			delete try_board;
			return true;
		}
		return false;
	}
	/**
	* `bool is_check(int king_color)` - проверка на шах для короля заданного цвета
	* Возвращает true, если король цвета king_color находится под шахом
	*/
	bool is_check(int king_color) {
		int king_pos[2] = {-1, -1};
		string king_type = " K ";
		if (king_color == -1) {
			king_type[0] = '-';
		}
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (cells[i][j]->get_symb() == king_type) {
					king_pos[0] = j;
					king_pos[1] = i;
					break;
				}
			}
			if (king_pos[0] != -1) {
				break;
			}
		}
		if (king_pos[0] == -1) {
			return false;
		}
		int check_turn[2][2];
		check_turn[1][0] = king_pos[0];
		check_turn[1][1] = king_pos[1];
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (cells[i][j]->get_color() == -king_color) {
					check_turn[0][0] = j;
					check_turn[0][1] = i;
					if (cells[i][j]->check_move(check_turn, cells)) {
						return true;
					}
				}
			}
		}
		return false;
	}
	/**
	 * `bool is_check()` - перегрузка для инкапсуляции
	 */
	bool is_check() {
		return is_check(player_color);
	}
	/**
	 * `int is_mate(Board &board)` - проверка на мат
	 * Возвращает: 1 - мат белым, -1 - мат черным, 0 - нет мата
	 */
	int is_mate(Board &board) {
		if (!is_check(player_color)) {
			return 0;
		}
		int maybe_turn[2][2];
		for (int start_i = 0; start_i < 8; start_i++) {
			for (int start_j = 0; start_j < 8; start_j++) {
				if (cells[start_i][start_j]->get_color() == player_color) {
					for (int end_i = 0; end_i < 8; end_i++) {
						for (int end_j = 0; end_j < 8; end_j++) {
							if (start_i == end_i && start_j == end_j) continue;
							maybe_turn[0][1] = start_i;
							maybe_turn[0][0] = start_j;
							maybe_turn[1][0] = end_j;
							maybe_turn[1][1] = end_i;
							if (!cells[start_i][start_j]->check_move(maybe_turn, cells)) {
								continue;
							}
							Board * try_board = new Board(board);
							try_board->player_color = player_color;
							swap(try_board->cells[start_i][start_j], try_board->cells[end_i][end_j]);
							delete try_board->cells[start_i][start_j];
							try_board->cells[start_i][start_j] = new Empty();
							if (!try_board->is_check(player_color)) {
								delete try_board;
								return 0;
							}
							delete try_board;
						}
					}
				}
			}
		}
		return player_color;
	}
};

int main() {
	Board * board = new Board;
	string turn;
	int color;
	int mate = 0;
	cout << "Annotation (examples):\ne2-e4\naxb3\nKe2-f2\n";
	while (mate == 0) {
		for (int i = 0; i < 100; i++) {
			cout << endl;
		}
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
		mate = board->is_mate(*board);
	}
	for (int i = 0; i < 100; i++) {
			cout << endl;
		}
		cout << board->render() << endl;
	if (mate == 1) {
		cout << "White won!";
	} else {
		cout << "Black won!";
	}
	delete board;
	return 0;
}
