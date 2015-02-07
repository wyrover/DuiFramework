﻿#pragma once
#include "uikit/widget/ui_view.h"
#include "uikit/ui_responder.h"

namespace ui
{
	class UIViewController : public UIResponder
	{
	public:
		UIViewController();
		~UIViewController();

		virtual void Init() override;

		virtual UIResponder* NextResponder() const override;

		virtual UIView* view() { return view_; }
		virtual void setView(UIView* view) { view_ = view; }
	protected:
		UIView* view_;
	};
}