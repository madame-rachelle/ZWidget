
#include <zwidget/core/widget.h>
#include <zwidget/core/resourcedata.h>
#include <zwidget/window/window.h>
#include <zwidget/widgets/textedit/textedit.h>
#include <zwidget/widgets/mainwindow/mainwindow.h>

#ifdef WIN32

#include <Windows.h>
#include <stdexcept>

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

static std::wstring to_utf16(const std::string& str)
{
	if (str.empty()) return {};
	int needed = MultiByteToWideChar(CP_UTF8, 0, str.data(), (int)str.size(), nullptr, 0);
	if (needed == 0)
		throw std::runtime_error("MultiByteToWideChar failed");
	std::wstring result;
	result.resize(needed);
	needed = MultiByteToWideChar(CP_UTF8, 0, str.data(), (int)str.size(), &result[0], (int)result.size());
	if (needed == 0)
		throw std::runtime_error("MultiByteToWideChar failed");
	return result;
}

static std::vector<uint8_t> ReadAllBytes(const std::string& filename)
{
	HANDLE handle = CreateFile(to_utf16(filename).c_str(), FILE_READ_ACCESS, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (handle == INVALID_HANDLE_VALUE)
		throw std::runtime_error("Could not open " + filename);

	LARGE_INTEGER fileSize;
	BOOL result = GetFileSizeEx(handle, &fileSize);
	if (result == FALSE)
	{
		CloseHandle(handle);
		throw std::runtime_error("GetFileSizeEx failed");
	}

	std::vector<uint8_t> buffer(fileSize.QuadPart);

	DWORD bytesRead = 0;
	result = ReadFile(handle, buffer.data(), (DWORD)buffer.size(), &bytesRead, nullptr);
	if (result == FALSE || bytesRead != buffer.size())
	{
		CloseHandle(handle);
		throw std::runtime_error("ReadFile failed");
	}

	CloseHandle(handle);

	return buffer;
}

std::vector<uint8_t> LoadWidgetFontData(const std::string& name)
{
	return ReadAllBytes("C:\\Windows\\Fonts\\segoeui.ttf");
}

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	auto mainwindow = new MainWindow();
	auto textedit = new TextEdit(mainwindow);
	textedit->SetText(R"(
#version 460

in vec4 AttrPos;
in vec4 AttrColor;
out vec4 Color;

void main()
{
    gl_Position = AttrPos;
    Color = AttrColor;
}
)");
	mainwindow->SetWindowTitle("ZWidget Example");
	mainwindow->SetFrameGeometry(100.0, 100.0, 1700.0, 900.0);
	mainwindow->SetCentralWidget(textedit);
	textedit->SetFocus();
	mainwindow->Show();

	DisplayWindow::RunLoop();

	return 0;
}

#else

int main()
{
	return 0;
}

#endif
