//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Render/Renderer.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Layer.h>

#include <toyui/Widget/Widget.h>
#include <toyui/UiWindow.h>

namespace toy
{
	RenderTarget::RenderTarget(Renderer& renderer, MasterLayer& masterLayer, bool gammaCorrected)
		: m_renderer(renderer)
		, m_masterLayer(masterLayer)
		, m_gammaCorrected(gammaCorrected)
	{}

	void RenderTarget::render()
	{
		m_renderer.render(*this);
	}

	Renderer::Renderer(const string& resourcePath)
		: m_resourcePath(resourcePath)
		, m_debugBatch(0)
		, m_debugDepth(0)
	{
		DrawFrame::sRenderer = this;
	}
}
