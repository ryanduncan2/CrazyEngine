#ifndef CRAZYENGINE_CORE_INPUT_H_
#define CRAZYENGINE_CORE_INPUT_H_

#include "CrazyEngine/Math/Vector2.h"

namespace CrazyEngine
{
    enum Key
    {
        CE_KEY_BACKSPACE = 0x08,
        CE_KEY_ENTER = 0x0D,
        CE_KEY_TAB = 0x09,
        CE_KEY_SHIFT = 0x10,
        CE_KEY_CONTROL = 0X11,

        CE_KEY_PAUSE = 0x13,
        CE_KEY_CAPS_LOCK = 0x14,

        CE_KEY_ESCAPE = 0x1B,

        CE_KEY_CONVERT = 0x1C,
        CE_KEY_NONCONVERT = 0x1D,
        CE_KEY_ACCEPT = 0x1E,
        CE_KEY_MODE_CHANGE = 0x1F,

        CE_KEY_SPACE = 0x20,
        CE_KEY_PRIOR = 0x21,
        CE_KEY_NEXT = 0x22,
        CE_KEY_END = 0x23,
        CE_KEY_HOME = 0x24,
        CE_KEY_LEFT = 0x25,
        CE_KEY_UP = 0x26,
        CE_KEY_RIGHT = 0x27,
        CE_KEY_DOWN = 0x28,
        CE_KEY_SELECT = 0x29,
        CE_KEY_PRINT = 0x2A,
        CE_KEY_EXECUTE = 0x2B,
        CE_KEY_SNAPSHOT = 0x2C,
        CE_KEY_INSERT = 0x2D,
        CE_KEY_DELETE = 0x2E,
        CE_KEY_HELP = 0x2F,

        CE_KEY_NUM1 = 0x31,
        CE_KEY_NUM0 = 0x30,
        CE_KEY_NUM2 = 0x32,
        CE_KEY_NUM3 = 0x33,
        CE_KEY_NUM4 = 0x34,
        CE_KEY_NUM5 = 0x35,
        CE_KEY_NUM6 = 0x36,
        CE_KEY_NUM7 = 0x37,
        CE_KEY_NUM8 = 0x38,
        CE_KEY_NUM9 = 0x39,

        CE_KEY_A = 0x41,
        CE_KEY_B = 0x42,
        CE_KEY_C = 0x43,
        CE_KEY_D = 0x44,
        CE_KEY_E = 0x45,
        CE_KEY_F = 0x46,
        CE_KEY_G = 0x47,
        CE_KEY_H = 0x48,
        CE_KEY_I = 0x49,
        CE_KEY_J = 0x4A,
        CE_KEY_K = 0x4B,
        CE_KEY_L = 0x4C,
        CE_KEY_M = 0x4D,
        CE_KEY_N = 0x4E,
        CE_KEY_O = 0x4F,
        CE_KEY_P = 0x50,
        CE_KEY_Q = 0x51,
        CE_KEY_R = 0x52,
        CE_KEY_S = 0x53,
        CE_KEY_T = 0x54,
        CE_KEY_U = 0x55,
        CE_KEY_V = 0x56,
        CE_KEY_W = 0x57,
        CE_KEY_X = 0x58,
        CE_KEY_Y = 0x59,
        CE_KEY_Z = 0x5A,

        CE_KEY_LWIN = 0x5B,
        CE_KEY_RWIN = 0x5C,
        CE_KEY_APPS = 0x5D,

        CE_KEY_SLEEP = 0x5F,

        CE_KEY_NUMPAD0 = 0x60,
        CE_KEY_NUMPAD1 = 0x61,
        CE_KEY_NUMPAD2 = 0x62,
        CE_KEY_NUMPAD3 = 0x63,
        CE_KEY_NUMPAD4 = 0x64,
        CE_KEY_NUMPAD5 = 0x65,
        CE_KEY_NUMPAD6 = 0x66,
        CE_KEY_NUMPAD7 = 0x67,
        CE_KEY_NUMPAD8 = 0x68,
        CE_KEY_NUMPAD9 = 0x69,
        CE_KEY_MULTIPLY = 0x6A,
        CE_KEY_ADD = 0x6B,
        CE_KEY_SEPARATOR = 0x6C,
        CE_KEY_SUBTRACT = 0x6D,
        CE_KEY_DECIMAL = 0x6E,
        CE_KEY_DIVIDE = 0x6F,
        CE_KEY_F1 = 0x70,
        CE_KEY_F2 = 0x71,
        CE_KEY_F3 = 0x72,
        CE_KEY_F4 = 0x73,
        CE_KEY_F5 = 0x74,
        CE_KEY_F6 = 0x75,
        CE_KEY_F7 = 0x76,
        CE_KEY_F8 = 0x77,
        CE_KEY_F9 = 0x78,
        CE_KEY_F10 = 0x79,
        CE_KEY_F11 = 0x7A,
        CE_KEY_F12 = 0x7B,
        CE_KEY_F13 = 0x7C,
        CE_KEY_F14 = 0x7D,
        CE_KEY_F15 = 0x7E,
        CE_KEY_F16 = 0x7F,
        CE_KEY_F17 = 0x80,
        CE_KEY_F18 = 0x81,
        CE_KEY_F19 = 0x82,
        CE_KEY_F20 = 0x83,
        CE_KEY_F21 = 0x84,
        CE_KEY_F22 = 0x85,
        CE_KEY_F23 = 0x86,
        CE_KEY_F24 = 0x87,

        CE_KEY_NUM_LOCK = 0x90,
        CE_KEY_SCROLL = 0x91,

        CE_KEY_NUMPAD_EQUAL = 0x92,

        CE_KEY_LSHIFT = 0xA0,
        CE_KEY_RSHIFT = 0xA1,
        CE_KEY_LCONTROL = 0xA2,
        CE_KEY_RCONTROL = 0xA3,
        CE_KEY_LMENU = 0xA4,
        CE_KEY_RMENU = 0xA5,

        CE_KEY_SEMICOLON = 0xBA,
        CE_KEY_PLUS = 0xBD,
        CE_KEY_COMMA = 0xBC,
        CE_KEY_MINUS = 0xBD,
        CE_KEY_PERIOD = 0xBE,
        CE_KEY_SLASH = 0xBF,
        CE_KEY_GRAVE = 0xC0,
    };

    Key& operator++(Key& key);

    enum MouseButton
    {
        MOUSE_LEFT,
        MOUSE_RIGHT,
        MOUSE_MIDDLE,
        MAX_BUTTONS
    };

    class Input
    {
    private:

        bool m_CurrentKeyboardState[256];
        bool m_PreviousKeyboardState[256];

        Vector2 m_CurrentMousePosition;
        Vector2 m_PreviousMousePosition;
        bool m_CurrentMouseButtonsState[3];
        bool m_PreviousMouseButtonsState[3];
        int m_MouseWheelDelta;

    public:

        Input();
        ~Input();

        void Initialise();
        void Terminate();
        void Update();

        void ProcessKeyboardInput(Key key, bool pressed);
        void ProcessMouseButtonInput(MouseButton button, bool pressed);
        void ProcessMouseMovement(int mouseX, int mouseY);
        void ProcessMouseWheel(int delta);

        // Keyboard Querying Functions

        bool IsKeyDown(Key key);
        bool IsKeyUp(Key key);
        bool WasKeyDown(Key key);
        bool WasKeyUp(Key key);

        bool IsKeyPressed(Key key);
        bool IsKeyReleased(Key key);

        // Mouse Querying Functions

        bool IsMouseButtonDown(MouseButton button);
        bool IsMouseButtonUp(MouseButton button);
        bool WasMouseButtonDown(MouseButton button);
        bool WasMouseButtonUp(MouseButton button);

        bool IsMouseButtonPressed(MouseButton button);
        bool IsMouseButtonReleased(MouseButton button);

        int GetMouseWheelDelta();

        Vector2 GetMousePosition();
        Vector2 GetPreviousMousePosition();
    };
}

#endif