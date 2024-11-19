#include "ButtonHelper.h"
void ButtonHelper::SetButtonColor(const float color[4])
{
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(color[0], color[1], color[2], color[3]));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(color[0] * 0.8f, color[1] * 0.8f, color[2] * 0.8f, color[3]));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(color[0] * 0.6f, color[1] * 0.6f, color[2] * 0.6f, color[3]));
}

void ButtonHelper::PopButtonColor()
{
    ImGui::PopStyleColor(3);
}
