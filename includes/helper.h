#include "GLFW/glfw3.h"
#include "imgui.h"

#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Image {
bool LoadTextureFromMemory(const void *data, size_t data_size,
                           GLuint *out_texture, int *out_width,
                           int *out_height);
bool LoadTextureFromFile(const char *file_name, GLuint *out_texture,
                         int *out_width, int *out_height);
} // namespace Image
