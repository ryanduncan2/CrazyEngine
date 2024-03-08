#include "CrazyEngine/Core/Input.h"

namespace CrazyEngine
{
    Input::Input()
    {
    }

    Input::~Input()
    {
    }

    void Input::Initialise()
    {
        memset(&m_CurrentKeyboardState, 0, sizeof(m_CurrentKeyboardState));
        memset(&m_PreviousKeyboardState, 0, sizeof(m_PreviousKeyboardState));
        memset(&m_CurrentMouseButtonsState, 0, sizeof(m_CurrentMouseButtonsState));
        memset(&m_PreviousMouseButtonsState, 0, sizeof(m_PreviousMouseButtonsState));
    }

    void Input::Terminate()
    {
    }

    void Input::Update()
    {
        memcpy(m_PreviousKeyboardState, m_CurrentKeyboardState, sizeof(m_CurrentKeyboardState));
        memcpy(m_PreviousMouseButtonsState, m_CurrentMouseButtonsState, sizeof(m_CurrentMouseButtonsState));
    }

    void Input::ProcessKeyboardInput(Key key, bool pressed)
    {
        m_CurrentKeyboardState[key] = pressed;
    }

    void Input::ProcessMouseButtonInput(MouseButton button, bool pressed)
    {
        m_CurrentMouseButtonsState[button] = pressed;
    }

    void Input::ProcessMouseMovement(int mouseX, int mouseY)
    {
        m_CurrentMousePosition = Vector2(mouseX, mouseY);
    }

    // Keyboard Querying Functions

    bool Input::IsKeyDown(Key key)
    {
        return m_CurrentKeyboardState[key] == true;
    }

    bool Input::IsKeyUp(Key key)
    {
        return m_CurrentKeyboardState[key] == false;
    }

    bool Input::WasKeyDown(Key key)
    {
        return m_PreviousKeyboardState[key] == true;
    }

    bool Input::WasKeyUp(Key key)
    {
        return m_PreviousKeyboardState[key] == false;
    }

    bool Input::IsKeyPressed(Key key)
    {
        return m_PreviousKeyboardState[key] == false && m_CurrentKeyboardState[key] == true;
    }

    bool Input::IsKeyReleased(Key key)
    {
        return m_PreviousKeyboardState[key] == true && m_CurrentKeyboardState[key] == false;
    }

    // Mouse Querying Functions

    bool Input::IsMouseButtonDown(MouseButton button)
    {
        return m_CurrentMouseButtonsState[button] == true;
    }

    bool Input::IsMouseButtonUp(MouseButton button)
    {
        return m_CurrentMouseButtonsState[button] == false;
    }

    bool Input::WasMouseButtonDown(MouseButton button)
    {
        return m_PreviousMouseButtonsState[button] == true;
    }

    bool Input::WasMouseButtonUp(MouseButton button)
    {
        return m_PreviousMouseButtonsState[button] == false;
    }

    bool Input::IsMouseButtonPressed(MouseButton button)
    {
        return m_PreviousMouseButtonsState[button] == false && m_CurrentMouseButtonsState[button] == true;
    }

    bool Input::IsMouseButtonReleased(MouseButton button)
    {
        return m_PreviousMouseButtonsState[button] == true && m_CurrentMouseButtonsState[button] == false;
    }

    Vector2 Input::GetMousePosition()
    {
        return m_CurrentMousePosition;
    }

    Vector2 Input::GetPreviousMousePosition()
    {
        return m_PreviousMousePosition;
    }
}