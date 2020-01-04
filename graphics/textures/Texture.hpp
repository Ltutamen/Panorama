//
// Created by axiom on 6/23/19.
//

#ifndef PANORAMA_TEXTURE_HPP
#define PANORAMA_TEXTURE_HPP

#include <GL/glew.h>
/*
typedef struct{
    const char* filepath;
    unsigned char header[54];
    unsigned int dataPos;
    unsigned int width, height;
    unsigned int imageSize;

    unsigned char * data;

}BMPFile;


typedef struct {
    unsigned int width, height;
    unsigned int imageSize;
}shortBMP;


BMPFile* newBMPFILE(const char* filrpath);

typedef struct{
    BMPFile* file;
    GLuint textureID;
    shortBMP info;

}Textura;

Textura* newTexturaFP(const char* filepath);
Textura* newTexturaBM(BMPFile* bmpFile);

*/

GLuint loadBMP(const char * filepath);

#endif //PANORAMA_TEXTURE_HPP
