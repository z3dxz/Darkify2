#include <windows.h>
#include <Uxtheme.h>
#include <dwmapi.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

const wchar_t wWindowName[] = L"Darkify-2";

// HANDLES
HWND hMain;
HWND hMnTxt;
HWND hEdit;
HWND hSubmit;
HWND hHelpTxt;
HWND hSuccessPage;

// MENUS
constexpr auto IDC_SUBMIT = 7;
constexpr auto IDC_MSG = 34;
constexpr auto IDC_SUCCESSPAGE = 76;

// OTHER
HFONT dFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
HFONT pFont = CreateFont(18, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Verdana"));
HFONT zFont = CreateFont(30, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Verdana Bold"));

int b = 35;

COLORREF bk = RGB(b,b,b);

constexpr auto IDI_ICON1 = 104;

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR lpCmdLine, _In_ int nShowCmd) {

	const wchar_t wClassName[] = L"DarkifyWndClassHost";

	WNDCLASS wc{ };
	wc.hIcon = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR);
	wc.hbrBackground = CreateSolidBrush(bk);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hInstance;
	wc.lpszClassName = wClassName;
	wc.lpfnWndProc = WndProc;

	RegisterClass(&wc);

	hMain = CreateWindowEx(0, wClassName, wWindowName, WS_VISIBLE | WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 200, nullptr, nullptr, hInstance, nullptr);

	MSG msg{ };

	while (GetMessage(&msg, hMain, 0, 0) > 0) {
		if (!IsDialogMessage(hMain, &msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return 0;
}
wchar_t Buffer[256];

int enable = 1;

HBRUSH backEdit;



HDC hEdits;

bool pFound;



HWND test;
HWND test2;

RECT rect;


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {

	case WM_CREATE:
		hMnTxt = CreateWindowEx(0, L"STATIC", L"Darkify-2", WS_CHILD | WS_VISIBLE, 15, 10, 350, 30, hwnd, 0, 0, 0);
		hHelpTxt = CreateWindowEx(0, L"STATIC", L"Which application do you want to darkify?", WS_CHILD | WS_VISIBLE, 15, 50, 350, 25, hwnd, 0, 0, 0);
		hEdit = CreateWindowEx(0, L"EDIT", L"About Windows", BS_FLAT | WS_CHILD | WS_VISIBLE | WS_BORDER, 15, 78, 355, 28, hwnd, (HMENU)IDC_MSG, 0, 0);
		hSubmit = CreateWindowEx(0, L"BUTTON", L"Go!", WS_CHILD | WS_VISIBLE , 15, 115, 130, 28, hwnd, (HMENU)IDC_SUBMIT, 0, 0);
		hSuccessPage = CreateWindowEx(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE , 155, 119, 500, 25, hwnd, 0, 0, 0);

		SendMessage(hSubmit, WM_SETFONT, (WPARAM)pFont, 1);
		SendMessage(hHelpTxt, WM_SETFONT, (WPARAM)pFont, 1);
		SendMessage(hMnTxt, WM_SETFONT, (WPARAM)zFont, 1);
		SendMessage(hEdit, WM_SETFONT, (WPARAM)pFont, 1);
		SendMessage(hSuccessPage, WM_SETFONT, (WPARAM)pFont, 1);

		DwmSetWindowAttribute(hwnd, 20, &enable, sizeof(enable));


		SetWindowTheme(hSubmit, L"Darkmode_Explorer", NULL);
		SetWindowTheme(hMnTxt, L"Darkmode_Explorer", NULL);



		break;

	case WM_SIZE:

		if (GetWindowRect(hwnd, &rect))
		{
			int width = rect.right - rect.left;
			int height = rect.bottom - rect.top;


			SetWindowPos(hEdit, 0, 15, height-123, width-45, 28, 0);
			SetWindowPos(hSubmit, 0, 15, height-85, 0, 0, SWP_NOSIZE);
			SetWindowPos(hSuccessPage, 0, 155, height - 80, 0, 0, SWP_NOSIZE);

			RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
		}


	case WM_COMMAND:

		if (wparam == IDC_SUBMIT) {



			wchar_t txt[64];

			GetWindowText(hEdit, txt, sizeof(txt));

			test = FindWindowEx(0, 0, 0, txt);
			//test = FindWindow(txt, txt);



			if ((int)test != 0) {


				int i = (int)test;
				wchar_t istr[32];
				_itow_s(i, istr, 10);
				DwmSetWindowAttribute(test, 20, &enable, sizeof(enable));
				
				/*
				
				
				RECT extendedFrameBounds{ 0, 0, 0, 0 };
				HRESULT hr = ::DwmGetWindowAttribute(test,
					DWMWA_EXTENDED_FRAME_BOUNDS,
					&extendedFrameBounds,
					sizeof(extendedFrameBounds));

				DWMNCRENDERINGPOLICY ncrp = DWMNCRP_DISABLED;

				// Disable non-client area rendering on the window.
				hr = ::DwmSetWindowAttribute(test, DWMWA_NCRENDERING_POLICY, &ncrp, sizeof(ncrp));
				*/

				Beep(5000, 10);
			}
			else {

				Beep(500, 1000);

				int i = (int)test;
				wchar_t istr[32];
				_itow_s(i, istr, 10);
			}



		}
		break;
	case WM_CTLCOLOREDIT:
		


		wchar_t txt[64];

		GetWindowText(hEdit, txt, sizeof(txt));

		test2 = FindWindowEx(0, 0, 0, txt);
		//test = FindWindow(txt, txt);



		SendMessage(hSuccessPage, WM_SETTEXT, 0, (LPARAM)L"Can not be applied");

		if ((int)test2 != 0) {
			SendMessage(hSuccessPage, WM_SETTEXT, 0, (LPARAM)L"Found");
		}
		else {
			SendMessage(hSuccessPage, WM_SETTEXT, 0, (LPARAM)L"Not Found");
		}


		test = FindWindowEx(0, 0, 0, txt);



		///


		hEdits = (HDC)wparam;


		SetTextColor(hEdits, RGB(255, 255, 255));
		SetBkColor(hEdits, RGB(0, 255, 255));
		SetBkMode(hEdits, TRANSPARENT);



		backEdit = CreateSolidBrush(RGB(20, 20, 20));


		break;

	case WM_CTLCOLORSTATIC:
		hEdits = (HDC)wparam;


		SetTextColor(hEdits, RGB(255, 255, 255));
		SetBkColor(hEdits, RGB(0, 255, 255));
		SetBkMode(hEdits, TRANSPARENT);



		backEdit = CreateSolidBrush(bk);


		break;

	case WM_CTLCOLORBTN:

		return (LRESULT)CreateSolidBrush(bk);




	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);


	}
}

#pragma comment (lib, "uxtheme.lib")
#pragma comment (lib, "dwmapi.lib")

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")