#pragma once
#pragma once
#include "NodeMatrix.h"
#include <cstdlib>
#include <vector>

struct Cell {
	int row;
	int col;
};

class Maze {
public:
	Maze(int sz, int sd, int alg); //add rand() seed
	~Maze();
	bool PickNextK(int& count);
	Node PickNextP(std::vector<Cell>& moves);
	Cell FindGroup(int r, int c);
	void GenerateStart(std::vector<Cell>& moves, std::vector<Node>& added);
	void ConnectPieces(int r, int c, int tR, int tC);
	bool FindPath(int r, int c, int& count);
	void Print();
	int getPathSize() {
		return pathSize;
	}

private:
	NodeMatrix* maze;
	int size;
	int seed;
	int pathSize;
};

Maze::Maze(int sz, int sd, int alg) {
	size = sz;
	seed = sd;
	pathSize = 1;
	srand(seed);
	maze = new NodeMatrix(size);
	int count = 0;
	maze->matrix[0][0].route = true;
	///////////////////////////////////////
	if (alg == 1) {

		while (count < size * size - 1) {
			PickNextK(count);
		}

	}

	///////////////////////////////////////
	else {
		std::vector<Cell> moves;
		std::vector<Node> added;
		GenerateStart(moves, added);
		while (moves.size() > 0) {
			added.push_back(PickNextP(moves));
		}

	}

	FindPath(0, 0, pathSize);
}

bool Maze::PickNextK(int& count) { //Kruskal's alg
	int row = rand() % size;
	int col = rand() % size;
	int next = rand() % 4;
	Node* cell;
	cell = &maze->matrix[row][col];

	if (next == 0) {
		if (col - 1 < 0) {
			return false;
		}
		else if (cell->FindRoot() == maze->matrix[row][col - 1].FindRoot()) {
			return false;
		}
		else if (maze->matrix[row][col - 1].right == true) {
			return false;
		}
		else {
			count++;
			maze->matrix[row][col - 1].right = true;
			if (maze->matrix[row][col - 1].parent != nullptr) {
				Node* temp;
				temp = maze->matrix[row][col - 1].FindRoot();
				cell->Insert(temp);
			}
			else if (maze->matrix[row][col - 1].parent == nullptr) {
				cell->Insert(&maze->matrix[row][col - 1]);
			}
			return true;
		}
	}
	else if (next == 1) {
		if (row - 1 < 0) {
			return false;
		}
		else if (cell->FindRoot() == maze->matrix[row - 1][col].FindRoot()) {
			return false;
		}
		else if (maze->matrix[row - 1][col].right == true) {
			return false;
		}
		else {
			count++;
			maze->matrix[row - 1][col].down = true;
			if (maze->matrix[row - 1][col].parent != nullptr) {
				Node* temp;
				temp = maze->matrix[row - 1][col].FindRoot();
				cell->Insert(temp);
			}
			else if (maze->matrix[row - 1][col].parent == nullptr) {
				cell->Insert(&maze->matrix[row - 1][col]);
			}
			return true;
		}
	}
	else if (next == 2) {
		if (col + 1 >= size) {
			return false;
		}
		else if (cell->FindRoot() == maze->matrix[row][col + 1].FindRoot()) {
			return false;
		}
		else if (maze->matrix[row][col + 1].right == true) {
			return false;
		}
		else {
			count++;
			cell->right = true;
			if (maze->matrix[row][col + 1].parent != nullptr) {
				Node* temp;
				temp = maze->matrix[row][col + 1].FindRoot();
				cell->Insert(temp);
			}
			else if (maze->matrix[row][col + 1].parent == nullptr) {
				cell->Insert(&maze->matrix[row][col + 1]);
			}
			return true;
		}
	}
	else {
		if (row + 1 >= size) {
			return false;
		}
		else if (cell->FindRoot() == maze->matrix[row + 1][col].FindRoot()) {
			return false;
		}
		else if (maze->matrix[row + 1][col].right == true) {
			return false;
		}
		else {
			count++;
			cell->down = true;
			if (maze->matrix[row + 1][col].parent != nullptr) {
				Node* temp;
				temp = maze->matrix[row + 1][col].FindRoot();
				cell->Insert(temp);
			}
			else if (maze->matrix[row + 1][col].parent == nullptr) {
				cell->Insert(&maze->matrix[row + 1][col]);
			}
			return true;
		}
	}
}

Node Maze::PickNextP(std::vector<Cell>& moves) {
	int row, col;
	int rPick = 0;
	if (moves.size() > 0) {
		int rPick = rand() % moves.size();
	}
	Cell pick = moves[rPick];
	Cell add, from;
	from = FindGroup(pick.row, pick.col);
	ConnectPieces(from.row, from.col, pick.row, pick.col);
	moves.erase(moves.begin() + rPick);
	if (pick.row > 0) {
		row = pick.row - 1;
		col = pick.col;
		if (maze->matrix[row][col].group != 0 && maze->matrix[row][col].group != 1) {
			maze->matrix[row][col].group = 1;
			add.row = row;
			add.col = col;
			if (rand() % 2 == 0) {
				moves.push_back(add);
			}
			else {
				moves.insert(moves.begin(), add);
			}
		}
	}
	if (pick.row + 1 < size) {
		row = pick.row + 1;
		col = pick.col;
		if (maze->matrix[row][col].group != 0 && maze->matrix[row][col].group != 1) {
			maze->matrix[row][col].group = 1;
			add.row = row;
			add.col = col;
			if (rand() % 2 == 0) {
				moves.push_back(add);
			}
			else {
				moves.insert(moves.begin(), add);
			}
		}
	}
	if (pick.col > 0) {
		col = pick.col - 1;
		row = pick.row;
		if (maze->matrix[row][col].group != 0 && maze->matrix[row][col].group != 1) {
			maze->matrix[row][col].group = 1;
			add.row = row;
			add.col = col;
			if (rand() % 2 == 0) {
				moves.push_back(add);
			}
			else {
				moves.insert(moves.begin(), add);
			}
		}
	}
	if (pick.col + 1 < size) {
		col = pick.col + 1;
		row = pick.row;
		if (maze->matrix[row][col].group != 0 && maze->matrix[row][col].group != 1) {
			maze->matrix[row][col].group = 1;
			add.row = row;
			add.col = col;
			if (rand() % 2 == 0) {
				moves.push_back(add);
			}
			else {
				moves.insert(moves.begin(), add);
			}
		}
	}

	return maze->matrix[pick.row][pick.col];
}

Cell Maze::FindGroup(int r, int c) { //put in rand from group 1
	Cell result;
	result.row = -1;
	result.col = -1;

	while (result.col == -1) {
		int pick = rand() % 4;

		if (pick == 0 && r - 1 >= 0 && maze->matrix[r - 1][c].group == 0) {
			result.row = r - 1;
			result.col = c;
		}
		else if (pick == 1 && r + 1 < size && maze->matrix[r + 1][c].group == 0) {
			result.row = r + 1;
			result.col = c;
		}
		else if (pick == 2 && c - 1 >= 0 && maze->matrix[r][c - 1].group == 0) {
			result.row = r;
			result.col = c - 1;
		}
		else if (pick == 3 && c + 1 < size && maze->matrix[r][c + 1].group == 0) {
			result.row = r;
			result.col = c + 1;
		}
		else {
			//std::cout << "No valid moves!" << std::endl;
		}
	}
	return result;
}

void Maze::GenerateStart(std::vector<Cell>& moves, std::vector<Node>& added) {
	int row = rand() % size;
	int col = rand() % size;
	Cell temp;
	maze->matrix[row][col].group = 0;
	added.push_back(maze->matrix[row][col]);

	if (row > 0) {
		maze->matrix[row - 1][col].group = 1;
		temp.row = row - 1;
		temp.col = col;
		moves.push_back(temp);
	}
	if (col > 0) {
		maze->matrix[row][col - 1].group = 1;
		temp.row = row;
		temp.col = col - 1;
		moves.push_back(temp);
	}
	if (row + 1 < size) {
		maze->matrix[row + 1][col].group = 1;
		temp.row = row + 1;
		temp.col = col;
		moves.push_back(temp);
	}
	if (col + 1 < size) {
		maze->matrix[row][col + 1].group = 1;
		temp.row = row;
		temp.col = col + 1;
		moves.push_back(temp);
	}
}

void Maze::ConnectPieces(int r, int c, int tR, int tC) {
	if (r < tR) {
		//move down
		maze->matrix[r][c].down = true;
		maze->matrix[tR][tC].group = 0;
	}
	else if (r > tR) {
		//move up
		maze->matrix[tR][c].down = true;
		maze->matrix[tR][tC].group = 0;
	}
	else if (c < tC) {
		//move right
		maze->matrix[r][c].right = true;
		maze->matrix[tR][tC].group = 0;
	}
	else {
		//move left
		maze->matrix[r][tC].right = true;
		maze->matrix[tR][tC].group = 0;
	}
}

bool Maze::FindPath(int r, int c, int& count) {
	int row;
	int col;
	std::vector<Cell> moves;
	if (r == size - 1 && c == size - 1) {
		return true;
	}
	if (c > 0) {
		col = c - 1;
		if (!maze->matrix[r][col].route && maze->matrix[r][col].right) {
			Cell move;
			move.row = r;
			move.col = col;
			moves.insert(moves.begin(), move);
		}
	}
	if (c + 1 < size) {
		col = c + 1;
		if (!maze->matrix[r][col].route && maze->matrix[r][c].right) {
			Cell move;
			move.row = r;
			move.col = col;
			moves.insert(moves.begin(), move);
		}
	}
	if (r > 0) {
		row = r - 1;
		if (!maze->matrix[row][c].route && maze->matrix[row][c].down) {
			Cell move;
			move.row = row;
			move.col = c;
			moves.insert(moves.begin(), move);
		}
	}
	if (r + 1 < size) {
		row = r + 1;
		if (!maze->matrix[row][c].route && maze->matrix[r][c].down) {
			Cell move;
			move.row = row;
			move.col = c;
			moves.insert(moves.begin(), move);
		}
	}
	size_t s = moves.size();
	for (int i = 0; i < s; i++) {
		int iRow, iCol;
		Cell temp;
		temp = moves.back();
		iRow = temp.row;
		iCol = temp.col;
		maze->matrix[iRow][iCol].route = true;
		count++;
		if (!FindPath(iRow, iCol, count)) {
			moves.pop_back();
			maze->matrix[iRow][iCol].route = false;
			count--;
		}
		else {
			return true;
		}
	}

	return false;
}

void Maze::Print() {
	std::cout << "+";
	for (int i = 0; i < size; i++) {
		std::cout << "--+";
	}
	std::cout << std::endl;
	for (int j = 0; j < size; j++) {
		std::cout << "|";
		for (int i = 0; i < size; i++) {
			if (maze->matrix[j][i].route == false) {
				if (maze->matrix[j][i].right == true) {
					std::cout << "   ";
				}
				else {
					std::cout << "  |";
				}
			}
			else {
				std::cout << "**";
				if (maze->matrix[j][i].right == true) {
					std::cout << " ";
				}
				else {
					std::cout << "|";
				}
			}
		}
		std::cout << std::endl;
		std::cout << "+";
		for (int i = 0; i < size; i++) {
			if (maze->matrix[j][i].down == true) {
				std::cout << "  +";
			}
			else {
				std::cout << "--+";
			}
		}
		std::cout << std::endl;
	}
	std::cout << "Path length is " << pathSize << std::endl;
	std::cout << (pathSize / 900.0) * 100 << "%." << std::endl;
}

Maze::~Maze() {
	delete maze;
}