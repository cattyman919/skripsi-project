#include "login.h"

void Login::LoginDialog(Authentication_Status status, bool *p_open = NULL) {
  LPCWSTR name;
  UINT flags;

  switch (status) {
  case AUTH_SUCCESS:
    name = L"Authentication Success";
    flags = MB_ICONASTERISK;
    break;
  case AUTH_FAILED:
    name = L"Authentication Failed";
    flags = MB_ICONSTOP;
    break;
  }

  MessageBoxW(NULL, name, (LPCWSTR)L"Login", flags);

  if (p_open)
    *p_open = false;
}

void Login::LoginWindow(bool *p_open, std::string &username,
                        std::string &password) {
  static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration |
                                  ImGuiWindowFlags_NoMove |
                                  ImGuiWindowFlags_NoSavedSettings;

  const ImGuiViewport *viewport{ImGui::GetMainViewport()};
  ImGui::SetNextWindowPos(viewport->WorkPos);
  ImGui::SetNextWindowSize(viewport->WorkSize);

  if (ImGui::Begin("Login", p_open, flags)) {
    ImGui::PushFont(ImGui::fonts[SIZE_64]);
    ImGui::CENTERED_CONTROL(ImGui::Text("To-do Application"));
    ImGui::PopFont();
    ImGui::Text("Username");
    ImGui::SameLine();
    ImGui::InputText("##input_username", &username);
    ImGui::Text("Password");
    ImGui::SameLine();
    ImGui::InputText("##input_password", &password,
                     ImGuiInputTextFlags_Password);

    if (*p_open &&
        ImGui::CENTERED_CONTROL(ImGui::Button("Login", ImVec2(250, NULL)))) {
      if (username.compare("seno") == 0 && password.compare("rahman") == 0) {
        Login::LoginDialog(AUTH_SUCCESS, p_open);
      } else {
        Login::LoginDialog(AUTH_FAILED);
      }
    }
  }

  ImGui::End();
}
