#pragma once
#include "pch.h"

#include "MTX/Core.h"

namespace MTX {

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	// BIT shifts the bit to the left by 1
	// Example 0 = '0000 0000' then shift it by one to (1 << 0) = '0000 0001'
	// This is because Events can have multiple categories. 
	// A mouse button event can have Input, Mouse, MousButton. Because we shift it, it looks like this
	// '0000 0010' for Input
	// '0000 1000' for Mouse
	// '0001 0000' for MouseButton
	// Combine it all so it looks like this '0001 1010'
	// Thereby showing it is Input, Mouse and MouseButton
	// They are combined by using | (OR them together)
	// example EventCategoryInput | EventCategoryKeyboard. Now it's one value of '0000 0110'
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication =	BIT(0), // (1 << 0) 0000 0001
		EventCatergoryInput =		BIT(1), // (1 << 1) 0000 0010 etc
		EventCatergoryKeyboard =	BIT(2),
		EventCatergoryMouse =		BIT(3),
		EventCatergoryMouseButton = BIT(4)
	};

	// ## token-pasing takes two seperate tokens and pastes them together to form a single token
	// Ex. #define ArgArg(x, y) x##y
	// Then do ArgArg(lady, bug) goes to ladybug
	// It reduces the space so that EventType:: has not space after thereby ruining the macro
	// # token-string (used to turn the macro parameter into a string) 'stringizing'
	// #@ token-string (used to turn the macro parameter into a char) 'charizing'
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
							   virtual EventType GetEventType() const override { return GetStaticType(); }\
							   virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }\

	// Virtual class to be implemented by other classes
	class Event
	{
	public:
		bool Handled = false;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	};

	// Dispatcher to dispatch events to layers to determine if they want to use them
	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			:m_Event(event)
		{}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled = func(*(T*)& m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}