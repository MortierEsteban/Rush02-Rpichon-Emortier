
#define INT_MAX = 21474836487
#define INT_MIN = -2147483648
#include "gameData.hpp"
int	Att_def_definer(int myteam_aligned, int ennemy_aligned, int potplacement);
 int* gameData::recursive_find(int depth,std::vector<std::vector<char > > Tab,char PLAYER)
{
	int result[2];
	int score = 0;
	std::vector<std::vector<char > > TmpTab = data.get_gametab();
	if (depth == 0 || depth == (((data.width * data.height)/2) +1))
	{
		result[0] = Game_analysis(0,0,TmpTab,'A');
		result[1] = -1;
		return (result);
	if (PLAYER == data.myChar)
	{
		result[0] = -2147483648;
		result[1] = -1;
		int x = 0;
		int y = 0;
		while (y < width -1)
		{
			while (TmpTab[x++][y] != 1 && x < data.height -1){}
			if (x == data.height - 1)
				return (result);
			TmpTab[x][y] = data.myChar;
			score = recursive_find(depth - 1, TmpTab, PLAYER);
			if (score > result[0])
			{
				result[0] = score;
				result[1] = y;
			}
			y++;
		}
		return (result);
	if (PLAYER != data.myChar)
	{
		result [0] = 2147483647;
		result[1] = -1;
		int x = 0;
		int y = 0;
		while (y < width -1)
		{
			while (TmpTab[x++][y] != 1 && x < data.height -1){}
			if (x == data.height - 1)
				return (result);
			TmpTab[x][y] = data.ennemiChar;
			score = recursive_find(depth - 1, TmpTab, PLAYER);
			if (score < result[0])
			{
				result[0] = score;
				result[1] = y;
			}
			y++;
		}
		return (result);

	}
}
//puts directions into a line + sends final score
int gameData::Game_analysis(int posx,int posy,std::vector<std::vector<char > > tab,char PLAYER)
{
	int i = 0;
	int score = 0;
	int tmpx = posx;
	int tmpy = posy;

	std::string Lineup;
	//check horizontal
	while (Tmptab[posx][i] == '0')
		i++;
	while (i < data.width -1)
	{
		string.append (Lineup, Tmptab[posx][i]);
		i++;
	}
	score += Line_scanner(Lineup,PLAYER);
	std::cout << "score(H) = " << score << std::endl; 
	//check vertical
	string.erase(Lineup);
	i = 0;
	while (Tmptab[i][posy] == '0')
		i++;
	while (i < data.height -1)
	{
		string.append (Lineup, Tmptab[i][posy]);
		i++;
	}
	score += Line_scanner(Lineup,PLAYER);
	std::cout << "score(H+V) = " << score << std::endl; 
	//here score = horizontal+ vertical score+RL
	string.clear(Lineup);
	i = 0;
	//anti-segfault
	if (y - tmpx < 0)
		y = 0;
	else 
		y = y - tmpx;
	if (x - tmpy < 0)
		x = 0;
	else
		x = x - tmpy;
	//done
	while (Tmptab[x + i][y + i] == '0')
		i++;
	while (x + i < data.Height - 1 && y + i < width - 1)
	{
		string.append (Lineup, Tmptab[x + i][y + i]);
		i++;
	}
	score += Line_scanner(Lineup,PLAYER);
	std::cout << "score(H+V+RL) = " << score << std::endl; 
	//here score = horizontal+ vertical score + RL + LR
	string.clear(Lineup);
	i = 0;
	//anti-segfault
	if (y + tmpx < 0)
		y = 0;
	else 
		y = y + tmpx;
	if (x - tmpy < 0)
		x = 0;
	else
		x = x - tmpy;
	//done
	while (Tmptab[x - i][y + i] == '0' && x - i < data.Height - 1 && y + i > 0 )
		i--;
	while (x - i < data.Height - 1 && y + i > 0)
	{
		string.append (Lineup, Tmptab[x - i][y + i]);
		i--;
	}
	score += Line_scanner(Lineup,PLAYER);
	std::cout << "score(H+V+RL) = " << score << std::endl; 
	return (score); 
}

//check who wins on alignement
int Line_scanner(char *aligned, char PLAYER)
{
	int i = 0;
	int myteam = 0;
	int ennemy = 0;
	int potplacement = 0;
	while (i < strlen(aligned) - 1)
	{
		 if	(aligned [i] == '1')
			potplacement ++;
		if (aligned [i] == 'PLAYER')
			myteam++;
		if (aligned [i] == '0'){}
		else 
			ennemy++;
		i++;
	}
	return(att_def_definer(myteam, ennemy, potplacement));
}
int	gamedata::Att_def_definer(int myteam_aligned, int ennemy_aligned, int potplacement)
{
	// On privilegie les gros scores defensifs
	//permet egaleemtn de choisir si une attaque sur deux front vaux mieux que def (balance scores 2dothat)
	int score;
	if (myteam_aligned == data.winlen)
	{
		score = 70000;
		return (score);
	}
	else if  (myteam_aligned == data.winlen -2 && potplacement >= 2);
		score = 100;
	else if (myteam_aligned == data.winlen -1 && potplacement >= 1);
		score = 500;
	else if  (ennemy_aligned == data.winlen -2 && potplacement >= 2);
		score = -100;
	else if  (ennemy_aligned == data.winlen -1 && potplacement >= 1);
		score = -500;
	else if (ennemy_aligned == data.winlen)
		score = -70000;
	return (score);
}
