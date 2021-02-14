#include <SFML/Graphics.hpp>
#include<iostream>
#include<vector>

const int SCREEN_SIZE = 200;
sf::RenderWindow window(sf::VideoMode(SCREEN_SIZE, SCREEN_SIZE), "SNOWFLAKE");

struct Position{
    float x;
    float y;
};

class Flake{
    private:
        Position pos;
        sf::Sprite flake;
        sf::Texture texture;

    public:
        Flake(sf::Texture snow, Position pos){
            this->pos.x = pos.x;
            this->pos.y = pos.y;
            this->texture = snow;
            flake.setTexture(snow);
            //flake.setScale(0.025, 0.05);
            flake.setScale(0.0025, 0.005);
            flake.setPosition(pos.x, pos.y);
        };

    void move(Position pos){
        this->pos.x = pos.x;
        this->pos.y = pos.y;

        flake.setTexture(this->texture);
        flake.move(0, pos.y - flake.getPosition().y);

    };

    void draw(){
        window.draw(flake);
    }

    void moveY(float y){
        Position pos;
        pos.x  = this->pos.x;
        pos.y = y;
        this->move(pos);
    };

    void reset(Position pos){
        flake.setTexture(texture);
        flake.setPosition(pos.x,pos.y);
    }
};

class Scene{

    private:
        std::vector<Flake*>flakes;
        Position pos = getRandomPos();
        Position getRandomPos(){
            Position pos;
            pos.x = rand() % 200;
            pos.y = 0;
            return pos;
        };
        float currentY = 0;
    public:
        Scene(int numFlakes){
            sf::Texture snow;
            snow.loadFromFile("unnamed.png");
            for(int i = 0; i < numFlakes; i++){
                Position pos = this->getRandomPos();
                flakes.push_back(new Flake(snow,pos));

            };
        };

    public:
        void animate(){

            window.clear();

            if( currentY >= SCREEN_SIZE) {
                currentY = 0;
                for(std::vector<Flake*>::iterator it = flakes.begin(); it != flakes.end(); it++){
                    Flake* flake = *it;
                    flake->reset(this->getRandomPos());
                };
            }
            else
                currentY += 0.05;

            for(std::vector<Flake*>::iterator it = flakes.begin(); it != flakes.end(); it++){
                Flake* flake = *it;
                flake->moveY(currentY);
            };

            for(std::vector<Flake*>::iterator it = flakes.begin(); it != flakes.end(); it++){
                Flake* flake = *it;
                flake->draw();
            };

            window.display();

    }; //animate


}; //class Scene


int main(){
    //render window (do not modify)

    Scene* scene = new Scene(100);

    //event listener loop(do not modify outer)
     while (window.isOpen()){
            sf::Event event;
            //specific window event listeners (keys and stuff)
            while (window.pollEvent(event)){
                if (event.type == sf::Event::Closed){
                    window.close();
                }
            }

            scene->animate();
     }


     return 0;
}


int mainOld(){
 int dimension = 200;
 float y = 0.1;

 //render window (do not modify)
 //sf::RenderWindow window(sf::VideoMode(dimension, dimension), "SNOWFLAKE");

    //event listener loop(do not modify outer)
 while (window.isOpen()){
        sf::Event event;
        //specific window event listeners (keys and stuff)
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }

        }

        //snowflake setup (do not modify):
        sf::Texture snow;
        snow.loadFromFile("unnamed.png");
        sf::Sprite flake[100];
        for(int i = 0; i  < 100; i++){
            flake[i].setTexture(snow);
            flake[i].setScale(0.025, 0.05);
        }

        //movement(modify):

        for(int i = 0; i < 100; i++){
            flake[i].move(0.5,y);
            flake[i].rotate(0.5);
            y += 0.0025;
            //if(flake[i].getPosition().y > 200){
             //flake[i].move(rand() % 200, 0.1);
          //}

        }

        //display (do not modify)
        window.clear();
        for(int i = 0; i < 100; i++){
            window.draw(flake[i]);
        }

        window.display();
    }

    return 0;

}
