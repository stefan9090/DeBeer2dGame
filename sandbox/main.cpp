//
// Created by stefan on 4/29/22.
//

#include <DeBeer2d.h>

class Game : public Beer::Application
{
private:
    std::string strTexturePath = "/home/stefan/Documents/code/DeBeer2dGame/resources/textures";
public:
    void init()
    {
        loadTexture(strTexturePath + "test.jpg");

        initTextures();
    }
};

int main()
{
    Game game;

    game.init();
    game.run();

    return 0;
}