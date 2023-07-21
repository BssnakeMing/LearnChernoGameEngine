#include "hzpch.h"
#include "LayerStack.h"

namespace Hazel
{

	LayerStack::LayerStack()
	{
		m_LayerInsert = m_Layers.begin();
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
		{
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		// 在 m_Layers 容器中将 layer 插入到 m_LayerInsert 迭代器指定的位置，并更新 m_LayerInsert 迭代器以指向新插入元素
		m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if(it != m_Layers.end())
		{
			// 移除
			m_Layers.erase(it);
			m_LayerInsert--;
		}
	}

	// 最后渲染
	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if ( it != m_Layers.end())
		{
			m_Layers.erase(it);
		}
	}
}
