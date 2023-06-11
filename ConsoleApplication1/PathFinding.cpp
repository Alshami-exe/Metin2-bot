#include "PathFinding.h"
#include <iostream>
PathFinding::PathFinding(int Width, int Height, int** Map) {
	PathFinding::width = Width;
	PathFinding::height = Height;
	PathFinding::map = new int* [width];
	for (int i = 0; i < width; ++i) {
		map[i] = new int[height];
	}
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			if (Map[i][j] == 1 || Map[i][j]==2) {
				map[i][j] = 0;
			}else
			map[i][j] = Map[i][j];
		}
	}
	PathFinding::visited = new int* [width];
	for (int i = 0; i < width; ++i) {
		visited[i] = new int[height];
	}
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			visited[i][j] = 0;
		}
	}
	PathFinding::byWho = new int* [width];
	for (int i = 0; i < width; ++i) {
		byWho[i] = new int[height];
	}
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			byWho[i][j] = -1;
		}
	}
	PathFinding::movesCount = new int* [width];
	for (int i = 0; i < width; ++i) {
		movesCount[i] = new int[height];
	}
	
};
PathFinding::PathFinding() {

}
int* PathFinding::getPath(int x, int y) {
	int* path;
	//std::cout << "GetPath phase 0 done " << movesCount[x][y] << std::endl;
	if (10000000 == movesCount[x][y]) {
		//std::cout << "No Path Found!" << std::endl;
		path = new int[2];
		path[0] = 2;
		path[1] = -1;
		return path;
	}
	path = new int[movesCount[x][y] + 2];
	//std::cout << "GetPath phase 1 done" << std::endl;
	path[0] = movesCount[x][y] + 2;
	path[1] = (x * 10000 + y)*10+9;
	int count = 2;
	int tx, ty, tm, twho = byWho[x][y];
	//std::cout << "GetPath phase 2 done" << std::endl;
	do {
		tm = twho % 10;
		twho /= 10;
		ty = twho % 10000;
		twho /= 10000;
		tx = twho % 10000;
		path[count] = ((tx * 10000 + ty) * 10 + tm);
		twho = byWho[tx][ty];
		++count;
	} while (map[tx][ty] != 1);
	//std::cout << "GetPath phase 3 done" << std::endl;
	return path;
}
bool PathFinding::pathfinding(int x, int y) {	
	if (x <= -1 || y <= -1 || x >= width || y >= height) {
		return false;
	}

	if (map[x][y] == 3) {
		//wall what to do?

		return false;
	}
	else if (visited[x][y] == 0) {
		// Not Visited what to do?
		visited[x][y] = 1; // make it visited!

		getMinimumMoves(x, y);
		pathfinding(x, y + 1);
		pathfinding(x, y - 1);
		pathfinding(x + 1, y);
		pathfinding(x - 1, y);
		pathfinding(x + 1, y + 1);
		pathfinding(x - 1, y - 1);
		pathfinding(x + 1, y - 1);
		pathfinding(x - 1, y + 1);

	}
	else if (visited[x][y] == 1)
	{
		if (movesCount[x][y] > getMinimumMoves(x, y)) {
			pathfinding(x, y + 1);
			pathfinding(x, y - 1);
			pathfinding(x + 1, y);
			pathfinding(x - 1, y);
			pathfinding(x + 1, y + 1);
			pathfinding(x - 1, y - 1);
			pathfinding(x + 1, y - 1);
			pathfinding(x - 1, y + 1);
		}
		// visited what to do?
	}


	return false;

}
int PathFinding::getMinimumMoves(int x, int y) {
	if (y + 1 < height && movesCount[x][y + 1] + 1 < movesCount[x][y]) {
		movesCount[x][y] = movesCount[x][y + 1] + 1;
		byWho[x][y] = ((x) * 10000 + (y + 1)) * 10 + 4;
	}
	if (y - 1 > -1 && movesCount[x][y - 1] + 1 < movesCount[x][y]) {
		movesCount[x][y] = movesCount[x][y - 1] + 1;
		byWho[x][y] = ((x) * 10000 + (y - 1)) * 10 + 2;
	}
	if (x + 1 < width && movesCount[x + 1][y] + 1 < movesCount[x][y]) {
		movesCount[x][y] = movesCount[x + 1][y] + 1;
		byWho[x][y] = ((x + 1) * 10000 + (y)) * 10 + 1;
	}
	if (x - 1 > -1 && movesCount[x - 1][y] + 1 < movesCount[x][y]) {
		movesCount[x][y] = movesCount[x - 1][y] + 1;
		byWho[x][y] = ((x - 1) * 10000 + (y)) * 10 + 3;
	}
	if (x + 1 < width && y + 1 < height && movesCount[x + 1][y + 1] + 1 < movesCount[x][y]) {
		movesCount[x][y] = movesCount[x + 1][y + 1] + 1;
		byWho[x][y] = ((x + 1) * 10000 + (y + 1)) * 10 + 8;
	}
	if (y - 1 > -1 && x - 1 > -1 && movesCount[x - 1][y - 1] + 1 < movesCount[x][y]) {
		movesCount[x][y] = movesCount[x - 1][y - 1] + 1;
		byWho[x][y] = ((x - 1) * 10000 + (y - 1)) * 10 + 6;
	}
	if (x - 1 > -1 && y + 1 < height && movesCount[x - 1][y + 1] + 1 < movesCount[x][y]) {
		movesCount[x][y] = movesCount[x - 1][y + 1] + 1;
		byWho[x][y] = ((x - 1) * 10000 + (y + 1)) * 10 + 7;
	}
	if (y - 1 > -1 && x + 1 < width && movesCount[x + 1][y - 1] + 1 < movesCount[x][y]) {
		movesCount[x][y] = movesCount[x + 1][y - 1] + 1;
		byWho[x][y] = ((x + 1) * 10000 + (y - 1)) * 10 + 5;
	}
	//cout << "(" << x << "," << y << ") " << "Visited By " << byWho[x][y] << " With " << movesCount[x][y] << " Moves" << endl;
	return movesCount[x][y];
}
int* PathFinding::Pathfinding(int xStartPoint, int yStartPoint, int xEndPoint, int yEndPoint) {
	
	if (xStartPoint == xEndPoint && yStartPoint == yEndPoint) {
		int* x = new int[2];
		 x[0] = 2;
		 x[1] = (xStartPoint * 10000 + yEndPoint) * 10 + 9;
		return x;
	}
	
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			if (i == xStartPoint && j == yStartPoint)
			{
				map[i][j] = 1;
				movesCount[i][j] = 0;
				//visited[i][j] = 1;
			}
			else if (i == xEndPoint && j == yEndPoint) {
				map[i][j] = 2;
				movesCount[i][j] = 10000000;
				//visited[i][j] = 0;
			}
			else {
				movesCount[i][j] = 10000000;
				//visited[i][j] = 0;
			}
		}
	}
	pathfinding(xStartPoint, yStartPoint);
	

	/* Finds 1 and 2
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			if (map[i][j] == 1)
				std::cout << i << " " << j << " this is 1" << std::endl;
			if (map[i][j] == 2)
				std::cout << i << " " << j << " this is 2" << std::endl;
		}
		
	}
	*/

	return getPath(xEndPoint, yEndPoint);
}
void PathFinding::UpdateMap(int** Map) {

	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			if (Map[i][j] == 1 || Map[i][j] == 2) {
				map[i][j] = 0;
			}
			else {
				map[i][j] = Map[i][j];
			}
		}
	}

	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			byWho[i][j] = -1;
		}
	}

	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			visited[i][j] = 0;
		}
	}
	
}
void PathFinding::PrintMap() {
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			std::cout << map[i][j];
		}
		std::cout << std::endl;
	}
}
void PathFinding::DeleteMap() {
	for (int i = 0; i < width; ++i) {
		delete[] map[i];
	}
	delete[] map;
	for (int i = 0; i < width; ++i) {
		delete[] visited[i];
	}
	delete[] visited;
	for (int i = 0; i < width; ++i) {
		delete[] byWho[i];
	}
	delete[] byWho;
	for (int i = 0; i < width; ++i) {
		delete[] movesCount[i];
	}
	delete[] movesCount;

}