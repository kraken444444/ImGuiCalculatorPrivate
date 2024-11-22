#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include <stdio.h>
#include <SDL.h>
#include <string>
#include <windows.h>
#include <SDL_syswm.h>
#include <unordered_map>
#include "CalculatorHelper.h"
#include "ButtonHelper.h"


//static SDL_Surface *load_image(char* buff, int size) {
//    SDL_RWops* rw = SDL_RWFromMem(buff, size);
//    SDL_Surface* temp = IMG_Load_RW(rw, 1);
//    SDL_Surface* image;
//    SDL_FreeSurface(temp);
//
//    return image;
//} //WIP
////TODO




int main(int, char**)
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER);
  //  SDL_Surface* surface = IMG_Load("image.png");

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


//DECLARATIONS

    static char inputBuffer[512] = "";
    bool close_application = false;
     ImVec4 window_color = ImVec4(0.264f, 0.247f, 0.311f, 1.0f);
     static float purp_color[4] = { 0.255f, 0.212f, 0.38f, 1.0f };
     static float operand_button_color[4] = { 0.302f, 0.294f, 0.439f, 1.0f };
     static float clear_button_color[4] = { 0.729f, 0.173f, 0.122f, 1.0f };
     bool startingWindow = true;
     ImVec2 basic_button_size(75, 60);
     static ImVec4 button_frame_color = ImVec4(0.165f, 0.063f, 0.459f, 1.0f);
     ButtonHelper buttonHelper;
     CalculatorHelper* calculateHelper = CalculatorHelper::getInstance();
     ImFontConfig fontConfig;
     fontConfig.RasterizerDensity = 3.0f;
     ImFont* myFont = io.Fonts->AddFontFromFileTTF("Unibody8Pro-Regular.otf", 16.0f, &fontConfig);
     ImFont* biggerMyFont = io.Fonts->AddFontFromFileTTF("Unibody8Pro-Regular.otf", 20.0f, &fontConfig);
    


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

       

        ImGui::GetStyle().AntiAliasedFill = false;
        ImGui::GetStyle().AntiAliasedLines = false;
      
        

        {
            ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = window_color;
            if (startingWindow) {
                ImGui::PushFont(myFont);
                ImGui::SetNextWindowSize(ImVec2(350, 500));
                ImGui::Begin("The Big Sphagetilamaterificater", &startingWindow, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollWithMouse);
                ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
                ImGui::PushStyleColor(ImGuiCol_Border, button_frame_color);
                ImGui::SetWindowFontScale(4.0f);
                ImGui::InputTextMultiline("##Display", inputBuffer, IM_ARRAYSIZE(inputBuffer), ImVec2(330, 75), ImGuiInputTextFlags_ReadOnly);
                ImGui::SetWindowFontScale(1.0f);
                ImGui::PopFont();
                
                ImGui::PushFont(biggerMyFont);
                ImGui::Dummy(basic_button_size);
                ImGui::SameLine();
                    buttonHelper.SetButtonColor(purp_color);
                    buttonHelper.SetButtonColor(operand_button_color);
                if (ImGui::Button("+/-", basic_button_size)) {
                    calculateHelper->ToggleNegative(inputBuffer, IM_ARRAYSIZE(inputBuffer));
                }
                ImGui::SameLine();
                if (ImGui::Button("<-", basic_button_size)) {
                    calculateHelper->Backspace(inputBuffer);
                }
                ImGui::SameLine();
                buttonHelper.PopButtonColor();
                
                buttonHelper.SetButtonColor(clear_button_color);
                if (ImGui::Button("C", basic_button_size)) {

                    calculateHelper->Clear(inputBuffer); 

                }
                buttonHelper.PopButtonColor();
                buttonHelper.SetButtonColor(operand_button_color);
                if (ImGui::Button("tan", basic_button_size)) {
                    strcat_s(inputBuffer, IM_ARRAYSIZE(inputBuffer), "tan ");
                }
                ImGui::SameLine();
                if (ImGui::Button("sin", basic_button_size)) {
                    strcat_s(inputBuffer, IM_ARRAYSIZE(inputBuffer), "sin "); 
                }
                ImGui::SameLine();
                if (ImGui::Button("cos", basic_button_size)) {
                    strcat_s(inputBuffer, IM_ARRAYSIZE(inputBuffer), "cos ");
                }
                ImGui::SameLine();
                if (ImGui::Button("%", basic_button_size)) {
                    strcat_s(inputBuffer, IM_ARRAYSIZE(inputBuffer), "%");
                }
                buttonHelper.PopButtonColor();


                if (ImGui::Button("7", basic_button_size)) {
                    strcat_s(inputBuffer, IM_ARRAYSIZE(inputBuffer), "7");
                }
                ImGui::SameLine();
                if (ImGui::Button("8", basic_button_size)) {
                    strcat_s(inputBuffer, IM_ARRAYSIZE(inputBuffer), "8");
                }
                ImGui::SameLine();
                if (ImGui::Button("9", basic_button_size)) {
                    strcat_s(inputBuffer, IM_ARRAYSIZE(inputBuffer), "9");
                }
                ImGui::SameLine();

                buttonHelper.SetButtonColor(operand_button_color);
                if (ImGui::Button("/", basic_button_size)) {
                    strcat_s(inputBuffer, IM_ARRAYSIZE(inputBuffer), "/");
                }
                buttonHelper.PopButtonColor();



                if (ImGui::Button("4", basic_button_size)) {
                    strcat_s(inputBuffer, IM_ARRAYSIZE(inputBuffer), "4");
                }
                ImGui::SameLine();
                if (ImGui::Button("5", basic_button_size)) { 
                    strcat_s(inputBuffer, IM_ARRAYSIZE(inputBuffer), "5");
                }
                ImGui::SameLine();
                if (ImGui::Button("6", basic_button_size)) {
                    strcat_s(inputBuffer, IM_ARRAYSIZE(inputBuffer), "6");
                }
                ImGui::SameLine();
                buttonHelper.SetButtonColor(operand_button_color);
                if (ImGui::Button("*", basic_button_size)) {
                    strcat_s(inputBuffer, IM_ARRAYSIZE(inputBuffer), "*");
                }
                buttonHelper.PopButtonColor();



                if (ImGui::Button("1", basic_button_size)) {
                    strcat_s(inputBuffer, IM_ARRAYSIZE(inputBuffer), "1");
                }
                ImGui::SameLine();
                if (ImGui::Button("2", basic_button_size)) { 
                    strcat_s(inputBuffer, IM_ARRAYSIZE(inputBuffer), "2");
                }
                ImGui::SameLine();
                if (ImGui::Button("3", basic_button_size)) {
                    strcat_s(inputBuffer, IM_ARRAYSIZE(inputBuffer), "3");
                } 
                ImGui::SameLine();
                buttonHelper.SetButtonColor(operand_button_color);
                if (ImGui::Button("-", basic_button_size)) { 
                    strcat_s(inputBuffer, IM_ARRAYSIZE(inputBuffer), "-");
                }
                buttonHelper.PopButtonColor();


                buttonHelper.SetButtonColor(operand_button_color);
                if (ImGui::Button(".", basic_button_size)) { 
                    calculateHelper->AddDecimal(inputBuffer, IM_ARRAYSIZE(inputBuffer)); 
                }
                buttonHelper.PopButtonColor();
                ImGui::SameLine();
                if (ImGui::Button("0", basic_button_size)) {
                    strcat_s(inputBuffer, IM_ARRAYSIZE(inputBuffer), "0");
                }
                buttonHelper.SetButtonColor(operand_button_color);
                ImGui::SameLine();
                if (ImGui::Button("=", basic_button_size)) { 

                    calculateHelper->EvaluateExpression(inputBuffer, IM_ARRAYSIZE(inputBuffer));

                }
                ImGui::SameLine();
                if (ImGui::Button("+", basic_button_size)) {
                    strcat_s(inputBuffer, IM_ARRAYSIZE(inputBuffer), "+");
                }
                ImGui::PopFont();
                buttonHelper.PopButtonColor();
                buttonHelper.PopButtonColor();
                ImGui::PopStyleColor();
                ImGui::PopStyleVar();
                    ImGui::End();
                    if (startingWindow == false) {
                        ImGui_ImplSDLRenderer2_Shutdown();
                        ImGui_ImplSDL2_Shutdown();
                        ImGui::DestroyContext();
                        exit(0);
                    }
            }
        }
    
       
        



        ImGui::Render();
        SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
       // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // does some stuff to make window transparent
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

