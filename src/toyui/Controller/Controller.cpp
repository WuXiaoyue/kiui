//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Controller/Controller.h>

#include <toyui/Widget/Widget.h>
#include <toyui/Widget/RootSheet.h>

namespace toy
{
	KeyInputFrame::KeyInputFrame()
		: InputReceiver()
	{}

	void KeyInputFrame::keyUp(KeyEvent& keyEvent)
	{
		auto it = m_keyUpHandlers.find(keyEvent.code);
		if(it != m_keyUpHandlers.end())
		{
			(*it).second();
			keyEvent.consumed = true;
		}
	}

	void KeyInputFrame::keyDown(KeyEvent& keyEvent)
	{
		auto it = m_keyDownHandlers.find(keyEvent.code);
		if(it != m_keyDownHandlers.end())
		{
			(*it).second();
			keyEvent.consumed = true;
		}
	}

	Controller::Controller(ControlMode controlMode, DeviceType deviceType)
		: KeyInputFrame()
		, m_controlMode(controlMode)
		, m_deviceType(deviceType)
		, m_inputWidget(nullptr)
	{
		m_keyUpHandlers[KC_ESCAPE] = [this]() { this->yield(); };
	}

	void Controller::take(Widget& inputWidget)
	{
		m_inputWidget = &inputWidget;
		inputWidget.giveControl(*this, m_controlMode, DEVICE_MOUSE_ALL);
		inputWidget.rootController().takeControl(*this, m_controlMode, DEVICE_KEYBOARD);
	}

	void Controller::yield()
	{
		m_inputWidget->rootController().yieldControl(*this);
		m_inputWidget = nullptr;
	}

	void Controller::leftClick(MouseEvent& mouseEvent)
	{
		if(m_controlMode < CM_MODAL)
			return;

		DimFloat local = m_inputWidget->frame().localPosition(mouseEvent.posX, mouseEvent.posY);
		if(!m_inputWidget->frame().inside(local.x(), local.y()))
			this->yield();
	}
}
