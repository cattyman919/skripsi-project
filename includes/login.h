#pragma once
#define GLFW_EXPOSE_NATIVE_WIN32
#include "ImGuiUtils.h"
#include "imgui.h"
#include "imgui_stdlib.h"
#include <GLFW/glfw3native.h>
#include <windows.h>
namespace Login {

enum Authentication_Status { AUTH_SUCCESS, AUTH_FAILED };

void LoginDialog(Authentication_Status status, bool *p_open);
void LoginWindow(bool *p_open, std::string &username, std::string &password);
} // namespace Login
