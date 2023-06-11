/*
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

void clickAction(Event);
const int  width = 1000, height = 1000;
const int row = 7, col = 7;
VertexArray quad[row * col];
//sf::RenderWindow window(sf::VideoMode(width, height), "TITLE", sf::Style::None | sf::Style::Close);
const int widthm = 7;
const int heightm = 7;

int mapm[widthm][heightm] = {
	{-1,-1,-1,-1,-1,-1,-1},
	{-1,1,0,2,0,0,-1},
	{-1,0,0,3,3,0,-1},
	{-1,0,3,3,0,0,-1},
	{-1,0,3,0,0,0,-1},
	{-1,0,3,0,0,3,-1},
	{-1,-1,-1,-1,-1,-1,-1}
};
int visited[widthm][heightm] = { 0 };
int odx = 1, ody = 1, c = 0;
int byWho[widthm][heightm];
int movesCount[widthm][heightm];

int* getPath(int x, int y) {
	int* path = new int[movesCount[x][y]+1];
	path[0] = x * 10000 + y;
	int count = 1;
	int tx, ty,twho=byWho[x][y];
	do {
		ty = twho % 10000;
		twho /= 10000;
		tx = twho % 10000;
		path[count] = tx * 10000 + ty;
		twho = byWho[tx][ty];
		++count;
	} while (mapm[tx][ty]!=1);
	for (int i = 0; i < count; ++i) {
		cout << path[i] << endl;
	}
	return path;
}
int getMinimumMoves(int x, int y) {
	if (movesCount[x][y + 1] + 1 < movesCount[x][y]) {
		movesCount[x][y] = movesCount[x][y + 1] + 1;
		byWho[x][y] = (x ) * 10000 + (y + 1);
	}
	if (movesCount[x][y - 1] + 1 < movesCount[x][y]) {
		movesCount[x][y] = movesCount[x][y - 1] + 1;
		byWho[x][y] = (x ) * 10000 + (y - 1);
	}
	if (movesCount[x+1][y] + 1 < movesCount[x][y]) {
		movesCount[x][y] = movesCount[x + 1][y] + 1;
		byWho[x][y] = (x + 1) * 10000 + (y);
	}
	if (movesCount[x-1][y] + 1 < movesCount[x][y]) {
		 movesCount[x][y] = movesCount[x - 1][y] + 1;
		 byWho[x][y] = (x - 1) * 10000 + (y);
	}
	if (movesCount[x+1][y + 1] + 1 < movesCount[x][y]) {
		 movesCount[x][y] = movesCount[x + 1][y + 1] + 1;
		 byWho[x][y] = (x + 1) * 10000 + (y + 1);
	}
	if (movesCount[x - 1][y - 1] + 1 < movesCount[x][y]) {
		 movesCount[x][y] = movesCount[x - 1][y - 1] + 1;
		 byWho[x][y] = (x - 1) * 10000 + (y - 1);
	}
	if (movesCount[x-1][y + 1] + 1 < movesCount[x][y]) {
		 movesCount[x][y] = movesCount[x - 1][y + 1] + 1;
		 byWho[x][y] = (x- 1) * 10000 + (y + 1);
	}
	if (movesCount[x+1][y - 1] + 1 < movesCount[x][y]) {
		 movesCount[x][y] = movesCount[x + 1][y - 1] + 1;
		 byWho[x][y] = (x+1) * 10000 + (y-1);
	}
	cout << "(" << x << "," << y << ") " << "Visited By " << byWho[x][y] << " With " << movesCount[x][y] << " Moves" << endl;
	return movesCount[x][y];
}
bool pathfinding(int x, int y) {
	
	if (x == 0 || y == 0 || x == widthm - 1 || y == heightm - 1) {
		//corners what to do?
		return false;
	}
	
	if (mapm[x][y] == 3) {
		//wall what to do?
		
		return false;
	}
	else if (visited[x][y] == 0) {
		// Not Visited what to do?
		visited[x][y] = 1; // make it visited!
	
		getMinimumMoves(x, y);
		odx = x;
		ody = y;
		system("pause");
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
		getMinimumMoves(x, y);

		// visited what to do?
	}
	
	
	
	return false;

}

/*
int main()
{
	for (int i = 0; i < widthm; ++i) {
		for (int j = 0; j < heightm; ++j) {
			if (mapm[i][j] == 1)
				movesCount[i][j] = 0;
			else
				movesCount[i][j] = 10000000;
		}
	}
	
	

	
	
	

	quad[0] = VertexArray(Quads, 4);
	int mabx=0, maby=0;
	float boxW =width/(float)row, boxH = height/(float)col;
	for(int i =0,y=0,x=0;i<row*col;++i){
		quad[i] = VertexArray(Quads, 4);
		
			quad[i][0].position = Vector2f(boxW*(x) , y);            //(0,0)    ,(250,0)
			quad[i][1].position = Vector2f(boxW*((x+1)), y);      //(250,0)  ,(500,0)
			quad[i][2].position = Vector2f(boxW*((x+1)), boxH + y);//(250,250),(500,250)
			quad[i][3].position = Vector2f(boxW*(x), boxH +y);      //(0,250)  ,(250,250)
			if (mapm[mabx][maby] == -1) {
				quad[i][0].color = Color::Red;
				quad[i][1].color = Color::Red;
				quad[i][2].color = Color::Red;
				quad[i][3].color = Color::Red;
			}
		else if(mapm[mabx][maby] == 0) {
			quad[i][0].color = Color::White;
			quad[i][1].color = Color::White;
			quad[i][2].color = Color::White;
			quad[i][3].color = Color::White;
		}
		else if (mapm[mabx][maby] == 2) {
				quad[i][0].color = Color::Yellow;
				quad[i][1].color = Color::Yellow;
				quad[i][2].color = Color::Yellow;
				quad[i][3].color = Color::Yellow;
			}
		else if (mapm[mabx][maby] == 3) {
				quad[i][0].color = Color::Black;
				quad[i][1].color = Color::Black;
				quad[i][2].color = Color::Black;
				quad[i][3].color = Color::Black;
			}
		else if (mapm[mabx][maby] == 1) {
				quad[i][0].color = Color::Green;
				quad[i][1].color = Color::Green;
				quad[i][2].color = Color::Green;
				quad[i][3].color = Color::Green;
			}

		if ((i + 1) % col == 0) {
			y += boxH;
			x = 0;
			++mabx;
			maby = 0;
		}
		else {
			++x;
			++maby;
		}
	}
	
	
	sf::Event e;
	bool lock_click = false;
	while (window.isOpen()) {

		while (window.pollEvent(e)) {
			if (e.type == sf::Event::Closed) {
				window.close();
			}
			if (e.MouseButtonPressed && lock_click != true) {
				if (e.mouseButton.button == Mouse::Left) {
					
					pathfinding(1, 1);
					for (int i = 0; i < widthm; ++i) {
						for (int j = 0; j < heightm; ++j) {
							cout << " | (" << i << "," << j << ") " << byWho[i][j];
						}cout<<endl;
					}
					cout << endl;
					int* xx=getPath(5, 4);
					
				}
				if (e.mouseButton.button == Mouse::Right)
				{
					lock_click = true;
					clickAction( e);
					lock_click = false;
				}

			}
			if (e.type == sf::Event::MouseButtonReleased) //Mouse button Released now.
			{
				if (e.mouseButton.button == sf::Mouse::Left) //specifies the held button       again. (You can make a variable for that if you want)
				{
					lock_click = false; //unlock when the button has been released.
				}
			}
		}
		
		
		window.clear();
		
		for (int i = 0; i< col*row; ++i) {
			window.draw(quad[i]);
		
		}
		window.display();
	}
	return 0;
}

void clickAction( Event e) {
	int x = width / row;
	int y = height / col;
	int quadClicked = (e.mouseButton.y / y) * row + (e.mouseButton.x / x);
	if (e.mouseButton.button == Mouse::Left) {

		

		quad[quadClicked][0].color = Color::Red;
		quad[quadClicked][1].color = Color::Red;
		quad[quadClicked][2].color = Color::Red;
		quad[quadClicked][3].color = Color::Red;
	}
	if (e.mouseButton.button == Mouse::Right) {
		quad[quadClicked][0].color = Color::Yellow;
		quad[quadClicked][1].color = Color::Yellow;
		quad[quadClicked][2].color = Color::Yellow;
		quad[quadClicked][3].color = Color::Yellow;
	}



}



/*
++c;
	if (x < 0 || y < 0)
		return false;
	if (mapm[x][y] == -1)
	{
		//std::cout << "(" << x << "," << y << ") " << "is -1" << std::endl;
		quad[(x * widthm) + y][0].color = Color::Blue;
		quad[(x * widthm) + y][1].color = Color::Red;
		quad[(x * widthm) + y][2].color = Color::Blue;
		quad[(x * widthm) + y][3].color = Color::Red;
		return false;
	}
	else if (visited[x][y] == 1) {
		cout <<"("<<odx<<","<<ody<<") Visited " << "(" << x << "," << y << ") By " << (byWho[odx][ody] % 100 + 1) << " Moves But The Old Is " << (byWho[x][y] % 100) << endl;


		//search if it's lower path

	}
	else if (mapm[x][y] == 3) {
		//std::cout << "(" << x << "," << y << ") " << "is a Wall" << std::endl;
		quad[(x * widthm) + y][0].color = Color::Blue;
		quad[(x * widthm) + y][1].color = Color::Black;
		quad[(x * widthm) + y][2].color = Color::Blue;
		quad[(x * widthm) + y][3].color = Color::Black;
		return false;
	}
	else if (visited[x][y] == 0) {
		visited[x][y] = 1;

		if (byWho[x - 1][y - 1] % 100 < c) {
			c = byWho[x - 1][y - 1] % 100;
			byWho[x][y] = ((x - 1) * 1000000) + ((y - 1) * 1000) + (c);
			cout << "Case 1 " << byWho[x][y] << endl;
		}
		else if (byWho[x - 1][y] % 100 < c) {
			c = byWho[x - 1][y] % 100;
			byWho[x][y] = ((x - 1) * 1000000) + ((y) * 1000) + (c);
			cout << "Case 2 " <<byWho[x][y] << endl;
		}
		else if (byWho[x - 1][y + 1] % 100 < c) {
			c = byWho[x - 1][y + 1] % 100;
			byWho[x][y] = ((x - 1) * 1000000) + ((y + 1) * 1000) + (c);
			cout << "Case 3 " << byWho[x][y] << endl;
		}
		else if (byWho[x][y + 1] % 100 < c) {
			c = byWho[x][y + 1] % 100;
			byWho[x][y] = ((x) * 1000000) + ((y + 1) * 1000) + (c);
			cout << "Case 4 " << byWho[x][y] << endl;
		}
		else if (byWho[x + 1][y + 1] % 100 < c) {
			c = byWho[x + 1][y + 1] % 100;
			byWho[x][y] = ((x + 1) * 1000000) + ((y + 1) * 1000) + (c);
			cout << "Case 5 " << byWho[x][y] << endl;
		}
		else if (byWho[x + 1][y] % 100 < c) {
			c = byWho[x + 1][y] % 100;
			byWho[x][y] = ((x + 1) * 1000000) + ((y) * 1000) + (c);
			cout << "Case 6 " << byWho[x][y] << endl;
		}
		else if (byWho[x + 1][y - 1] % 100 < c) {
			c = byWho[x + 1][y - 1] % 100;
			byWho[x][y] = ((x + 1) * 1000000) + ((y - 1) * 1000) + (c);
			cout << "Case 7 " << byWho[x][y] << endl;
		}
		else if (byWho[x][y - 1] % 100 < c) {
			c = byWho[x][y - 1] % 100;
			byWho[x][y] = ((x) * 1000000) + ((y - 1) * 1000) + (c);
			cout << "Case 8 " << byWho[x][y] << endl;
		}




		odx = x;
		ody = y;
		quad[(x * widthm) + y][0].color = Color::Blue;
		quad[(x * widthm) + y][1].color = Color::Blue;
		quad[(x * widthm) + y][2].color = Color::Blue;
		quad[(x * widthm) + y][3].color = Color::Blue;
		window.clear();

		for (int i = 0; i < col * row; ++i) {
			window.draw(quad[i]);

		}
		window.display();
		std::cout << "(" << x << "," << y << ") " << "Not Visited " << std::endl;

		//return



		system("pause");




		pathfinding(x - 1, y);// |
		pathfinding(x + 1, y);// |
		pathfinding(x, y + 1);// |
		pathfinding(x, y - 1);// |
		pathfinding(x + 1, y + 1);// |
		pathfinding(x + 1, y - 1);// |
		pathfinding(x - 1, y - 1);// |
		pathfinding(x - 1, y + 1);

		quad[(x * widthm) + y][0].color = Color::Blue;
		quad[(x * widthm) + y][1].color = Color::Green;
		quad[(x * widthm) + y][2].color = Color::Blue;
		quad[(x * widthm) + y][3].color = Color::Green;
	}
	if (mapm[x][y] == 2) {
	std::cout << "(" << x << "," << y << ") " << "DANG IT" << std::endl;


	quad[(x * widthm) + y][0].color = Color::Blue;
	quad[(x * widthm) + y][1].color = Color::Yellow;
	quad[(x * widthm) + y][2].color = Color::Blue;
	quad[(x * widthm) + y][3].color = Color::Yellow;
	//find the target
	//how to print path?

	return true;
	}
	return false;
	
	}*/

