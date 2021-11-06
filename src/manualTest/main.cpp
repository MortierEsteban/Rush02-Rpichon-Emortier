#include <unistd.h>
#include <fstream>
#include <sys/types.h>
#include <string>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;
#include "gameData.hpp"
int main()
{
    int i = 0;
    gameData data;

    std::ofstream outfile ("rep.txt");
    std::string line;
    int whereToPlay;
    outfile << data.width << " " << data.height << " " << data.winLen << " " << data.player_start << " " << data.time << " " << data.gain << " " << data.lastPlay << " " << std::endl;
    while (1){
        if (data.player_start == 1) {
            std::vector<int> my_ints;
            if (i++ != 0)
            {
                for (int column = 0; column < data.width; column++)
                    my_ints.push_back(data.recursive_find(0,column,'A',data.getGameTab(), 1));
                for (int t: my_ints)
                     std::cout << t << '|';
                whereToPlay = std::min_element(my_ints.begin(),my_ints.end()) - my_ints.begin();
            }
            else
              whereToPlay = data.width/2;
            outfile << data.myChar << ": " << whereToPlay << std::endl;
            std::cout << "letsplay in: "<< whereToPlay << std::endl;
            data.updateField(whereToPlay, data.myChar);
        }
        std::cout << "Where do you want to play";
        std::getline (std::cin,line);
        i++;
        outfile << data.ennemiChar << ": " << line << std::endl;
        data.updateField(atoi(line.c_str()),data.ennemiChar);
        data.player_start = 1;
    }
}

