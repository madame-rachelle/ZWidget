#pragma once

#define NOMINMAX
#define WIN32_MEAN_AND_LEAN
#include <Windows.h>

#include <list>
#include <zwidget/window/window.h>

class Win32Window : public DisplayWindow
{
public:
	Win32Window(DisplayWindowHost* windowHost);
	~Win32Window();

	void SetWindowTitle(const std::string& text) override;
	void SetWindowFrame(const Rect& box) override;
	void SetClientFrame(const Rect& box) override;
	void Show() override;
	void ShowFullscreen() override;
	void ShowMaximized() override;
	void ShowMinimized() override;
	void ShowNormal() override;
	void Hide() override;
	void Activate() override;
	void ShowCursor(bool enable) override;
	void LockCursor() override;
	void UnlockCursor() override;
	void Update() override;
	bool GetKeyState(EInputKey key) override;

	Rect GetWindowFrame() const override;
	Size GetClientSize() const override;
	int GetPixelWidth() const override;
	int GetPixelHeight() const override;
	double GetDpiScale() const override;

	void PresentBitmap(int width, int height, const uint32_t* pixels) override;

	Point GetLParamPos(LPARAM lparam) const;

	static void ProcessEvents();
	static void RunLoop();
	static void ExitLoop();

	static bool ExitRunLoop;
	static std::list<Win32Window*> Windows;
	std::list<Win32Window*>::iterator WindowsIterator;

	LRESULT OnWindowMessage(UINT msg, WPARAM wparam, LPARAM lparam);
	static LRESULT CALLBACK WndProc(HWND windowhandle, UINT msg, WPARAM wparam, LPARAM lparam);

	DisplayWindowHost* WindowHost = nullptr;

	HWND WindowHandle = 0;
	bool Fullscreen = false;

	bool MouseLocked = false;
	POINT MouseLockPos = {};
};
