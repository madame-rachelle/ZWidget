
#pragma once

#include "../../core/widget.h"

class ListView : public Widget
{
public:
	ListView(Widget* parent = nullptr);

protected:
	void OnPaintFrame(Canvas* canvas) override;
};
