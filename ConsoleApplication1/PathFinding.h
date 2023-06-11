#pragma once

class PathFinding
{
public: //vars

private : //vars
	int width, height;
	
	int** map; //int* map;
	int** visited; //visited[width][height];
	int** byWho; //byWho[width][height];
	int** movesCount;//movesCount[width][height];

public: //meth
	int* Pathfinding(int xStartPoint, int yStartPoint, int xEndPoint, int yEndPoint);
	PathFinding(int , int,int**);
	PathFinding();
	void UpdateMap(int** Map);
	void PrintMap();
	void DeleteMap();
	//int* backToTrack(int xStartPoint,int yStartPoint);

private: //meth
	bool pathfinding(int x, int y);
	int getMinimumMoves(int x, int y);
	int* getPath(int x, int y);
};

