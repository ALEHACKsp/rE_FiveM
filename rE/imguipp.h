
#ifndef IMGUIPP_H
#include <Windows.h>
#include <string>
#include <functional>
#include <imgui.h>
#include <imgui_internal.h>

#define Helpmarker(s) ImGui::SameLine();ImGui::TextColored(ImColor(255,0,0,255), XOR("[?]")); if (ImGui::IsItemHovered()) { ImGui::SetTooltip(XOR(s)); }
namespace imguipp
{
	float getx();
	float gety();

	void button(const char* label, int& currentTab, int newTab, bool same_line, ImVec2 size = ImVec2());

	void line(const char* id);
	void linevertical();

	void center_text(const char* text, const char* lineId, bool separator);
	void center_text_helpmarker(const char* text, const char* helpformat, const char* lineId, bool separator);
	void center_text_ex(const char* text = nullptr, float width_available = ImGui::GetContentRegionAvail().x, bool separator = false);

	void draw_rect(const char* id, const ImVec2& size, const std::function<void()>& function);

	void uniqueItem(const char* const label, ImVec2 cdata,  const int& tab);
	void uniqueItem2(const char* const label, ImVec2 cdata, const int& tab);

	ImVec4 to_vec4(float r, float g, float b, float a);

}
#define IMGUIPP_H
#endif