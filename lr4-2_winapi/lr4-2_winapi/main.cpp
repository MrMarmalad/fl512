#include <windows.h>
#include <tchar.h>
#include <format>

#include "Figure.h"
#include "Circle.h"
#include "Triangle.h"
#include "Rect.h"

const int BTN_CIRCLE = 100;
const int BTN_TRIANGLE = 101;
const int BTN_RECTANGLE = 102;
const int BTN_VIEW = 103;
const int BTN_OUTPUT = 104;
const int BTN_GO = 105;

const int BTN_WIDTH = 80;
const int BTN_HEIGHT = 20;

const std::wstring TXT_AREA = L"Площадь фигуры = ";

struct State {
    int figure = 0;
    int action = 0;
    std::string getTextState() {
        return "Figure: " + std::to_string(this->figure) + " Action: " + std::to_string(this->action);
    }

    std::wstring getTextStateW() {
        std::string defaultStr = this->getTextState();
        std::wstring stemp = std::wstring(defaultStr.begin(), defaultStr.end());
        return stemp;
    }
};

//Ширина окна
int winW = 640;
int halfWinW = winW / 2;

// Высота окна
int winH = 480;
int halfWinH = winH / 2;

//состояние программы
State appState = State();

// классы фигур
Circle circle = Circle(10);
Triangle triangle = Triangle({3,4,5});
Rect rectangle = Rect(40, 50);

// Function prototype:
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


// A Win32 app uses a WinMain function instead of main.  We will not look at the details of this function.
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, INT iCmdShow)
{
    LPCWSTR szAppName = L"Lr4-2";
    LPCWSTR szWndName = L"Lr4-2";

    HWND hWnd;
    MSG msg;
    WNDCLASS wndclass;

    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = szAppName;

    if (!RegisterClass(&wndclass))
    {
        MessageBox(NULL, L"Could not create window.", L"Error", 0);
        return 0;
    }

    hWnd = CreateWindow(szAppName, szWndName, WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, hInstance, NULL);

    ShowWindow(hWnd, iCmdShow);
    UpdateWindow(hWnd);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}


// This function processes the various messages for the window.
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
   
    //static int Count;    // Counts the number of times that the user has clicked with the mouse.
    HWND hwndButtonCircle, hwndButtonTriangle,
        hwndButtonRectangle, hwndButtonView, hwndButtonOutput;
    switch (message)
    {
    case WM_CREATE:   // When the window is first created we initialize Count to zero.
        //Count = 0;
        hwndButtonCircle = CreateWindow(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"Circle",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            10,         // x position 
            10,         // y position 
            BTN_WIDTH,        // Button width
            BTN_HEIGHT,        // Button height
            hWnd,     // Parent window
            HMENU(BTN_CIRCLE),       // No menu.
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        hwndButtonTriangle = CreateWindow(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"Triangle",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            10 + BTN_WIDTH + 5,         // x position 
            10,         // y position 
            BTN_WIDTH,        // Button width
            BTN_HEIGHT,        // Button height
            hWnd,     // Parent window
            HMENU(BTN_TRIANGLE),       // No menu.
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        hwndButtonRectangle = CreateWindow(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"Rectangle",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            10 + (BTN_WIDTH + 5)*2,         // x position 
            10,         // y position 
            BTN_WIDTH,        // Button width
            BTN_HEIGHT,        // Button height
            hWnd,     // Parent window
            HMENU(BTN_RECTANGLE),       // No menu.
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        hwndButtonView = CreateWindow(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"View",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            10 + (BTN_WIDTH + 5) * 3,         // x position 
            10,         // y position 
            BTN_WIDTH,        // Button width
            BTN_HEIGHT,        // Button height
            hWnd,     // Parent window
            HMENU(BTN_VIEW),       // No menu.
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        hwndButtonOutput = CreateWindow(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"Output",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            10 + (BTN_WIDTH + 5) * 4,         // x position 
            10,         // y position 
            BTN_WIDTH,        // Button width
            BTN_HEIGHT,        // Button height
            hWnd,     // Parent window
            HMENU(BTN_OUTPUT),       // No menu.
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        return 0;

    case WM_PAINT:
        HDC hDC;
        PAINTSTRUCT ps;
        HPEN hOldPen, hNewPen;
        HBRUSH hOldBrush, hNewBrush;

        hDC = BeginPaint(hWnd, &ps);
        hNewPen = CreatePen(PS_SOLID, 1, RGB(0, 180, 180));   // aqua color (mixes green and blue)
        hOldPen = (HPEN)SelectObject(hDC, hNewPen);
        TextOutW(hDC, 30, 40, appState.getTextStateW().c_str(), appState.getTextStateW().size());

        if (appState.figure != 0 || appState.action != 0) {
            switch (appState.action)
            {
            case BTN_VIEW: {
                switch (appState.figure)
                {
                case BTN_CIRCLE: {
                        hNewBrush = CreateSolidBrush(RGB(0, 255, 0));   // to fill with green
                        hOldBrush = (HBRUSH)SelectObject(hDC, hNewBrush);

                        Ellipse(hDC, halfWinW - 10, halfWinH - 10, halfWinW + 10, halfWinH + 10);   // draw the circle
                        SetTextColor(hDC, RGB(0, 0, 255));   // blue text
                        SetBkMode(hDC, TRANSPARENT);
                        SetBkColor(hDC, RGB(0, 255, 0));   // and green background for the text
                        SetTextColor(hDC, RGB(0, 0, 0));   // restore black text
                        SetBkMode(hDC, OPAQUE);
                        SetBkColor(hDC, RGB(255, 255, 255));  // and white background

                        SelectObject(hDC, hOldBrush);
                        DeleteObject(hNewBrush);
                    break;
                }
                case BTN_RECTANGLE: {
                    MoveToEx(hDC, halfWinW - 50, halfWinH - 50, NULL);
                    LineTo(hDC, halfWinW + 50, halfWinH - 50);
                    LineTo(hDC, halfWinW + 50, halfWinH + 50);
                    LineTo(hDC, halfWinW - 50, halfWinH + 50);
                    LineTo(hDC, halfWinW - 50, halfWinH - 50);
                    break;
                }
                case BTN_TRIANGLE: {
                    MoveToEx(hDC, halfWinW - 50, halfWinH - 50, NULL);
                    LineTo(hDC, halfWinW + 50, halfWinH - 50);
                    LineTo(hDC, halfWinW - 50, halfWinH + 50);
                    LineTo(hDC, halfWinW - 50, halfWinH - 50);
                    break;
                }
                default:
                    break;
                }
                break;
                }
            case BTN_OUTPUT: {
                switch (appState.figure)
                {
                case BTN_CIRCLE:
                    TextOutW(hDC,
                        30,
                        60,
                        (TXT_AREA + std::to_wstring(circle.area())).c_str(),
                        (TXT_AREA + std::to_wstring(circle.area())).size()
                    );
                    break;
                case BTN_RECTANGLE:
                    TextOutW(hDC,
                        30,
                        60,
                        (TXT_AREA + std::to_wstring(rectangle.area())).c_str(),
                        (TXT_AREA + std::to_wstring(rectangle.area())).size()
                    );
                    break;
                case BTN_TRIANGLE:
                    TextOutW(hDC,
                        30,
                        60,
                        (TXT_AREA + std::to_wstring(triangle.area())).c_str(),
                        (TXT_AREA + std::to_wstring(triangle.area())).size()
                    );
                    break;
                default:
                    break;
                }

                break;
            }
            default:
                break;
            }
        }
        //if (Count >= 0)   // User has clicked 0 or more times.  Display a rectangle and message.
        //{
        //    TextOut(hDC, 10, 10, L"This is a test", 14);
        //    MoveToEx(hDC, 100, 10, NULL);
        //    LineTo(hDC, 100, 110);
        //    LineTo(hDC, 300, 110);
        //    LineTo(hDC, 300, 10);
        //    LineTo(hDC, 100, 10);
        //}

        //if (Count >= 1)   // User has clicked at least once.  Display a circle.
        //{
        //    hNewBrush = CreateSolidBrush(RGB(0, 255, 0));   // to fill with green
        //    hOldBrush = (HBRUSH)SelectObject(hDC, hNewBrush);

        //    Ellipse(hDC, 350, 10, 550, 210);   // draw the circle
        //    SetTextColor(hDC, RGB(0, 0, 255));   // blue text
        //    SetBkMode(hDC, TRANSPARENT);
        //    SetBkColor(hDC, RGB(0, 255, 0));   // and green background for the text
        //    TextOut(hDC, 400, 40, L"Circle", 6);
        //    SetTextColor(hDC, RGB(0, 0, 0));   // restore black text
        //    SetBkMode(hDC, OPAQUE);
        //    SetBkColor(hDC, RGB(255, 255, 255));  // and white background

        //    SelectObject(hDC, hOldBrush);
        //    DeleteObject(hNewBrush);
        //}

        //SelectObject(hDC, hOldPen);
        //DeleteObject(hNewPen);

        //if (Count >= 2)   // User has clicked at least twice.  Display a polygon.
        //{
        //    POINT PointArray[6];
        //    PointArray[0].x = 100;
        //    PointArray[0].y = 160;
        //    PointArray[1].x = 50;
        //    PointArray[1].y = 210;
        //    PointArray[2].x = 160;
        //    PointArray[2].y = 260;
        //    PointArray[3].x = 200;
        //    PointArray[3].y = 310;
        //    PointArray[4].x = 300;
        //    PointArray[4].y = 200;
        //    PointArray[5].x = 100;
        //    PointArray[5].y = 160;

        //    hNewPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));   // red, double width
        //    hOldPen = (HPEN)SelectObject(hDC, hNewPen);

        //    hNewBrush = CreateSolidBrush(RGB(10, 200, 70));   // a greenish color
        //    hOldBrush = (HBRUSH)SelectObject(hDC, hNewBrush);
        //    Polygon(hDC, PointArray, 6);

        //    SelectObject(hDC, hOldBrush);
        //    DeleteObject(hNewBrush);

        //    SelectObject(hDC, hOldPen);
        //    DeleteObject(hNewPen);
        //}

        //if (Count >= 3)   // User has clicked at least 3 times.  Display an elliptical smiley face.
        //{
        //    hNewPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));   // blue
        //    hOldPen = (HPEN)SelectObject(hDC, hNewPen);

        //    hNewBrush = CreateSolidBrush(RGB(255, 255, 0));   // to fill with yellow
        //    hOldBrush = (HBRUSH)SelectObject(hDC, hNewBrush);

        //    Ellipse(hDC, 360, 240, 480, 310);
        //    SetPixel(hDC, 400, 260, RGB(0, 0, 255));   // draw one pixel
        //    SetPixel(hDC, 440, 260, RGB(0, 0, 255));
        //    SetPixel(hDC, 420, 270, RGB(0, 0, 255));
        //    Arc(hDC, 380, 260, 460, 290, 380, 275, 460, 275);

        //    SelectObject(hDC, hOldBrush);
        //    DeleteObject(hNewBrush);

        //    SelectObject(hDC, hOldPen);
        //    DeleteObject(hNewPen);
        //}

        EndPaint(hWnd, &ps);
        return 0;

    //case WM_LBUTTONDOWN:      // Left mouse button was clicked   
    //    if (Count >= 3)
    //        // Tell the user that there are no more drawings
    //        MessageBox(hWnd, L"End of sequence of drawings.", L"End", 0);
    //    else
    //    {
    //        Count++;
    //        InvalidateRect(hWnd, NULL, TRUE);   // Causes the window to be redrawn
    //    }

    //    return 0;
    case WM_COMMAND: {
        switch (LOWORD(wParam)) {
            case BTN_CIRCLE: {
                appState.figure = BTN_CIRCLE;
                break;
            }
            case BTN_RECTANGLE: {
                appState.figure = BTN_RECTANGLE;
                break;
            }
            case BTN_TRIANGLE: {
                appState.figure = BTN_TRIANGLE;
                break;
            }
            case BTN_VIEW: {
                appState.action = BTN_VIEW;
                break;
            }
            case BTN_OUTPUT: {
                appState.action = BTN_OUTPUT;
                break;
            }
        }
        //MessageBox(nullptr, appState.getTextStateW().c_str(), L"Error", MB_OK | MB_ICONINFORMATION);
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}

// преобразование строк в широкие строки
std::wstring strToWStr(std::string in) {
    std::wstring stemp = std::wstring(in.begin(), in.end());
    return stemp;
}