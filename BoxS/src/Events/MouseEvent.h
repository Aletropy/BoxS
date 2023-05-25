#pragma once

#include "Event.h"

#include "Core/MouseCodes.h"

#include <sstream>

namespace BoxS
{
    class MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(const float x, const float y)
            : m_MouseX(x), m_MouseY(y) { }

        float GetX() const { return m_MouseX; }
        float GetY() const { return m_MouseY; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseMoved)

    private:
        float m_MouseX, m_MouseY;
    };

    class MouseScrolledEvent : public Event
    {
    public:
        MouseScrolledEvent(const float xoffset, const float yoffset)
            : m_XOffset(xoffset), m_YOffset(yoffset) { }

        float GetXOffset() const { return m_XOffset; }
        float GetYOffset() const { return m_YOffset; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseScrolled)

    private:
        float m_XOffset, m_YOffset;
    };

    class MouseButtonPressedEvent : public Event
    {
    public:
        MouseButtonPressedEvent(MouseCode button)
            : m_Button(button) { }

        MouseCode GetButton() const { return m_Button; }

        EVENT_CLASS_TYPE(MouseButtonPressed)

    private:
        MouseCode m_Button;
    };

    class MouseButtonReleasedEvent : public Event
    {
    public:
        MouseButtonReleasedEvent(MouseCode button)
            : m_Button(button) { }

        MouseCode GetButton() const { return m_Button; }

        EVENT_CLASS_TYPE(MouseButtonReleased)

    private:
        MouseCode m_Button;
    };
}