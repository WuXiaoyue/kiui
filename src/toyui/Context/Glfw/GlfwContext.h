//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_GLFW_CONTEXT_H
#define TOY_GLFW_CONTEXT_H

/* toy Og */
#include <toyui/Forward.h>
#include <toyui/Render/RenderWindow.h>
#include <toyui/Input/InputDispatcher.h>
#include <toyui/UiWindow.h>

namespace toy
{
	class GlfwRenderWindow : public RenderWindow
	{
	public:
		GlfwRenderWindow(const string& name, int width, int height, bool autoSwap = true);
		~GlfwRenderWindow();

		GLFWwindow* glWindow() { return m_glWindow; }

		void initContext();

		bool nextFrame();
		void resize();

	protected:
		GLFWwindow* m_glWindow;
		bool m_autoSwap;
	};

	class GlfwInputWindow : public InputWindow
	{
	public:
		GlfwInputWindow(GlfwRenderWindow& renderWindow);
		~GlfwInputWindow();

		void initInput(Mouse& mouse, Keyboard& keyboard);

		bool nextFrame();

		void injectMouseMove(double x, double y);
		void injectMouseButton(int button, int action, int mods);
		void injectKey(int key, int scancode, int action, int mods);
		void injectChar(unsigned int codepoint, int mods = 0);
		void injectWheel(double x, double y);

		void resize(size_t width, size_t height);

	protected:
		GlfwRenderWindow& m_renderWindow;
		GLFWwindow* m_glWindow;

		float m_mouseX;
		float m_mouseY;

		Mouse* m_mouse;
		Keyboard* m_keyboard;
	};

	class GlfwContext : public Context
	{
	public:
		GlfwContext(RenderSystem& renderSystem, const string& name, int width, int height, bool fullScreen, bool autoSwap);
	};

	class GlfwRenderSystem : public RenderSystem
	{
	public:
		GlfwRenderSystem(const string& resourcePath);

		virtual unique_ptr<Context> createContext(const string& name, int width, int height, bool fullScreen);
		virtual unique_ptr<Renderer> createRenderer(Context& context);
	};
}

#endif
