#include "menu.h"
#include "settings.h"
#include "globals.hpp"
#include "imguipp.h"
#include "icons.h"
#include "TextEditor.h"

#include <D3dx9tex.h>
#pragma comment(lib, "D3dx9")

extern ImFont* Consolas;
extern PDIRECT3DTEXTURE9 reImage;
static TextEditor editor;

void Menu::Render()
{
	static auto width = ImGui::GetContentRegionAvailWidth();
	static auto height = ImGui::GetWindowHeight();


	ImGui::Columns(2);
	ImGui::SetColumnOffset(1, 220);

	{
		const ImVec2 Imagedata = ImVec2(86 / 1.05, 105 / 1.05);

		ImGui::NewLine();
		ImGui::SetCursorPosX(Imagedata.x / 1.2);
		ImGui::Image((PVOID)reImage, Imagedata);
		for(int c = 0; c < 5; c++)
			ImGui::Spacing();
	}

	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0,0));
		ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, 0);
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1);
		{
			ImGui::SetCursorPosX(0);
			imguipp::uniqueItem(ICON_FA_CODE" Executor", ImVec2(220, 45), 1);
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 6);

			ImGui::SetCursorPosX(0);
			imguipp::uniqueItem(ICON_FA_DOWNLOAD" Resources", ImVec2(220, 45), 2);
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 6);

			ImGui::SetCursorPosX(0);
			imguipp::uniqueItem(ICON_FA_BOOK" Menus", ImVec2(220, 45), 3);
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 6);

			ImGui::SetCursorPosX(0);
			imguipp::uniqueItem(ICON_FA_COGS" Config", ImVec2(220, 45), 4);
		}
		ImGui::PopStyleVar(3);
		
		ImGui::NewLine();

		imguipp::center_text_ex("Licensed to #4581", 205);
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 6);
		imguipp::center_text_ex("Build Date: Jan 10 2021", 205);

		ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 30);
		ImGui::Text("");
	}

	{
		ImGui::NextColumn();

		if (globals->Menu.Tab == 0)
		{
			ImGui::Spacing();
			imguipp::center_text("Default", "DefaultLine", true);
			ImGui::Text("No section has been selected. Click a button on the left navbar.");
		}

		if (globals->Menu.Tab == 1)
		{
			editor.SetShowWhitespaces(false);
			editor.SetReadOnly(false);
			editor.SetPalette(TextEditor::GetDarkPalette());

			ImGui::Spacing();
			imguipp::center_text("Executor", "ExecutorLine", true);

			ImGui::PushFont(Consolas);
			editor.Render("##REDENGINEENGINE", ImVec2(imguipp::getx(), imguipp::gety() - 45));
			ImGui::PopFont();

			ImGui::Spacing();

			ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(20, 20, 20, 255));
			if (ImGui::Button(ICON_FA_CODE" Execute")) {}
			ImGui::SameLine();
			if (ImGui::Button(ICON_FA_FILE" Execute from file")) {}
			ImGui::SameLine();

			ImGui::PushItemWidth(ImGui::GetContentRegionAvailWidth());
			if (ImGui::BeginCombo("##Cheatlist", nullptr)) 
			{
				for (const auto& resource : globals->resources)
				{
					ImGui::Text(resource);
				}
				ImGui::EndCombo();
			}
			ImGui::PopItemWidth();

			ImGui::PopStyleColor();
		}

		if (globals->Menu.Tab == 2)
		{
			static std::string buttonName = "Save All Resources";

			ImGui::Spacing();
			imguipp::center_text("Resources", "ResourcesLine", true);
			ImGui::Spacing();

			{
				
				imguipp::uniqueItem2(ICON_FA_FOLDER_OPEN" File Browser", ImVec2(ImGui::GetContentRegionAvail().x / 4, 34), 0);
				ImGui::SameLine();
				imguipp::uniqueItem2(ICON_FA_SEARCH_PLUS" Triggers", ImVec2(ImGui::GetContentRegionAvail().x / 3, 34), 1);
				ImGui::SameLine();
				imguipp::uniqueItem2(ICON_FA_TAGS" Stopper", ImVec2(ImGui::GetContentRegionAvail().x / 2, 34), 2);
				ImGui::SameLine();
				imguipp::uniqueItem2(ICON_FA_BAN" Event Blocker", ImVec2(ImGui::GetContentRegionAvail().x / 1, 34), 3);
			
				ImGui::Spacing();
				imguipp::line("underResources");
			}

			ImGui::Spacing();

			
			if (globals->Menu.rTab == 0 || globals->Menu.rTab == 1 || globals->Menu.rTab == 2)
			{
				if (ImGui::ListBoxHeader("##ResourcesListBox", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y - 65)))
				{
					if (globals->Menu.rTab == 0 || globals->Menu.rTab == 1)
					{
						buttonName = "Save All Resources";
						for (const auto& resource : globals->resources)
						{
							const DWORD colors[] = { ImGuiCol_Header , ImGuiCol_HeaderActive , ImGuiCol_HeaderHovered };
							for (const auto& color : colors)
								ImGui::PushStyleColor(color, IM_COL32(30, 30, 30, 255));
							if (ImGui::CollapsingHeader(resource))
							{
								if (globals->Menu.rTab == 1)
									ImGui::Text("TriggerServerEvent('test', 123')");
							}
							ImGui::PopStyleColor(IM_ARRAYSIZE(colors));
						}
					}

					if (globals->Menu.rTab == 2)
					{
						buttonName = std::string("Stop ") += globals->current_resource;
						for (const auto& resource : globals->resources)
						{
							const bool selected = (globals->current_resource == resource);
							if (ImGui::Selectable(resource, selected))
								globals->current_resource = resource;
							if (selected)
								ImGui::SetItemDefaultFocus();
						}
					}
					ImGui::ListBoxFooter();
				}
			}
			else if (globals->Menu.rTab == 3)
			{
				buttonName = "Save All Resources";

				ImGui::Checkbox("##BlockerOn", &globals->blockerOn);
				ImGui::SameLine(); ImGui::Text("Enabled"); ImGui::Spacing();

				imguipp::line("UnderBlocker");

				{
					ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(32, 32, 32, 255));
					ImGui::BeginChild("##LeftSideBlocker", ImVec2(ImGui::GetContentRegionAvail().x / 2, ImGui::GetContentRegionAvail().y - 55));
					ImGui::EndChild();
					ImGui::PopStyleColor();
				}

				ImGui::SameLine();
				ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
				ImGui::SameLine();

				{
					ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0, 0, 0, 0));
					ImGui::BeginChild("##RightSideBlocker", ImVec2(ImGui::GetContentRegionAvail().x , ImGui::GetContentRegionAvail().y - 55));
					{
						ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(4, 4));
						ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x);
						ImGui::InputTextWithHint("##EventBuffer", "Event Name", globals->eventBuffer, 512);
						ImGui::PopItemWidth();

						imguipp::line("UnderEventBuffer");

						if (ImGui::Button("Add", ImVec2(ImGui::GetContentRegionAvail().x, 33))) {}
						if (ImGui::Button("Remove", ImVec2(ImGui::GetContentRegionAvail().x, 33))) {}
						ImGui::PopStyleVar();
					}
					ImGui::EndChild();
					ImGui::PopStyleColor();
				}

			}

			ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 43);
			imguipp::line("UnderscoreButton");
			if (ImGui::Button(buttonName.c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 33)))
			{
				if (buttonName.find("Stop") == std::string::npos)
				{
					MessageBoxA(0, "Dump Saved in C:\\redENGINE\\127.0.0.1", "rE", MB_OK | MB_ICONINFORMATION);
				}
			}
		}
		
		if (globals->Menu.Tab == 3)
		{
			ImGui::Spacing();
			imguipp::center_text("Menus", "MenusLine", true);
			ImGui::Spacing();

			{
				ImGui::BeginChild("##EntireMenusChild", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y ));
				{
					{
						ImGui::BeginChild("##FirstLeftSideMenus", ImVec2(ImGui::GetContentRegionAvail().x / 2, ImGui::GetContentRegionAvail().y));
						{
							imguipp::center_text(ICON_FA_HOME " Free Menus " ICON_FA_HOME, "FreeMenusLine", true);
							if (ImGui::ListBoxHeader("##FreeSide", ImVec2(ImGui::GetContentRegionAvail().x, 300)))
							{
								for (const auto& free : globals->free_menus)
								{
									const bool selected = (free == globals->freemenu);
									if (ImGui::Selectable(free, selected))
										globals->freemenu = free;

									if (selected)
										ImGui::SetItemDefaultFocus();
								}
								ImGui::ListBoxFooter();
							}
							if (ImGui::Button((std::string("Run ") += globals->freemenu).c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 33)))
							{

							}
						}
						ImGui::EndChild();
					}

					ImGui::SameLine();

					{
						ImGui::BeginChild("##FirstRightSideMenus", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y - 55));
						{
							imguipp::center_text(ICON_FA_STAR " Premium Menus " ICON_FA_STAR, "PremiumMenusLine", true);
							if (ImGui::ListBoxHeader("##PremSide", ImVec2(ImGui::GetContentRegionAvail().x, 300)))
							{
								for (const auto& prem : globals->prem_menus)
								{
									const bool selected = (prem == globals->premmenu);
									if (ImGui::Selectable(prem, selected))
										globals->premmenu = prem;

									if (selected)
										ImGui::SetItemDefaultFocus();
								}
								ImGui::ListBoxFooter();
							}
							if (ImGui::Button((std::string("Run ") += globals->premmenu).c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 33)))
							{

							}
						}
						ImGui::EndChild();
					}
				}
				ImGui::EndChild();
			}
		}

		if (globals->Menu.Tab == 4)
		{
			ImGui::Spacing();
			imguipp::center_text("Config", "ConfigLine", true);
			ImGui::Spacing();

			{
				ImGui::BeginChild("##ConfigLeft", ImVec2(ImGui::GetContentRegionAvail().x / 2, ImGui::GetContentRegionAvail().y));
				{
					imguipp::center_text_helpmarker("Safe Mode", "Safemode creates a isolated scripting environment. Anticheats cannot attach to.", "SafeModeLine", true);
					ImGui::Checkbox("##IsolatedMode", &globals->isolated);
					ImGui::SameLine(); ImGui::Text("Enabled");
					imguipp::line("SafeModeLine2");
				}
				{
					imguipp::center_text_helpmarker("ScriptHook Bypass", "Allows you to use .asi menus.", "SHModeLine", true);
					ImGui::Checkbox("##shAllowCheck", &globals->shAllow);
					ImGui::SameLine(); ImGui::Text("Enabled");
					imguipp::line("SHModeLine2");
				}
				ImGui::EndChild();
			}

			ImGui::SameLine();
			ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
			ImGui::SameLine();

			{
				ImGui::BeginChild("##ConfigRight", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y));
				{
					imguipp::center_text("Server related stuff", "ServerRelated", true);
					ImGui::Text("Server IP: 51.210.178.158");
					imguipp::line("ServerRelated2");
				}
				ImGui::EndChild();
			}
		}
	}
	
}

void Menu::Theme()
{
	auto& style = ImGui::GetStyle();

	style.WindowMinSize = ImVec2(900, 540); 

	style.FrameBorderSize = 0;
	style.WindowRounding = 0;
	style.WindowPadding = ImVec2(0, 0);
	style.TabRounding = 0;
	style.ScrollbarRounding = 0;
	style.FramePadding = ImVec2(8, 6);
	style.WindowTitleAlign = ImVec2(0.0f, 0.5f);

	style.Colors[ImGuiCol_TitleBg] = ImColor(227, 0, 40, 255);		
	style.Colors[ImGuiCol_TitleBgActive] = ImColor(227, 0, 40, 255);			
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImColor(15, 15, 15, 50);		   

	style.Colors[ImGuiCol_Border] = ImColor(0, 0, 0, 0);
	style.Colors[ImGuiCol_WindowBg] = ImColor(12, 12, 12, 255);				

	style.Colors[ImGuiCol_Button] = ImColor(24, 25, 24, 255);		
	style.Colors[ImGuiCol_ButtonActive] = ImColor(44, 44, 44, 255);	      
	style.Colors[ImGuiCol_ButtonHovered] = ImColor(44, 44, 44, 255);		

	style.Colors[ImGuiCol_CheckMark] = ImColor(255, 255, 255, 255);			

	style.Colors[ImGuiCol_FrameBg] = ImColor(36, 37, 36, 255);
	style.Colors[ImGuiCol_FrameBgActive] = ImColor(36, 37, 36, 255);
	style.Colors[ImGuiCol_FrameBgHovered] = ImColor(36, 37, 36, 255);

	style.Colors[ImGuiCol_Header] = ImColor(54, 56, 54, 255);			// for collapsing headers , etc
	style.Colors[ImGuiCol_HeaderActive] = ImColor(54, 56, 54, 255);
	style.Colors[ImGuiCol_HeaderHovered] = ImColor(54, 56, 54, 255);

	style.Colors[ImGuiCol_ResizeGrip] = ImColor(51, 49, 50, 255);		    // the resize grip thing bottom right
	style.Colors[ImGuiCol_ResizeGripActive] = ImColor(54, 53, 55);			// when you hold it / active
	style.Colors[ImGuiCol_ResizeGripHovered] = ImColor(51, 49, 50, 255);			// when you hover over it

	style.Colors[ImGuiCol_SliderGrab] = ImColor(249, 79, 49, 255);
	style.Colors[ImGuiCol_SliderGrabActive] = ImColor(249, 79, 49, 255);
	// 54 , 56, 54 , 255
	style.Colors[ImGuiCol_Border] = ImColor(54, 54, 54);
	style.Colors[ImGuiCol_Separator] = ImColor(54, 54, 54);
	style.Colors[ImGuiCol_SeparatorActive] = ImColor(54, 54, 54);
	style.Colors[ImGuiCol_SeparatorHovered] = ImColor(54, 54, 54);
}