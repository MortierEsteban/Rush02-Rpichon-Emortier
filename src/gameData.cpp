#include "gameData.hpp"
#include <iostream>
#include <fstream>

gameData::gameData() : height(0),width(0),
gain(0),time(0),winLen(0),player_start(0),lastPlay(-1) {
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
	if (player_start == 1)
	{ myChar = 'A'; ennemiChar = 'B' }
	else
	{ myChar = 'B'; ennemiChar = 'A' }
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
	 		outfile << gameTab[i][j] << " ";
		outfile << std::endl;
  }
	outfile << std::endl;
}

void	gameData::updateField(int i, char whoPlay) {
	int pos = height - 1;
	if (i >= 0 && i < width -1)
		while (pos >= 0) {
			if (gameTab[pos][i] == '1') {
				gameTab[pos][i] = whoPlay;
				if (pos - 1 >= 0)
					gameTab[pos - 1][i] = '1';
				pos = -1;
			}
			pos--;
		}
	dispGameTab();
}
