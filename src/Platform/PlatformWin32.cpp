#include "CrazyEngine/Platform/Platform.h"

#if PLATFORM_WINDOWS

#include <windows.h>
#include <windowsx.h>
#include <iostream>
#include <optional>

#include <Vendor/glad/glad.h>

#define WGL_CONTEXT_MAJOR_VERSION_ARB             0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB             0x2092
#define WGL_CONTEXT_PROFILE_MASK_ARB              0x9126
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB          0x00000001

#define WGL_DRAW_TO_WINDOW_ARB                    0x2001
#define WGL_ACCELERATION_ARB                      0x2003
#define WGL_SUPPORT_OPENGL_ARB                    0x2010
#define WGL_DOUBLE_BUFFER_ARB                     0x2011
#define WGL_PIXEL_TYPE_ARB                        0x2013
#define WGL_COLOR_BITS_ARB                        0x2014
#define WGL_DEPTH_BITS_ARB                        0x2022
#define WGL_STENCIL_BITS_ARB                      0x2023

#define WGL_FULL_ACCELERATION_ARB                 0x2027
#define WGL_TYPE_RGBA_ARB                         0x202B

typedef HGLRC WINAPI wglCreateContextAttribsARB_type(HDC hdc, HGLRC hShareContext, const int *attribList);
wglCreateContextAttribsARB_type* wglCreateContextAttribsARB;

typedef BOOL WINAPI wglChoosePixelFormatARB_type(HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats);
wglChoosePixelFormatARB_type* wglChoosePixelFormatARB;

namespace CrazyEngine
{
    struct Win32InternalState
    {
        // Windows Objects
        HINSTANCE HInstance;
        HWND HWND;
        HDC HDC;
        HGLRC HGLRC;

        // Callbacks
        std::optional<Callbacks> Callbacks;

        // Clock Objects
        double ClockFrequency;
        LARGE_INTEGER StartTime;
    };  

    LRESULT CALLBACK Win32ProcessMessage(HWND hwnd, std::uint32_t message, WPARAM wParam, LPARAM lParam);

    Platform::Platform(const char* appTitle, std::uint32_t x, std::uint32_t y, std::uint32_t width, std::uint32_t height)
    {
        // Creating Win32 Internal State

        m_InternalState = new Win32InternalState();
        Win32InternalState* state = (Win32InternalState*)m_InternalState;
        state->Callbacks.reset();

        state->HInstance = GetModuleHandleA(0);

        // Initialising OpenGL

        WNDCLASSA dummyClass { };
        dummyClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC,
        dummyClass.lpfnWndProc = Win32ProcessMessage;
        dummyClass.hInstance = GetModuleHandle(0);
        dummyClass.lpszClassName = "DummyWindow";

        if (!RegisterClassA(&dummyClass))
        {
            MessageBoxA(0, "Dummy window registration failed", "Error", MB_ICONEXCLAMATION | MB_OK);
            return;
        }

        HWND dummyWindow = CreateWindowExA(0, dummyClass.lpszClassName, "Dummy OpenGL Window", 0, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, dummyClass.hInstance, 0);

        if (!dummyWindow)
        {
            MessageBoxA(0, "Dummy window creation failed", "Error", MB_ICONEXCLAMATION | MB_OK);
            return;
        }

        PIXELFORMATDESCRIPTOR dummyPFD { };
        dummyPFD.nSize = sizeof(dummyPFD);
        dummyPFD.nVersion = 1;
        dummyPFD.iPixelType = PFD_TYPE_RGBA;
        dummyPFD.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        dummyPFD.cColorBits = 32;
        dummyPFD.cAlphaBits = 8;
        dummyPFD.iLayerType = PFD_MAIN_PLANE;
        dummyPFD.cDepthBits = 24;
        dummyPFD.cStencilBits = 8;

        HDC dummyHDC = GetDC(dummyWindow);

        int dummyPixelFormat = ChoosePixelFormat(dummyHDC, &dummyPFD);
        if (!dummyPixelFormat)
        {
            MessageBoxA(0, "Failed to locate a suitable dummy pixel format.", "Error", MB_ICONEXCLAMATION | MB_OK);
            return;
        }

        if (!SetPixelFormat(dummyHDC, dummyPixelFormat, &dummyPFD))
        {
            MessageBoxA(0, "Failed to set dummy pixel format.", "Error", MB_ICONEXCLAMATION | MB_OK);
            return;
        }

        HGLRC dummyContext = wglCreateContext(dummyHDC);
        if (!dummyContext)
        {
            MessageBoxA(0, "Failed to create dummy OpenGL context.", "Error", MB_ICONEXCLAMATION | MB_OK);
            return;
        }

        if (!wglMakeCurrent(dummyHDC, dummyContext))
        {
            MessageBoxA(0, "Failed to set dummy OpenGL context as current.", "Error", MB_ICONEXCLAMATION | MB_OK);
            return;
        }

        wglCreateContextAttribsARB = (wglCreateContextAttribsARB_type*)wglGetProcAddress("wglCreateContextAttribsARB");
        wglChoosePixelFormatARB = (wglChoosePixelFormatARB_type*)wglGetProcAddress("wglChoosePixelFormatARB");

        wglMakeCurrent(dummyHDC, 0);
        wglDeleteContext(dummyContext);
        ReleaseDC(dummyWindow, dummyHDC);
        DestroyWindow(dummyWindow);

        // Creating + Registering Window Class

        HICON icon = LoadIcon(state->HInstance, IDI_APPLICATION);

        WNDCLASSA windowClass { };
        windowClass.style = CS_DBLCLKS;
        windowClass.lpfnWndProc = Win32ProcessMessage;
        windowClass.cbClsExtra = 0;
        windowClass.cbWndExtra = 0;
        windowClass.hInstance = state->HInstance;
        windowClass.hIcon = icon;
        windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
        windowClass.hbrBackground = NULL;
        windowClass.lpszClassName = "Window";

        if (!RegisterClassA(&windowClass))
        {
            MessageBoxA(0, "Window registration failed.", "Error", MB_ICONEXCLAMATION | MB_OK);
            return;
        }

        std::uint32_t clientX = x;
        std::uint32_t clientY = y;
        std::uint32_t clientWidth = width;
        std::uint32_t clientHeight = height;

        std::uint32_t windowX = clientX;
        std::uint32_t windowY = clientY;
        std::uint32_t windowWidth = clientWidth;
        std::uint32_t windowHeight = clientHeight;
        
        std::uint32_t windowStyle = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | CS_OWNDC;
        std::uint32_t windowExStyle = WS_EX_APPWINDOW;

        windowStyle |= WS_MAXIMIZEBOX;
        windowStyle |= WS_MINIMIZEBOX;
        windowStyle |= WS_THICKFRAME;

        RECT borderSize = { 0, 0, 0, 0 };
        AdjustWindowRectEx(&borderSize, windowStyle, 0, windowExStyle);

        windowX += borderSize.left;
        windowY += borderSize.top;
        windowWidth += borderSize.right - borderSize.left;
        windowHeight += borderSize.bottom - borderSize.top;

        HWND windowHandle = CreateWindowExA(windowExStyle, "Window", appTitle, windowStyle, windowX, windowY, windowWidth, windowHeight, 0, 0, state->HInstance, 0);

        if (!windowHandle)
        {
            MessageBoxA(NULL, "Window creation failed.", "Error", MB_ICONEXCLAMATION | MB_OK);
            return;
        }
        else
        {
            state->HWND = windowHandle;
        }

        // Creating OpenGL Rendering Context

        int pixelFormatAttributes[] = 
        {
            WGL_DRAW_TO_WINDOW_ARB,     GL_TRUE,
            WGL_SUPPORT_OPENGL_ARB,     GL_TRUE,
            WGL_DOUBLE_BUFFER_ARB,      GL_TRUE,
            WGL_ACCELERATION_ARB,       WGL_FULL_ACCELERATION_ARB,
            WGL_PIXEL_TYPE_ARB,         WGL_TYPE_RGBA_ARB,
            WGL_COLOR_BITS_ARB,         32,
            WGL_DEPTH_BITS_ARB,         24,
            WGL_STENCIL_BITS_ARB,       8,
            0 
        };

        state->HDC = GetDC(state->HWND);
        int pixelFormat;
        UINT formatCount;

        wglChoosePixelFormatARB(state->HDC, pixelFormatAttributes, 0, 1, &pixelFormat, &formatCount);

        if (!formatCount)
        {
            MessageBoxA(NULL, "Failed to set the OpenGL 3.3 pixel format.", "Error", MB_ICONEXCLAMATION | MB_OK);
            return;
        }

        PIXELFORMATDESCRIPTOR PFD;
        DescribePixelFormat(state->HDC, pixelFormat, sizeof(PFD), &PFD);
        if (!SetPixelFormat(state->HDC, pixelFormat, &PFD))
        {
            MessageBoxA(NULL, "Failed to set the OpenGL 3.3 pixel format.", "Error", MB_ICONEXCLAMATION | MB_OK);
            return;
        }

        int gl33Attributes[] =
        {
            WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
            WGL_CONTEXT_MINOR_VERSION_ARB, 3,
            WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
            0,
        };

        state->HGLRC = wglCreateContextAttribsARB(state->HDC, 0, gl33Attributes);

        if (!state->HGLRC)
        {
            MessageBoxA(NULL, "Failed to set the OpenGL 3.3 context.", "Error", MB_ICONEXCLAMATION | MB_OK);
            return;
        }

        if (!wglMakeCurrent(state->HDC, state->HGLRC))
        {
            MessageBoxA(NULL, "Failed to set the OpenGL 3.3 context as current.", "Error", MB_ICONEXCLAMATION | MB_OK);
            return;
        }

        // Loading GLAD

        gladLoadGL();
        glViewport(0, 0, width, height);

        // Showing Window

        bool shouldActivate = true;
        std::uint32_t cmdFlags = shouldActivate ? SW_SHOW : SW_SHOWNOACTIVATE;
        ShowWindow(state->HWND, cmdFlags);

        SetWindowLongPtrA(state->HWND, GWLP_USERDATA, (LONG_PTR)state);

        // Setting Up Clock

        LARGE_INTEGER frequency;
        QueryPerformanceFrequency(&frequency);
        state->ClockFrequency = 1.0f / (double)frequency.QuadPart;
        QueryPerformanceCounter(&(state->StartTime));
    }

    void Platform::Terminate()
    {
        Win32InternalState* state = (Win32InternalState*)m_InternalState;

        ReleaseDC(state->HWND, state->HDC);
        wglDeleteContext(state->HGLRC);

        if (state->HWND != nullptr)
        {
            DestroyWindow(state->HWND);
            state->HWND = nullptr;
        }
    }

    void Platform::SetCallbacks(Callbacks callbacks)
    {
        Win32InternalState* state = (Win32InternalState*)m_InternalState;
        state->Callbacks = callbacks;
    }

    bool Platform::PumpMessages()
    {
        MSG message;

        while (PeekMessageA(&message, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&message);
            DispatchMessageA(&message);
        }

        return true;
    }

    double Platform::GetAbsoluteTime() const noexcept
    {
        Win32InternalState* state = (Win32InternalState*)m_InternalState;

        LARGE_INTEGER now;
        QueryPerformanceCounter(&now);
        return (double)now.QuadPart * state->ClockFrequency;
    }

    void Platform::Sleep(std::uint64_t milliseconds)
    {
        ::Sleep(milliseconds);
    }

    void Platform::SwapBuffers()
    {
        ::SwapBuffers(((Win32InternalState*)m_InternalState)->HDC);
    }

    // TODO: Make event system.
    LRESULT CALLBACK Win32ProcessMessage(HWND hwnd, std::uint32_t message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
            case WM_CREATE:
            {
            } break;
            case WM_ERASEBKGND:
                return 1;
            case WM_CLOSE:
                ((Win32InternalState*)GetWindowLongPtrA(hwnd, GWLP_USERDATA))->Callbacks.value().WindowCloseCallback(true);
                return 0;
            case WM_DESTROY:
                PostQuitMessage(0);
                return 0;
            case WM_SIZE: 
            {
                UINT width = LOWORD(lParam);
                UINT height = HIWORD(lParam);
                Win32InternalState* state = (Win32InternalState*)GetWindowLongPtrA(hwnd, GWLP_USERDATA);

                if (state != nullptr && state->Callbacks.has_value())
                {
                    state->Callbacks.value().WindowResizeCallback(width, height);
                }
            } return 0;
            case WM_KEYDOWN:
            case WM_SYSKEYDOWN:
            case WM_KEYUP:
            case WM_SYSKEYUP:
            {
                ((Win32InternalState*)GetWindowLongPtrA(hwnd, GWLP_USERDATA))->Callbacks.value().KeyCallback((Key)wParam, (message == WM_KEYDOWN || message == WM_SYSKEYDOWN));
            } break;
            case WM_MOUSEMOVE:
            {
                ((Win32InternalState*)GetWindowLongPtrA(hwnd, GWLP_USERDATA))->Callbacks.value().MousePositionCallback(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

            } break;
            case WM_MOUSEHWHEEL:
            {
                std::int32_t delta = GET_WHEEL_DELTA_WPARAM(wParam);
                if (delta != 0)
                {
                    delta = (delta < 0) ? -1 : 1;
                }
            } break;
            case WM_LBUTTONDOWN:
            case WM_MBUTTONDOWN:
            case WM_RBUTTONDOWN:
            case WM_LBUTTONUP:
            case WM_MBUTTONUP:
            case WM_RBUTTONUP:
            {
                bool pressed = (message == WM_LBUTTONDOWN || message == WM_MBUTTONDOWN || message == WM_RBUTTONDOWN);
                MouseButton button = MouseButton::MAX_BUTTONS;

                switch (message)
                {
                    case WM_LBUTTONDOWN:
                    case WM_LBUTTONUP:
                        button = MouseButton::MOUSE_LEFT;
                        break;
                    case WM_RBUTTONDOWN:
                    case WM_RBUTTONUP:
                        button = MouseButton::MOUSE_RIGHT;
                        break;
                    case WM_MBUTTONDOWN:
                    case WM_MBUTTONUP:
                        button = MouseButton::MOUSE_MIDDLE;
                        break;
                }

                if (button != MouseButton::MAX_BUTTONS)
                {
                    ((Win32InternalState*)GetWindowLongPtrA(hwnd, GWLP_USERDATA))->Callbacks.value().MouseButtonCallback(button, pressed);
                }
            } break;
        }

        return DefWindowProcA(hwnd, message, wParam, lParam);
    }    
}

#endif