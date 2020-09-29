﻿#ifndef _SELECTEVENTARGs_HPP_
#define _SELECTEVENTARGs_HPP_

#include "EventArgs.hpp"

class MenuItem;

class SelectEventArgs : public EventArgs
{
private:
	String _selected;

public:
	SelectEventArgs(MenuItem *source);
	SelectEventArgs(MenuItem *source, String selected);
	String getSelected();
};

#endif
