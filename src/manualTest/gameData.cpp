#include "gameData.hpp"
#include <iostream>
#include <fstream>

gameData::gameData() : height(0),width(0),
gain(0),time(0),winLen(0),player_start(0),lastPlay(-1),
myChar('A'), ennemiChar('B') {
	int i = 0;
	for (std::string line; std::getline(std::cin, line);) {
		if (i == 0)
			width = atoi(line.c_str());
		else if (i == 1)
			height = atoi(line.c_str());
		else if (i == 2)
			winLen = atoi(line.c_str());
		else if (i == 3)
			player_start = atoi(line.c_str());
		else if (i == 4)
			time = atoi(line.c_str());
		else if (i == 5){
			gain = atoi(line.c_str());
			break;
		}
		i++;
	}
	initGameTab();
}

gameData::~gameData() {}

void gameData::initGameTab() {
  gameTab.resize(height);
  for (int i = 0; i < height;i++)
  {
    gameTab[i].resize(width);
    for (int j = 0; j < width; j++)
      if (i != height -1)
        gameTab[i][j] = '0';
      else
        gameTab[i][j] = '1';
  }
}

void	gameData::dispGameTab() {
	std::ofstream outfile;
	outfile.open("tab.txt", std::ios_base::app);
	for (int i = 0; i < height;i++)
  {
    for (int j = 0; j < width; j++)
	 		std::cout << gameTab[i][j] << " ";
		std::cout << std::endl;
  }
	std::cout << std::endl;
}

void	gameData::updateField(int i, char whoPlay) {
	int pos = height - 1;
	if (i >= 0 && i < width)
		while (pos >= 0) {
			if (gameTab[pos][i] == '1') {
				gameTab[pos][i] = whoPlay;
				if (pos - 1 >= 0)
					gameTab[pos - 1][i] = '1';
				break;
			}
			pos--;
		}
	dispGameTab();
}

bool	gameData::checkWin(char verif, int posx, int posy) {
	//check horizontal only from x-winlen included to x+winlen
	int count = 0;
	int i = posy;
	for (int j = std::max(0, posx-winLen+1); j < std::min(width, posx+winLen); j++) {
		if (gameTab[i][j] == verif)
			count++;
		else
			count=0;
		if (count == winLen)
			return(true);
	}
	count=0;
	//check vertical from y-winlen included to y+winlen
	i = posx;
	for (int j = std::max(0, posy-winLen+1); j < std::min(height, posy+winLen); j++) {
		if (gameTab[j][i] == verif)
			count++;
		else
			count=0;
		if (count == winLen)
			return(true);
	}

	count=0;
	i = posx-winLen+1;
	// for (int i = posx-winLen+1; i < posx+winLen; i++) {
		for (int j = 0; j < winLen*2;j++) {
			if ((i+j >= 0) && (i+j<height) && (posy+j >=0) && (posy+j < width)
				&& gameTab[i+j][posy+j] == verif)
				count++;
			else
				count=0;
			if (count == winLen)
				return(true);
		}
		int z=0;
		for (int j = 0; j < winLen*2;j++) {
			if ((i-z >= 0) && (i-z<height) && (posy+winLen-z >=0) && (posy+winLen-z < width)
				&& gameTab[i-z][posy+winLen-z] == verif)
				count++;
			else
				count=0;
			if (count == winLen)
				return(true);
			z++;
		}
	return false;
}

int gameData::recursive_find(int x, int y,char teamletter,std::vector<std::vector<char> > Tmptab, int depth)
{
    int poids = 0;
    int tmppoids;
    int tmpy;
    while(x < height-1 && Tmptab[x][y] != '1')
      x++;
		if(checkWin(teamletter, x, y) || depth > 6)
		{
			if (checkWin(teamletter, x, y))
				std::cout << "HAS WON" << std::endl;
			return (poids + depth);
		}
    if (Tmptab[x][y] != '1')
		{
			return -1;
		}
		// std::cout << "check1" << std::endl;
    if (teamletter == 'A')
      {
					// std::cout << "check2" << std::endl;
          Tmptab[x][y] = 'A';
					// std::cout << "check3" << std::endl;
					poids = -2;
          tmpy = 0;
					// std::cout << "check4" << std::endl;
          while (tmpy < width) {
            tmppoids = recursive_find(0,tmpy,'B',Tmptab,depth+1);
						// std::cout << "poids1=" << tmppoids << std::endl;
            if (poids < tmppoids && tmppoids > 0)
              poids = tmppoids;
            tmpy++;
          }
					// std::cout << "check5" << std::endl;
      }
      else
      {
          Tmptab[x][y] = 'B';
          poids = 10000;
						// std::cout << "poids2=" << poids << std::endl;
          tmpy = 0;
          while (tmpy < width) {
          	tmppoids = recursive_find(0,tmpy,'A',Tmptab,depth+1);
						// std::cout << "poids3=" << tmppoids << std::endl;
            if (poids > tmppoids && tmppoids > 0)
              poids = tmppoids;
            tmpy++;
           }
      }
	return (poids + depth);
}
