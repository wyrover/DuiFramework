#include "stdafx.h"
#include "border.h"

#include "core/view.h"
#include "render/painter.h"

namespace ui
{

	NormalBorder::NormalBorder()
	{
		SetBorder(0, ColorSetRGB(0, 0, 0));
	}

	NormalBorder::~NormalBorder()
	{

	}

	void NormalBorder::SetBorder(Direction direction, int size, Color color)
	{
		border_size_[direction] = size;
		border_color_[direction] = color;
	}

	void NormalBorder::SetBorder(int size, Color color)
	{
		SetBorder(LEFT, size, color);
		SetBorder(TOP, size, color);
		SetBorder(RIGHT, size, color);
		SetBorder(BOTTOM, size, color);
	}

	int NormalBorder::size(Direction direction) const
	{
		return border_size_[direction];
	}

	Color NormalBorder::color(Direction direction) const
	{
		return border_color_[direction];
	}

	void NormalBorder::DoPaint(Painter* painter, const Rect& dest)
	{
		//��->��->��->��
		painter->FillRect(Rect(0, 0, dest.width(), top()), top_color());
		painter->FillRect(Rect(0, 0, left(), dest.height()), left_color());
		painter->FillRect(Rect(0, dest.height() - bottom(), dest.width(),
			bottom()), bottom_color());
		painter->FillRect(Rect(dest.width() - right(), 0, right(),
			dest.height()), right_color());
	}

	int NormalBorder::left() const
	{
		return size(LEFT);
	}

	int NormalBorder::top() const
	{
		return size(TOP);
	}

	int NormalBorder::right() const
	{
		return size(RIGHT);
	}

	int NormalBorder::bottom() const
	{
		return size(BOTTOM);
	}

	Color NormalBorder::left_color() const
	{
		return color(LEFT);
	}

	Color NormalBorder::top_color() const
	{
		return color(TOP);
	}

	Color NormalBorder::right_color() const
	{
		return color(RIGHT);
	}

	Color NormalBorder::bottom_color() const
	{
		return color(BOTTOM);
	}

	ui::Padding NormalBorder::GetPadding()
	{
		return Padding(left(), top(), right(), bottom());
	}

}