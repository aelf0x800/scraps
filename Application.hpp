#pragma once

#include <exception>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

template<class DerrivedType>
class Application
{
protected:
	HINSTANCE _hInstance{};
	HWND _hWnd{};
	WNDCLASS _wndClass{};

public:
	BOOL Create(const wchar_t title[], int width, int height)
	{
		_hInstance = GetModuleHandleW(nullptr);

		_wndClass.lpfnWndProc = WndProc;
		_wndClass.hInstance = _hInstance;
		_wndClass.lpszClassName = title;
		RegisterClass(&_wndClass);

		_hWnd = CreateWindowEx(WS_EX_COMPOSITED, title, title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, nullptr, nullptr, _hInstance, this);
		if (_hWnd == nullptr)
			throw std::exception("CreateWindowExW failed");

		ShowWindow(_hWnd, SW_SHOW);
		UpdateWindow(_hWnd);
	}

	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_CLOSE:
			OnExit();
			break;
		}

		return 0;
	}

private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		DerrivedType* pThis = nullptr;
		
		if (uMsg == WM_NCCREATE)
		{
			CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
			pThis = (DerrivedType*)pCreate->lpCreateParams;
			SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pThis);
			pThis->_hWnd = hWnd;
		}
		else
		{
			pThis = (DerrivedType*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		}

		if (pThis)
			return pThis->HandleMessage(uMsg, wParam, lParam);
		else
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

protected:
	virtual void OnPaint(HDC hDC, PAINTSTRUCT ps) const {}
	virtual void OnResize() const {}
	virtual void OnKeyDown(WPARAM key) const {}
	virtual void OnKeyUp(WPARAM key) const {}
	virtual void OnExit() const {}
};