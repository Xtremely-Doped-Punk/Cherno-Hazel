#pragma once

#include "Hazel/Core.h"

#include <string>
#include <functional>

namespace Hazel {

	// Initial Setup: Event calls are blocking, i.e. event invokes are immediately dispatched.
	// Future Setup: Buffer event in a bus and process them	at event part of update stage

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseBtnPressed, MouseBtnReleased, MouseMoved, MouseScrolled,
	};

	enum EventCategory // we assign 'bits' in-order to facilitate a event to be in multiple categories
	{
		EvCat_None = 0,
		EvCat_Application = BIT(0),
		EvCat_Input = BIT(1),
		EvCat_Keyboard = BIT(2),
		EvCat_Mouse = BIT(3),
		EvCat_MouseBtn = BIT(4),
	};

	/*
	Diff bet enum class (Scoped Enumeration)	&		enum (Unscoped Enumeration):
	-> contained within the enum type’s scope	|| -> injected into the surrounding scope
	->  no implicit conversion to int			|| ->  can be used as int directly

	Why such conventions?
	• EventType: Uses enum class for type safety and to avoid name clashes (e.g., WindowClose only exists inside EventType).
	• EventCategory: Uses enum for bitwise operations and easy conversion to int (since categories are flags).

	Macro Operators: [example: EVENT_CLASS_TYPE(WindowResize)]
	| Macro Usage		| Result               | Example Output			  | 
	|-------------------|----------------------|--------------------------| 
	| type				| Parameter itself	   | WindowResize		      |
	| #type				| String literal       | "WindowResize"			  | 
	| EventType::##type | Token concatenation  | EventType::WindowResize  |
	*/

/*
 so while using below macro declarations into derived event classes, call 
 EVENT_CLASS_TYPE(EventType::WindowResize) initially to make sure ur type is crt,
 then remove "EventType::" part from the param to work properly
*/
#define EVENT_CLASS_TYPE(type) \
static EventType GetStaticType() { return EventType::##type; } \
virtual EventType GetEventType() const override { return GetStaticType(); } \
virtual const char* GetName() const override { return #type; }

/* ALTERNATE STYLE: (NOT OPTIMAL) for call EVENT_CLASS_TYPE(EventType::WindowResize)
#define EVENT_CLASS_TYPE(type) \
static EventType GetStaticType() { return type; } \
virtual EventType GetEventType() const override { return GetStaticType(); } \

virtual const char* GetName() const override { #type; } // note: it will give string "EventType::WindowResize"
									<-- [or] -->
virtual const char* GetName() const override { return StripPrefix(#type).c_str(); } // string: "WindowResize"

	// put inside EventBase
	std::string StripPrefix(const std::string& type) const {
		size_t pos = type.find("::");
		if (pos != std::string::npos)
			return type.substr(pos + 2);
		return type;
*/

#define EVENT_CLASS_CATEGORY(category) \
virtual int	GetCategoryFlags() const override { return category; }


	class HAZEL_API EventBase
	{
		friend class EventDispatcher; // grants permission to private members (EventDispatcher has full access to Event)

	protected:
		bool m_Handled = false; // to handle propagation flow of dispatched event throughout the layers

	public:
		// virual with const = 0, means its a pure vitual fn, i.e. acts a abstract methods, 
		// i.e. strictly need to be declared in derived classes. note const here in fn def 
		// indicates that this member function does not modify any member variables of the class. 
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		// need for inline =>  Suggests to the compiler to insert the function’s code directly at the call site, 
		// rather than making a regular function call as it Can reduce function call overhead for very small functions like simple getters.
		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category; // bit wise 'and' op with resp category. 
			// returns true if 1 exist in the resp 2^x's position integer form of CategoryFlags
		}
	};

	/* #Dispatcher:
	- to help dispatch events based on their time
	*/
	class EventDispatcher
	{
	private:
		template<typename T>
		using EventFn = std::function<bool(T&)>; // funtion arg that returns bool and take T-ref param
		EventBase& m_Event; // refernce to store orginal event that is passed in as class arg (for scope bending properties)
	
	public:
		EventDispatcher(EventBase& event) : m_Event(event) { }

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			// currently there is no type safety for this template T to be of event type only
			if (m_Event.GetEventType() == T::GetStaticType()) 
				// if func's type matches with this dispatcher's eventype, then it called
			{
				m_Event.m_Handled = func(*(T*)&m_Event); 
				/* Breakdown:
				0.	m_Event:		reference to the actual event, i.e. changes will be reflected in orginal event class
				1.	&m_Event:		gets the address of m_Event
				2.	(T*)&m_Event:	casts the pointer from EventBase* to T*, where T is a derived event type
				3.	*(T*)&m_Event:	dereferences the pointer, resulting in a reference to the derived event type T
				4.	func(*(T*)&m_Event): func is expected to take a T& parameter. */
				return true;
			}
			return false;
		}
	};

	// operator overriding for c-out-stream for Event classes to automatically use ToString() fn within it
	// Error    C2079    '_' uses undefined struct 'fmt::v10::detail::type_is_unformattable_for<T,char>'
	// ?? this worked with older version, I guess ??
	/*inline std::ostream& operator<<(std::ostream& os, const EventBase& e)
	{
		return os << e.ToString();
	}*/

	// Solution for newer version: https://fmt.dev/latest/api/#udt
	/* There are two ways to make a user-defined type formattable: 
	providing a format_as function or specializing the formatter struct template.
	The format_as function should take an object of your type and return an object of a formattable type.
	*/
	inline std::string format_as(const EventBase& e)
	{
		return e.ToString();
	}
}