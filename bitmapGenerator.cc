#include <iostream>
#include <fstream>

using namespace std;

// Estruturas do Windows BMP (necessárias para o formato)
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

struct Pixel {
    unsigned char b;
    unsigned char g;
    unsigned char r;
};

void criarBitmapColorido_bit_bit(const char* filename, int width, int height, Pixel color){

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

    std::ofstream image_file(filename, std::ios::binary);
    image_file.write(reinterpret_cast<char*>(&header), sizeof(header));
    image_file.write(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    Pixel px = color;
    Pixel reverse_px = {color.r, color.g, color.b}; 
    Pixel* col = new Pixel[width+padding];
    int a = width / 2;
    int b = height / 2;
    int r = 200;
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; ++j) {
            if(((j - a) * (j - a)) + ((i - b) * (i - b)) < r*r){
                col[j] = px;
            } else{
                col[j] = reverse_px;
            }
        }
        image_file.write(reinterpret_cast<char*>(col), rowSize);
    }
    image_file.close();
    std::cout << "Bitmap colorido gerado: " << filename << std::endl;

}

void criarBitmapColorido(const char* filename, int width, int height, Pixel color) {

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

    std::ofstream image_file(filename, std::ios::binary);
    image_file.write(reinterpret_cast<char*>(&header), sizeof(header));
    image_file.write(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    Pixel px = color;
    Pixel *row = new Pixel[width];

    for (int i = 0; i < width; i++)
    {
        row[i] = px;
    }
    
    
    // Escreve as linhas
    for (int i = 0; i < height; ++i) {
        image_file.write(reinterpret_cast<char*>(row), rowSize);
    }

    image_file.close();
    std::cout << "Bitmap colorido gerado: " << filename << std::endl;
}

int main() {
    while (1)
    {
        cout << "Escolha a cor do bitmap (0 - Branco, 1 - Azul, 2 - Verde, 3 - Vermelho): ";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 0:
            criarBitmapColorido_bit_bit("../branco.bmp", 800, 800, {255, 255, 255});
            break;
        case 1:
            criarBitmapColorido_bit_bit("../azul.bmp", 800, 800, {255, 0, 0});
            break;
        case 2:
            criarBitmapColorido_bit_bit("../verde.bmp", 800, 800, {0, 255, 0});
            break;
        case 3:
            criarBitmapColorido_bit_bit("../vermelho.bmp", 800, 800, {0, 0, 255});
            break;
        default:
            break;
        }
        break;
    }
    
    cout << sizeof(Pixel) << endl; // Verifica o tamanho da estrutura Pixel
    return 0;
}