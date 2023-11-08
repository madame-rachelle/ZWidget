
#include "widgets/listview/listview.h"

ListView::ListView(Widget* parent) : Widget(parent)
{
	SetNoncontentSizes(10.0, 5.0, 10.0, 5.0);
}

void ListView::OnPaintFrame(Canvas* canvas)
{
	double w = GetFrameGeometry().width;
	double h = GetFrameGeometry().height;
	Colorf bordercolor = Colorf::fromRgba8(100, 100, 100);
	canvas->fillRect(Rect::xywh(0.0, 0.0, w, h), Colorf(38 / 255.0f, 38 / 255.0f, 38 / 255.0f));
	canvas->fillRect(Rect::xywh(0.0, 0.0, w, 1.0), bordercolor);
	canvas->fillRect(Rect::xywh(0.0, h - 1.0, w, 1.0), bordercolor);
	canvas->fillRect(Rect::xywh(0.0, 0.0, 1.0, h - 0.0), bordercolor);
	canvas->fillRect(Rect::xywh(w - 1.0, 0.0, 1.0, h - 0.0), bordercolor);
}
