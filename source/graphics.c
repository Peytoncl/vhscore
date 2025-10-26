#include "../headers/graphics.h"
#include "../headers/game.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../headers/stb_image.h"

GLuint textures[MAX_TEXTURES]; // array of textures ranging from 0 - MAX_TEXTURES
int amountOfTextures = 0; // current amount of textures loaded

void LoadTexture(char* textureName, int index) // loads texture at index, can not be over MAX_TEXTURES
{
    int width, height, channels;

    char texturePath[2048];

    sprintf(texturePath, "%s%s", cwd, "/");
    sprintf(texturePath, "%s%s", texturePath, textureName);

    unsigned char* data = stbi_load(texturePath, &width, &height, &channels, 0);

    if (!data) 
    {
        printf("Failed to load texture\n");

        exit(1);
    }

    //printf("%s loaded at index %d\n", textureName, index);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_image_free(data);

    textures[index] = texture;
    amountOfTextures++;
}

void UnloadTexture(int index) // unloads texture at index
{
    glDeleteTextures(1, &textures[index]);

    textures[index] = 0;

    //printf("texture at index %d unloaded\n", index);

    amountOfTextures--;
}