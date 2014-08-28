#pragma once

#include "base/basictypes.h"
#include "render/point.h"
#include "render/size.h"
#include "render/transform.h"
#include "render/rect.h"
#include "render/color.h"
#include "render/image_file.h"
#include "render/font.h"

#include <string>

namespace ui
{
	class Widget;
	class Painter
	{
	public:
		Painter(Widget* widget);
		~Painter();

		void Trans(const Transform& m);

		void FillRect(const Rect& rect, Color color);
		void DrawLine(const Rect& rect, int line_size, DWORD color, int nStyle = PS_SOLID);

		void DrawImage(ImageRect* clip, const Rect& dest_rect);
		void DrawImage(ImageFile* image, const Rect& src_rect, const Rect& dest_rect);

		void DrawStringRect(const std::wstring& text, const Font& font, Color color, const Rect& rect);
		void DrawStringRectWithFlags(const std::wstring& text, const Font& font, Color color, const Rect& rect, int flags);
		void DrawStringRectWithFlags(const wchar_t* text, size_t len, const Font& font, Color color, const Rect& rect, int flags);

		static void CalcStringRectWithFlags(const std::wstring& text, const Font& font, const Rect& rect, int flags,
			Rect& out, size_t* len = NULL, int* lines = NULL);
		static void CalcStringSizeWithFlags(const std::wstring& text, const Font& font, const Size& sz, int flags,
			Size& out, size_t* len = NULL, int* lines = NULL);
		static void CalcStringSizeWithFlags(const wchar_t* text, size_t text_len, const Font& font, const Size& sz, int flags,
			Size& out, size_t* len = NULL, int* lines = NULL);
	private:
		Widget* widget_;

		HDC dc_;
		PAINTSTRUCT ps_;

		HBITMAP bitmap_;
		HBITMAP bitmap_prev_;
		Rect rect_;
	};

	class ScopedPainter
	{
	public:
		ScopedPainter(Painter* painter, const Transform& m);
		~ScopedPainter();
	private:
		Transform m_;
		Painter* p_;
	};
}