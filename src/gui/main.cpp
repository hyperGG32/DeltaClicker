#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

#include <chrono>
#include <filesystem>
#include <thread>

#include <DeltaClickerCore.hpp>

static void load_font() {
    ImGuiIO& io = ImGui::GetIO();
    const char* p = "C:/Windows/Fonts/segoeui.ttf";
    if (std::filesystem::exists(p))
        io.Fonts->AddFontFromFileTTF(p, 18.0f, nullptr, io.Fonts->GetGlyphRangesCyrillic());
}

int main() {
    if (!glfwInit()) return 1;
    GLFWwindow* win = glfwCreateWindow(380, 330, "DeltaClicker", nullptr, nullptr);
    if (!win) { glfwTerminate(); return 1; }
    glfwMakeContextCurrent(win);
    glfwSwapInterval(1);

    ImGui::CreateContext();
    ImGui::GetIO().IniFilename = nullptr;
    ImGui::StyleColorsDark();
    ImGuiStyle& s = ImGui::GetStyle();
    s.FrameRounding = 6.f;
    s.GrabRounding = 6.f;
    s.FramePadding = {10, 6};
    s.ItemSpacing = {10, 12};
    s.WindowPadding = {16, 16};
    load_font();

    ImGui_ImplGlfw_InitForOpenGL(win, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    Clicker clicker;
    bool running = false;

    int  delay      = clicker.getDelay();
    bool randomMode = clicker.getRandomMode();
    int  offset     = clicker.getRandomOffset();
    int  type       = clicker.getType();   // 1 або 2

    while (!glfwWindowShouldClose(win)) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowPos({0, 0});
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
        ImGui::Begin("##main", nullptr,
                     ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove |
                     ImGuiWindowFlags_NoSavedSettings);

        ImGui::Text("DeltaClicker");
        ImGui::Separator();

        ImGui::SetNextItemWidth(-1);
        if (ImGui::SliderInt("##delay", &delay, 1, 1000, "Delay: %d мс"))
            clicker.setDelay(delay);

        if (ImGui::Checkbox("Random mode", &randomMode))
            clicker.setRandomMode(randomMode);

        ImGui::BeginDisabled(!randomMode);
        ImGui::SetNextItemWidth(-1);
        if (ImGui::SliderInt("##offset", &offset, 0, 500, "Offset: %d мс"))
            clicker.setRandomOffset(offset);
        ImGui::EndDisabled();

        ImGui::TextDisabled("Button layout");
        bool t_changed = false;
        t_changed |= ImGui::RadioButton("Type 1", &type, 1); ImGui::SameLine();
        t_changed |= ImGui::RadioButton("Type 2", &type, 2);
        if (t_changed) {
            clicker.setType(type);


        }

        ImGui::PushStyleColor(ImGuiCol_Button,
            running ? ImVec4(0.75f, 0.22f, 0.22f, 1.f) : ImVec4(0.20f, 0.55f, 0.30f, 1.f));
        if (ImGui::Button(running ? "Stop" : "Start", {-1, 44})) {
            running = !running;
            if (running) clicker.start(); else clicker.stop();
        }
        ImGui::PopStyleColor();

        if (ImGui::Button("Save options", {-1, 0}))
            clicker.saveData();

        ImGui::End();
        ImGui::Render();

        int w, h;
        glfwGetFramebufferSize(win, &w, &h);
        glViewport(0, 0, w, h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(win);
    }

    clicker.stop();
    std::this_thread::sleep_for(std::chrono::milliseconds(300)); // даємо detached-потоку вийти

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(win);
    glfwTerminate();
}