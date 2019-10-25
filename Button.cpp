/*
	Button - a small library for Arduino to handle button debouncing
	
	MIT licensed.
*/

#include "Button.h"
#include <Arduino.h>

Button::Button(uint8_t pin, bool use_pullup)
:  _pin(pin)
,  _delay(100)
,  _state(HIGH)
,  _has_changed(false)
,  _ignore_until(0)
,  _use_pullup(use_pullup)
{
}

void Button::begin()
{
// use the internal pullup (default: true) 
	if (_use_pullup)
	{
		pinMode(_pin, INPUT_PULLUP);
	}
	else
	{
		pinMode(_pin, INPUT);
	}

// 
// public methods
// 

bool Button::read()
{
	// ignore pin changes until after this delay time
	if (_ignore_until > millis())
	{
		// ignore any changes during this period
	}
	
	// pin has changed 
	else if (digitalRead(_pin) != _state)
	{
		_ignore_until = millis() + _delay;
		_state = !_state;
		_has_changed = true;
	}
	
	return _state;
}

// has the button been toggled from on -> off, or vice versa
bool Button::toggled()
{
	read();
	return has_changed();
}

// mostly internal, tells you if a button has changed after calling the read() function
bool Button::has_changed()
{
	if (_has_changed == true)
	{
		_has_changed = false;
		return true;
	}
	return false;
}

// has the button gone from off -> on
bool Button::pressed()
{
	if(_use_pullup == true) {
		if (read() == !PRESSED && has_changed() == true) {
			return true;
		}else{
			return false;
		}
	} else {
		if (read() == PRESSED && has_changed() == true) {
			return true;
		}else{
			return false;
		}
	}
}

// has the button gone from on -> off
bool Button::released()
{
	if(_use_pullup == true) {
		if (read() == RELEASED && has_changed() == true)
			return true;
		else
			return false;
	} else {
		if (read() == !RELEASED && has_changed() == true)
			return true;
		else
			return false;
	}
}

