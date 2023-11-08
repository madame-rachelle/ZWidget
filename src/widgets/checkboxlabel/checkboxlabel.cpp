
#include "widgets/checkboxlabel/checkboxlabel.h"

CheckboxLabel::CheckboxLabel(Widget* parent) : Widget(parent)
{
}

void CheckboxLabel::SetText(const std::string& value)
{
	if (text != value)
	{
		text = value;
		Update();
	}
}

const std::string& CheckboxLabel::GetText() const
{
	return text;
}

double CheckboxLabel::GetPreferredHeight() const
{
	return 20.0;
}

void CheckboxLabel::OnPaint(Canvas* canvas)
{
	canvas->drawText(Point(0.0, GetHeight() - 5.0), Colorf(1.0f, 1.0f, 1.0f), "[x] " + text);
}
