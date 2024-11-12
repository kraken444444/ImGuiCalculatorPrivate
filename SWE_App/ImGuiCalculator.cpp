#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include <stdio.h>
#include <SDL.h>
#include <string>
#include <windows.h>
#include <SDL_config_windows.h>
#include <SDL_syswm.h>
#include <unordered_map>
#include "CalculatorHelper.h"


int main(int, char**)
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER);


    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);

    int screenWidth = displayMode.w;
    int screenHeight = displayMode.h;

    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Window* window = SDL_CreateWindow("ImGuiCalculator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_BORDERLESS | SDL_WINDOW_POPUP_MENU); // |SDL_ALWAYSONTOP

    SDL_SysWMinfo wmInfo; //variable that stores window manager information
    SDL_VERSION(&wmInfo.version); //initializes current version of info so we can pass it to getwindowinfo
    SDL_GetWindowWMInfo(window, &wmInfo);//getter for window info and stores it inside wmInfo
    HWND hwnd = wmInfo.info.win.window; // extracts info from wmInfo and stores it inside HWND
    SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED); //Sets window style, allowing it to be transparent
    SetLayeredWindowAttributes(hwnd, 0, 0, LWA_COLORKEY); // sets the window info of hwnd, LWA_COLORKEY sets it to transparent 0, 0, 0 color key is black, so any pixels matching will be transparent



    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsClassic();

    

    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);


    bool show_demo_window = false;
    bool show_another_window = false;

    bool done = false;


////////////////////////////////////////////////////////////////////////////////////////////DECLARATIONS

    static char inputBuffer[512] = "";
    ImVec2 basicButton(100, 50);
     ImVec4 window_color = ImVec4(0.264f, 0.247f, 0.311f, 1.0f);
     bool startingWindow = true;
     CalculatorHelper calculateHelper;

     






    while (!done)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                done = true;
        }
        if (SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED)
        {
            SDL_Delay(10);
            continue;
        }

    
        
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        ImVec2 basicButton(75, 60);

        static ImVec4 window_color = ImVec4(0.264f, 0.247f, 0.311f, 1.0f);

        ImGui::GetStyle().AntiAliasedFill = false;
        ImGui::GetStyle().AntiAliasedLines = false;

        

        {

            ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = window_color;
            if (startingWindow) {
                ImGui::SetNextWindowSize(ImVec2(350, 427));
                ImGui::Begin("Calculator", &startingWindow, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar);
                ImGui::SetWindowFontScale(4.0f);
                ImGui::InputTextMultiline("##Display", inputBuffer, IM_ARRAYSIZE(inputBuffer), ImVec2(330, 75), ImGuiInputTextFlags_ReadOnly);
                ImGui::SetWindowFontScale(1.0f);
                for (int i = 0; i < 3; i++) {

                    ImGui::Dummy(basicButton); ImGui::SameLine(); // adds spacing for the clear button
                }
                if (ImGui::Button("C", basicButton)) {

                    calculateHelper.Clear(inputBuffer); 

                }

                if (ImGui::Button("<-", basicButton)) { calculateHelper.Backspace(inputBuffer); }
                ImGui::SameLine();
                if (ImGui::Button("sin", basicButton)) { strcat_s(inputBuffer, IM_ARRAYSIZE(inputBuffer), "sin "); }
                ImGui::SameLine();
                if (ImGui::Button("cos", basicButton)) { strcat_s(inputBuffer, IM_ARRAYSIZE(inputBuffer), "cos "); }
                ImGui::SameLine();
                if (ImGui::Button("tan", basicButton)) { strcat_s(inputBuffer, IM_ARRAYSIZE(inputBuffer), "tan "); }



                if (ImGui::Button("7", basicButton)) { strcat_s(inputBuffer, IM_ARRAYSIZE(inputBuffer), "7"); }
                ImGui::SameLine();
                if (ImGui::Button("8", basicButton)) { strcat_s(inputBuffer, IM_ARRAYSIZE(inputBuffer), "8"); }
                ImGui::SameLine();
                if (ImGui::Button("9", basicButton)) { strcat_s(inputBuffer, IM_ARRAYSIZE(inputBuffer), "9"); }
                ImGui::SameLine();
                if (ImGui::Button("/", basicButton)) { strcat_s(inputBuffer, IM_ARRAYSIZE(inputBuffer), "/"); }



                if (ImGui::Button("4", basicButton)) { strcat_s(inputBuffer, IM_ARRAYSIZE(inputBuffer), "4"); }
                ImGui::SameLine();
                if (ImGui::Button("5", basicButton)) { strcat_s(inputBuffer, IM_ARRAYSIZE(inputBuffer), "5"); }
                ImGui::SameLine();
                if (ImGui::Button("6", basicButton)) { strcat_s(inputBuffer, IM_ARRAYSIZE(inputBuffer), "6"); }
                ImGui::SameLine();
                if (ImGui::Button("*", basicButton)) { strcat_s(inputBuffer, IM_ARRAYSIZE(inputBuffer), "*"); }



                if (ImGui::Button("1", basicButton)) { strcat_s(inputBuffer, IM_ARRAYSIZE(inputBuffer), "1"); }
                ImGui::SameLine();
                if (ImGui::Button("2", basicButton)) { strcat_s(inputBuffer, IM_ARRAYSIZE(inputBuffer), "2"); }
                ImGui::SameLine();
                if (ImGui::Button("3", basicButton)) { strcat_s(inputBuffer, IM_ARRAYSIZE(inputBuffer), "3"); } 
                ImGui::SameLine();
                if (ImGui::Button("-", basicButton)) { strcat_s(inputBuffer, IM_ARRAYSIZE(inputBuffer), "-"); }


                if (ImGui::Button("0", basicButton)) { strcat_s(inputBuffer, IM_ARRAYSIZE(inputBuffer), "0"); }
                ImGui::SameLine();
                if (ImGui::Button(".", basicButton)) { strcat_s(inputBuffer, IM_ARRAYSIZE(inputBuffer), "."); }
                ImGui::SameLine();
                if (ImGui::Button("=", basicButton)) { 

                    calculateHelper.EvaluateExpression(inputBuffer, IM_ARRAYSIZE(inputBuffer));

                } ImGui::SameLine();
                if (ImGui::Button("+", basicButton)) { strcat_s(inputBuffer, IM_ARRAYSIZE(inputBuffer), "+"); }


                    ImGui::End();
            }
        }
    
       
        



        ImGui::Render();
        SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // does some stuff to make window transparent
        SDL_RenderClear(renderer);
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
        SDL_RenderPresent(renderer); 



    }


    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

