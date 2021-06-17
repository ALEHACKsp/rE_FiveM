#include "imguipp.h"
#include "globals.hpp"

Globals* globals = new Globals();

namespace imguipp
{
	int line_counter = 0;

	float getx()
	{
		return ImGui::GetContentRegionAvail().x;
	}

	float gety()
	{
		return ImGui::GetContentRegionAvail().y;
	}

	void button(const char* label, int& currentTab, int newTab, bool same_line, ImVec2 size)
	{
		if (ImGui::Button(label, size))
			currentTab = newTab;
		if (same_line)
			ImGui::SameLine(0, 0);
	}

	void line(const char* id)
	{
		std::string sid = std::string("##Line:") += id;

		ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0, 0, 0, 0));
		ImGui::BeginChild(sid.c_str(), ImVec2(imguipp::getx(), 1), false);
		ImGui::Separator();
		ImGui::EndChild();
		ImGui::PopStyleColor();
	}

	void linevertical()
	{
		ImGui::SameLine(0, 1);
		ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
		ImGui::SameLine(0, 1);
	}

	void center_text(const char* text, const char* lineId, bool separator)
	{
		if (text == nullptr)
			return;

		ImGui::Spacing();
		ImGui::SameLine((ImGui::GetContentRegionAvail().x / 2) - (ImGui::CalcTextSize(text).x / 2));
		ImGui::Text(text);
		ImGui::Spacing();

		if (true == separator)
		{
			ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0, 0, 0, 0));
			ImGui::BeginChild(std::string("##").append(lineId).c_str(), ImVec2(getx(), 1), false);
			ImGui::Separator();
			ImGui::EndChild();
			ImGui::PopStyleColor();
		}
	}

	void center_text_helpmarker(const char* text, const char* helpformat, const char* lineId, bool separator)
	{
		if (text == nullptr)
			return;

		ImGui::Spacing();
		ImGui::SameLine((ImGui::GetContentRegionAvail().x / 2) - (ImGui::CalcTextSize(text).x / 2));
		ImGui::Text(text);
		ImGui::SameLine();
		ImGui::TextColored(ImColor(255, 0, 0, 255), "(?)");
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(helpformat);

		ImGui::Spacing();

		if (true == separator)
		{
			ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0, 0, 0, 0));
			ImGui::BeginChild(std::string("##").append(lineId).c_str(), ImVec2(getx(), 1), false);
			ImGui::Separator();
			ImGui::EndChild();
			ImGui::PopStyleColor();
		}
	}

	void center_text_ex(const char* text, float width_available, bool separator)
	{
		if (text == nullptr)
			return;

		ImGui::Spacing();
		ImGui::SameLine((width_available / 2) - (ImGui::CalcTextSize(text).x / 2));
		ImGui::Text(text);
		ImGui::Spacing();

		if (true == separator)
			ImGui::Separator();
	}


	void draw_rect(const char* id, const ImVec2& size, const std::function<void()>& function)
	{
		std::string title = ("##DrawRect_" + std::string(id));
		ImGui::BeginChild(title.c_str(), size);
		function();
		ImGui::EndChild();
	}

	void uniqueItem(const char* const label, ImVec2 cdata,  const int& tab)
	{
		if (label == nullptr)
			return;

		ImGui::PushStyleColor(ImGuiCol_Button, globals->Menu.Tab == tab ? IM_COL32(44, 44, 44, 255) : IM_COL32(26, 27, 26, 255));
		if (ImGui::Button(label, cdata))
			globals->Menu.Tab = tab;
		ImGui::PopStyleColor();
	}

	void uniqueItem2(const char* const label, ImVec2 cdata, const int& tab)
	{
		if (label == nullptr)
			return;

		ImGui::PushStyleColor(ImGuiCol_Button, globals->Menu.rTab == tab ? IM_COL32(44, 44, 44, 255) : IM_COL32(26, 27, 26, 255));
		if (ImGui::Button(label, cdata))
			globals->Menu.rTab = tab;
		ImGui::PopStyleColor();
	}

	ImVec4 to_vec4(float r, float g, float b, float a)
	{
		return ImVec4(r / 255.0, g / 255.0, b / 255.0, a / 255.0);
	}
}