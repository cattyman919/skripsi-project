#include "GLFW/glfw3.h"
#include "app_imgui/ImGuiUtils.h"
#include "app_imgui/login.h"
#include "app_imgui/stb_image.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

struct WindowData {
  bool ShowLoginWindow{true};
  bool ShowTodoWindow{false};
};

static void error_callback(int error, const char *description) {
  fprintf(stderr, "Error: %s\n", description);
}

int main() {
  struct WindowData window_data;
  std::string username{};
  std::string password{};

  glfwSetErrorCallback(error_callback);

  if (!glfwInit())
    exit(EXIT_FAILURE);

  // OpenGL3 config for GLFW
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // GLFW window config
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  ImGui::window = glfwCreateWindow(640, 640, "Todo Auth", NULL, NULL);

  if (!ImGui::window) {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(ImGui::window);
  glfwSwapInterval(1);

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls

  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(
      ImGui::window, true); // Second param install_callback=true will install
                            // GLFW callbacks and chain to existing ones.
  ImGui_ImplOpenGL3_Init();

  // Default ImGui Style & Fonts
  ImGui::SetupImGuiStyle(io, true, 1);

  while (!glfwWindowShouldClose(ImGui::window)) {
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (window_data.ShowLoginWindow)
      Login::LoginWindow(&window_data.ShowLoginWindow, username, password);

    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(ImGui::window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w,
                 clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(ImGui::window);
  }

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(ImGui::window);
  glfwTerminate();
  return 0;
}
