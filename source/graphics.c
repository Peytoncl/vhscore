#include "../headers/graphics.h"
#include "../headers/game.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../headers/stb_image.h"

GLuint spritesheet;

void LoadSpritesheet() // loads texture at index, can not be over MAX_TEXTURES
{
    int width, height, channels;

    char texturePath[2048];

    sprintf(texturePath, "%s%s", cwd, "/");
    sprintf(texturePath, "%s%s", texturePath, "spritesheet.png");

    unsigned char* data = stbi_load(texturePath, &width, &height, &channels, 3);

    if (!data) 
    {
        printf("Failed to load spritesheet.\n");

        exit(1);
    }

    glGenTextures(1, &spritesheet);
    glBindTexture(GL_TEXTURE_2D, spritesheet);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, spritesheet);

    stbi_image_free(data);
}