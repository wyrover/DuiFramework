#pragma once
#include "core/widget_delegate.h"
#include "core/event.h"
#include "core/label.h"

class TestMouseModel
{
public:
	class Observer {
	public:
		virtual void OnModelChanged(TestMouseModel* model) {}
	};
	TestMouseModel();
	~TestMouseModel();

	void SetObserver(Observer* ob);

	void SetPoint(const ui::Point& pt);

	void SetMouseIn(bool v);

	std::wstring ToString();
private:
	ui::Point pt_;
	bool is_mouse_in_{ false };
	Observer* ob_{ NULL };
};

class TestMouseEventWidget
	: public ui::WidgetDelegate
	, public ui::EventListener
	, public TestMouseModel::Observer
{
public:
	virtual void OnInit() override;
	virtual ui::Rect GetInitialRect() override;

	void OnGreenViewMove(ui::Event* event);
	void OnRedViewMove(ui::Event* event);

	virtual void OnModelChanged(TestMouseModel* model) override;
private:
	ui::Label* green_labe_;
	ui::Label* red_labe_;

	ui::EventListener listener_;

	TestMouseModel green_model_;
	TestMouseModel red_model_;
};
