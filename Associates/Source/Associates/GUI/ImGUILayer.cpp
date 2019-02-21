#include "Assoc_pch.h"
#include "ImGUILayer.h"

#include "Platform/OpenGL/ImGUI_OpenGL_Render.h"
#include <GLFW/glfw3.h>

#include "Associates/Application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Associates
{
	ImGUILayer::ImGUILayer() : Layer("ImGUILayer")
	{

	}

	ImGUILayer::~ImGUILayer()
	{
	}

	void ImGUILayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& IO = ImGui::GetIO();
		IO.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		IO.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		// TEMPORARY: should eventually use Hazel key codes
		IO.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		IO.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		IO.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		IO.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		IO.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		IO.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		IO.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		IO.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		IO.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		IO.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		IO.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		IO.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		IO.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		IO.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		IO.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		IO.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		IO.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		IO.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		IO.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		IO.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		IO.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGUILayer::OnDetach()
	{

	}

	void ImGUILayer::OnUpdate()
	{
		ImGuiIO& IO = ImGui::GetIO();
		Application& App = Application::Get();
		IO.DisplaySize = ImVec2(App.GetWindow().GetWidth(), App.GetWindow().GetHeight());

		float Time = (float)glfwGetTime();
		IO.DeltaTime = m_Time > 0.0 ? (Time - m_Time) : (1.0f / 60.0f);
		m_Time = Time;
	
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool bShow = true;
		ImGui::ShowDemoWindow(&bShow);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGUILayer::OnEvent(Event & Event)
	{
		EventDispatcher Dispatcher(Event);
		Dispatcher.Dispatch<MouseButtonPressedEvent>(ASSOC_BIND_EVENT_FN(ImGUILayer::OnMouseButtonPressedEvent));
		Dispatcher.Dispatch<MouseButtonReleasedEvent>(ASSOC_BIND_EVENT_FN(ImGUILayer::OnMouseButtonReleasedEvent));
		Dispatcher.Dispatch<MouseMovedEvent>(ASSOC_BIND_EVENT_FN(ImGUILayer::OnMouseMovedEvent));
		Dispatcher.Dispatch<MouseScrolledEvent>(ASSOC_BIND_EVENT_FN(ImGUILayer::OnMouseScrolledEvent));
		Dispatcher.Dispatch<KeyPressedEvent>(ASSOC_BIND_EVENT_FN(ImGUILayer::OnKeyPressedEvent));
		Dispatcher.Dispatch<KeyReleasedEvent>(ASSOC_BIND_EVENT_FN(ImGUILayer::OnKeyReleasedEvent));
		Dispatcher.Dispatch<KeyTypedEvent>(ASSOC_BIND_EVENT_FN(ImGUILayer::OnKeyTypedEvent));
		Dispatcher.Dispatch<WindowResizeEvent>(ASSOC_BIND_EVENT_FN(ImGUILayer::OnWindowResizedEvent));
	}

	bool ImGUILayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent & Event)
	{
		ImGuiIO& IO = ImGui::GetIO();
		IO.MouseDown[Event.GetMouseButton()] = true;

		return false;
	}

	bool ImGUILayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent & Event)
	{
		ImGuiIO& IO = ImGui::GetIO();
		IO.MouseDown[Event.GetMouseButton()] = false;

		return false;
	}

	bool ImGUILayer::OnMouseMovedEvent(MouseMovedEvent & Event)
	{
		ImGuiIO& IO = ImGui::GetIO();
		IO.MousePos = ImVec2(Event.GetX(), Event.GetY());

		return false;
	}

	bool ImGUILayer::OnMouseScrolledEvent(MouseScrolledEvent & Event)
	{
		ImGuiIO& IO = ImGui::GetIO();
		IO.MouseWheel += Event.GetXOffset();
		IO.MouseWheelH += Event.GetYOffset();

		return false;
	}

	bool ImGUILayer::OnKeyPressedEvent(KeyPressedEvent & Event)
	{
		ImGuiIO& IO = ImGui::GetIO();
		IO.KeysDown[Event.GetKeyCode()] = true;

		IO.KeyCtrl = IO.KeysDown[GLFW_KEY_LEFT_CONTROL] || IO.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		IO.KeyShift = IO.KeysDown[GLFW_KEY_LEFT_SHIFT] || IO.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		IO.KeyAlt = IO.KeysDown[GLFW_KEY_LEFT_ALT] || IO.KeysDown[GLFW_KEY_RIGHT_ALT];
		IO.KeySuper = IO.KeysDown[GLFW_KEY_LEFT_SUPER] || IO.KeysDown[GLFW_KEY_RIGHT_SUPER];

		return false;
	}

	bool ImGUILayer::OnKeyReleasedEvent(KeyReleasedEvent & Event)
	{
		return false;
	}

	bool ImGUILayer::OnKeyTypedEvent(KeyTypedEvent& Event)
	{
		ImGuiIO& IO = ImGui::GetIO();

		int KeyCode = Event.GetKeyCode();
		if (KeyCode > 0 && 0x10000)
			IO.AddInputCharacter((unsigned short)KeyCode);

		return false;
	}

	bool ImGUILayer::OnWindowResizedEvent(WindowResizeEvent & Event)
	{
		ImGuiIO& IO = ImGui::GetIO();
		IO.DisplaySize = ImVec2(Event.GetWidth(), Event.GetHeight());
		IO.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, Event.GetWidth(), Event.GetHeight());

		return false;
	}
}
