#pragma once


#include "Hazel/Core.h"
#include "Layer.h"

#include <vector>


namespace Hazel
{


	/**
	 * Layer类 的包装
	 */
	class HAZEL_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		// 普通层推送至前半部分
		void PushLayer(Layer* layer);
		// 将层添加至末尾
		void PushOverlay(Layer* overlay);
		// 弹出层推送至后半部分
		void PopLayer(Layer* layer);
		// 弹出覆盖层
		void PopOverlay(Layer* overlay);

		/**
		 * \iterator vector的迭代器 
		 *  以下两个函数返回m_Layers的迭代器，用于遍历层
		 */
		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }


	private:

		std::vector<Layer*> m_Layers;
		// 反向迭代器；更新时,将从图层末尾段开始传递事件; 用于指示在添加新的 Layer 指针时的插入位置。
		std::vector<Layer*>::iterator m_LayerInsert;
	};

}
