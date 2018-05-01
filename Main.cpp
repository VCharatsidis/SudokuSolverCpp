#include "Board.h";
#include "HardestSudoku.cpp";
#include "BoardDrawer.cpp";
#include <tuple>;
#include <iostream>;
#include <string>;
#include "Scores.h";

using std::tuple;
using std::cout;

int main() {
	HardestSudoku* hardestSudokuCreator = new HardestSudoku();
	vector<vector<int>> hardestSudoku = hardestSudokuCreator->returnHardestSudoku();

	Board* sudokuBoard = new Board(hardestSudoku);
	BoardDrawer* drawer = new BoardDrawer();

	//test draw_board and HardestSudoku.
	drawer->draw_board(hardestSudoku);

	SudokuMove* move = new SudokuMove();
	Box* box = new Box(0, 1);
	move->box = box;
	move->value = 7;

	//test play_move;
	sudokuBoard->play_move(*move);
	drawer->draw_board(sudokuBoard->board);

	//test undo_move;
	sudokuBoard->undo_move();
	drawer->draw_board(sudokuBoard->board);

	// test empty_boxes;
	stack<Box> eb = sudokuBoard->empty_boxes();
	int number_of_empty_boxes = eb.size();
	cout << "empty boxes number " + std::to_string(number_of_empty_boxes) << std::endl;
	
	for (int i = 0; i < number_of_empty_boxes; i++) {
		Box box = eb.top();

		int x = box.row;
		int y = box.column;
		eb.pop();
		cout << std::to_string(x)+","+ std::to_string(y) + " | ";
	}
	cout << " " << std::endl;

	// test Scores.
	Scores* sc = Scores::instance();
	double kati = sc->scores.at(1);
	cout << "score of 1 = " + std::to_string(kati) << std::endl;

	//test find_container_box
	//container box is denoted by its first element.
	Box* box1 = new Box(0, 0);
	Box container_box1 = sudokuBoard->find_container_starting_box(*box1);

	Box* box2 = new Box(3, 7);
	Box container_box2 = sudokuBoard->find_container_starting_box(*box2);

	Box* box3 = new Box(8, 8);
	Box container_box3 = sudokuBoard->find_container_starting_box(*box3);

	string x1 = std::to_string(container_box1.row);
	string y1 = std::to_string(container_box1.column);

	string x2 = std::to_string(container_box2.row);
	string y2 = std::to_string(container_box2.column);

	string x3 = std::to_string(container_box3.row);
	string y3 = std::to_string(container_box3.column);

	cout << "container box1 " + x1 + " , " + y1 << std::endl;
	cout << "container box2 " + x2 + " , " + y2 << std::endl;
	cout << "container box3 " + x3 + " , " + y3 << std::endl;
	//check validity_check
	/*string value_is_valid;
	vector<int> row1 = sudokuBoard->board[6];
	bool valid_row = sudokuBoard->validity_check(row1, 8);
	if (valid_row) {
		value_is_valid = " True ";
	}
	else {
		value_is_valid = " False";
	}
	cout << " check row 0 value 8 " + value_is_valid << std::endl;

	valid_row = sudokuBoard->validity_check(row1, 2);
	if (valid_row) {
		value_is_valid = " True ";
	}
	else {
		value_is_valid = " False";
	}
	cout << " check row 0 value 2 " + value_is_valid << std::endl;

	valid_row = sudokuBoard->validity_check(row1, 3);
	if (valid_row) {
		value_is_valid = " True ";
	}
	else {
		value_is_valid = " False";
	}
	cout << " check row 0 value 3 " + value_is_valid << std::endl;

	valid_row = sudokuBoard->validity_check(row1, 4);
	if (valid_row) {
		value_is_valid = " True ";
	}
	else {
		value_is_valid = " False";
	}
	cout << " check row 0 value 4 " + value_is_valid << std::endl;

	valid_row = sudokuBoard->validity_check(row1, 1);
	if (valid_row) {
		value_is_valid = " True ";
	}
	else {
		value_is_valid = " False";
	}
	cout << " check row 0 value 1 " + value_is_valid << std::endl;*/

 	//check is_move_valid
	SudokuMove* valid_move = new SudokuMove();
	Box* box_valid = new Box(0, 1);
	int valid_value = 2;
	valid_move->box = box_valid;
	valid_move->value = valid_value;

	bool is_valid = sudokuBoard->is_move_valid(*valid_move);
	string valid_string;
	if (is_valid) {
		valid_string = "true";
	}
	else {
		valid_string = "false";
	}
	cout << "is valid [0,1] : "+ std::to_string(valid_value)+" "+ valid_string;
	//check legal_moves
	/*stack<SudokuMove> moves = sudokuBoard->legal_moves();
	cout << "legal moves of box [0,1] ";
	int size = moves.size();
	for (int i = 0; i < size; i++) {
		SudokuMove current = moves.top();
		if (current.box->row == 0 && current.box->column == 1) {
			cout << " " + std::to_string(current.value);
		}	
	}*/

	return 0;
};