#pragma once

#include "CADie/Layer.h"
#include "CADie/Events/MouseEvent.h"
#include "CADie/Events/KeyEvent.h"
#include "CADie/Events/ApplicationEvent.h"

namespace CADie {

	class CADIE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}