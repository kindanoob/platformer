#ifndef MAP_H_
#define MAP_H_

#include <vector>
#include <string>

//B - brick, 0 - bonus, P - pistol, D - fire
const int TILE_SIDE_LENGTH = 32;

const std::vector<std::vector<std::string> > MAPS_VECTOR = {
{
    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
    "B                                                                              B",
    "B                                                                              B",
    "B                                                                              B",
    "B                                                                              B",
    "B         D00D                                                                 B",
    "B                                           B                 BB               B",
    "BBB                                        B                                   B",
    "B              BB                         B           B B             B        B",
    "B              BB          D             B            B B             B  BB    B",
    "B    B         BB         BB             B            B B           BBB        B",
    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",

},
{

    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
    "B                                                                              BB        DDD                                                                   B",
    "B                                                                                                                DB                         B            P     B",
    "B       0  D  0                                                                 B                                0 B                    BB  B                  B",
    "B                                                                              BB                                 B B                   B           B          B",
    "B         0000                                                               BBBB                                    B                   B          B          B",
    "B                                           B                 BBD              BBBBB          B                       BBBB                         B           B",
    "BBBD                                       BP                                  BB   B         B                B        B                         B            B",
    "B              BB                         B           B B             B        BB   0B        B          0             B                       BBB             B",
    "B              BB          D             B            B B             B  BB   PBB  BB B      BBB         D          BBB                      BB                B",
    "BP   B         BB         BB             B            B B           BBB        BB                        D                                                     B",
    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",

},
{

    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
    "B                                                                              BB                                 0                                            BB                                                                              BB                                                                              B",
    "B                                                                                                                 B                         B               B  BB                                                                              BB                                                                              B",
    "B                                                                               B                              0   B                    BB  B               B  BB                                                                              BB                                                                              B",
    "B  0      D  0                                                                 BB                              B  B B                   B                   B  BB                                                                              BB                                                                              B",
    "B                                                                            BBBB                         B          B                   B                  B  BB                                                                              BB                                                                              B",
    "B        0000                               B                 BBD              BBBBB          B                       BBBB                                 B   BB                                                                               B                                                                              B",
    "BBBD                                       B                                   BB   B         B                B        B         B                       B    BB          BBB                     BBBB                                                                                                                        B",
    "B              BB                         B0          B B             B        BB   0B        B                        B                       BBBBBBBBBBB     BB        BB                                                                     BBBB                                                                           B",
    "B              BB          D             B            B B             B  BB    BB  BB B      BBB                    BBB                      BB                BB      BB                                                                      BB                                                                              B",
    "BP   B         BB         BB             B0           B B           BBB        BB                                                                              00    BB                                                                        BB                                                                              B",
    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB         BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB   BBB   BBB   BBBBBBBBBBBB    BBBB    BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB                                BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB      BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",

}

};


class GameMap {
public:
    std::vector<std::string> char_map;
    int width;
    int height;
    int tile_side_length;
    GameMap(int ind);
    int ground_level;
};

GameMap::GameMap(int ind) {
    char_map = MAPS_VECTOR[ind];
    width = char_map[0].length();
    height = char_map.size();
    tile_side_length = TILE_SIDE_LENGTH;
    ground_level = height * TILE_SIDE_LENGTH;
}

#endif // MAP_H_
