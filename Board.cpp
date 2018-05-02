#include "Board.h";
#include <math.h>;
#include "Scores.h";
#include <string>;
#include <iostream>;

int empty_box_value = 0;
int container_size;

int Board::sudoku_size;
vector<vector<int>> Board::board;//(sudoku_size, vector<int>(sudoku_size, empty_box_value));
stack<SudokuMove*> Board::moves_done;

Board::Board(vector<vector<int>> board) {
	sudoku_size = board.size();
	container_size = sqrt(sudoku_size);
	Board::board = board;
	
}

void Board::assign_value(Box* box, int value) {
	Board::board[box->row][box->column] = value;
}

void Board::play_move(SudokuMove* move) {
	int value = move->value;
	//std::cout << "Play move " + std::to_string(move->box->row) + ", " + std::to_string(move->box->column) +" value: "+ std::to_string(move->value) << std::endl;
	//std::cout << "" << std::endl;
	assign_value(move->box, value);
	Board::moves_done.push(move);

	stack<SudokuMove*> s;
	//s = moves_done;
	//print_stack(s);
}

void Board::print_stack(stack<SudokuMove*> c) {
	std::cout << "" << std::endl;
	while (!c.empty()) {
		SudokuMove m = *c.top();
		Box b = *m.box;
		int x = b.row;
		int y = b.column;
		std::cout << std::to_string(x) + ", " + std::to_string(y) + " value " + std::to_string(m.value) + "||";
		c.pop();
	}
	std::cout << "" << std::endl;
}

void Board::undo_move() {
	
	SudokuMove move_to_undo = *Board::moves_done.top();
	//std::cout << "Undo move "+std::to_string(move_to_undo.box->row)+", "+std::to_string(move_to_undo.box->column) + " value: " + std::to_string(move_to_undo.value) << std::endl;
	assign_value(move_to_undo.box, empty_box_value);
	Board::moves_done.pop();	
}

bool Board::is_empty(Box box) {
	return Board::board[box.row][box.column] == empty_box_value;
}

stack<Box*> Board::empty_boxes() {
	stack<Box*> emptyBoxes;

	for (int row = 0; row < sudoku_size; row++) {
		for (int column = 0; column < sudoku_size; column++) {
			Box* box = new Box(row, column);
			
			if (Board::is_empty(*box)) {
				emptyBoxes.push(box);
			}
			else {
				delete box;
			}
		}
	}
	return emptyBoxes;
}

vector<SudokuMove*> Board::legal_moves() {
	vector<SudokuMove*> legal_moves;
	stack<Box*> empty_boxes = Board::empty_boxes();
	//std::cout << " empty_boxes size " +std::to_string(empty_boxes.size()) << std::endl;
	bool empty_box_exists = !empty_boxes.empty();
	bool first=true;
	while (empty_box_exists) {
		Box b = *empty_boxes.top();
		if (first) {
			//std::cout << "legal moves of box [" + std::to_string(box->row) + "," + std::to_string(box->column) + "] ";
		}
		for (int value = 1; value < sudoku_size+1; value++) {
			SudokuMove* move = new SudokuMove();
			Box* box = new Box(b.row, b.column);
			move->box = box;
			move->value = value;

			if (is_move_valid(*move)) {
				if (first) {
					//std::cout << "value "+std::to_string(move->value);
				}
				legal_moves.push_back(move);
			}
			else {
				delete box;
				delete move;
			}
		}
		
		first = false;
		delete empty_boxes.top();
		empty_boxes.pop();
		empty_box_exists = !empty_boxes.empty();
	}

	for (int i = 0; i < empty_boxes.size(); i++) {
		delete empty_boxes.top();
	}
	//std::cout << "legal moves " + std::to_string(legal_moves.size()) << std::endl;
	return legal_moves;
}

bool Board::is_move_valid(SudokuMove move) {
	int row = move.box->row;
	int column = move.box->column;
	int value = move.value;

	bool valid_row = is_value_valid(board[row], value);

	if (valid_row) {
		
		vector<int> column_boxes = gather_column_boxes(column);
		bool valid_column = is_value_valid(column_boxes, value);

		if (valid_column) {
			
			Box box = find_container_starting_box(*move.box);
			vector<int> container_boxes = gather_container_boxes(box);
			bool valid_container = is_value_valid(container_boxes, value);

			if (valid_container) {
				return true;
			}
		}
	}
	return false;
}

vector<int> Board::gather_column_boxes(int given_column) {
	vector<int> column_boxes;

	for(int row = 0; row < sudoku_size; row++) {
		column_boxes.push_back(Board::board[row][given_column]);
	}

	return column_boxes;
}

vector<int> Board::gather_container_boxes(Box starting_box) {
	vector<int> container_boxes;

	int start_row = starting_box.row;
	int end_row = start_row + container_size;
	int start_column = starting_box.column;
	int end_column = start_column + container_size;

	//std::cout << " start_row " + std::to_string(start_row) + " start_column " + std::to_string(start_column) << std::endl;
	for (int x = start_row; x < end_row; x++) {
		for (int y = start_column; y < end_column; y++) {
			container_boxes.push_back(Board::board[x][y]);
		}
	}

	return container_boxes;
}

bool Board::is_value_valid(vector<int> box_structure, int value) {
	int box_structure_size = box_structure.size();

	for (int box = 0; box < box_structure_size; box++) {
		
		int box_value = box_structure[box];
		
		bool is_not_valid = (box_value == value);

		if (is_not_valid) {
			return false;
		}	
	}

	return true;
}

Box Board::find_container_starting_box(Box box) {
	
	int container_x = box.row/container_size;
	int container_y = box.column/container_size;

	int starting_box_x = container_x * container_size;
	int starting_box_y = container_y * container_size;

	Box* starting_box = new Box(starting_box_x, starting_box_y);
	return *starting_box;
}

bool Board::game_over() {
	bool game_over = (empty_boxes().size() == 0);

	if (game_over) {
		return true;
	}
	else {
		return false;
	}
}
 






