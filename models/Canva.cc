#include <fstream>
#include <iostream>
#include <string>

#pragma pack(push, 1)
struct BMPHeader {
    unsigned short type = 0x4D42; // "BM"
    unsigned int size;
    unsigned short reserved1 = 0;
    unsigned short reserved2 = 0;
    unsigned int offset = 54;
};

struct BMPInfoHeader {
    unsigned int size = 40;
    int width;
    int height;
    unsigned short planes = 1;
    unsigned short bitsPerPixel = 24;
    unsigned int compression = 0;
    unsigned int imageSize;
    int xPixelsPerMeter = 0;
    int yPixelsPerMeter = 0;
    unsigned int colorsUsed = 0;
    unsigned int importantColors = 0;
};
#pragma pack(pop)

struct Color
{
    unsigned char b, g, r;
};

class Canva 
{
private: 
    int width;
    int height;
    std::ofstream& file;
public:
    Canva(std::string filename, int width, int height) : width(width), height(height), file(*(new std::ofstream())) {
        // Calcula o padding necessário para que cada linha seja múltiplo de 4 bytes
        int padding = (4 - (width * 3) % 4) % 4;
        int rowSize = width * 3 + padding;
        int imageSize = rowSize * height;

        BMPHeader header;
        header.size = sizeof(BMPHeader) + sizeof(BMPInfoHeader) + imageSize;

        BMPInfoHeader infoHeader;
        infoHeader.width = width;
        infoHeader.height = height;
        infoHeader.imageSize = imageSize;

        this->file.open(filename, std::ios::binary | std::ios::trunc);
        this->file.write(reinterpret_cast<char*>(&header), sizeof(header));
        this->file.write(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                Color pixel{255, 255, 255};
                this->file.write(reinterpret_cast<char*>(&pixel), sizeof(Color));
            }
            // Write padding bytes for each row
            int padding = (4 - (width * 3) % 4) % 4;
            for (int k = 0; k < padding; ++k) {
                this->file.put(0);
            }
        }
    }

    void setPixel(int x, int y, Color color) {
        // Ensure pixel coordinates are within bounds
        if (x < 0 || x >= width || y < 0 || y >= height) {
            return;
        }

        // Calculate the position in the file (row-major order)
        int padding = (4 - (width * 3) % 4) % 4;
        int rowSize = width * 3 + padding;
        int pixelOffset = sizeof(BMPHeader) + sizeof(BMPInfoHeader) + (height - 1 - y) * rowSize + x * 3;

        // Move file pointer to the pixel position and write color values
        file.seekp(pixelOffset);
        file.write(reinterpret_cast<char*>(&color.b), 1);
        file.write(reinterpret_cast<char*>(&color.g), 1);
        file.write(reinterpret_cast<char*>(&color.r), 1);
    }

    std::ofstream& getFile() const {
        return file;
    }
    int getWidth() const {
        return width;
    }
    int getHeight() const {
        return height;
    }

};