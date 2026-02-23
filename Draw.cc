#include <fstream>
#include "models/Canva.cc"



class IDraw
{
    public:
        virtual void draw(Canva& canva, int x, int y, int size, Color color /*int width = -1, int height = -1*/) = 0;
        virtual ~IDraw() = default;
};

class DrawCircle : public IDraw
{
    
public:
    void draw(Canva& canva, int x, int y, int size, Color color) override
    {
        for (int i = 0; i < canva.getHeight(); i++)
        {
            for (int j = 0; j < canva.getWidth(); ++j) {
                if(((j - x) * (j - x)) + ((i - y) * (i - y)) < size*size){
                    canva.setPixel(j, i, color);
                } 
            }
        }
    }
};

class DrawSquare : public IDraw
{
public:
    void draw(Canva& canva, int x, int y, int size, Color color) override
    {
        int maxW = x+size;
        int minW = x-size;

        int maxH = y+size;
        int minH = y-size;

        for (int i = 0; i < canva.getHeight(); i++)
        {
            for (int j = 0; j < canva.getWidth(); ++j) {
                if((i >= minH && i <= maxH) && (j >= minW && j <= maxW)){
                    canva.setPixel(j, i, color);
                } 
            }
        }
    }
};