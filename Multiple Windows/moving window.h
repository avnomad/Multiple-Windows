//	Copyright (C) 2010, 2012 Vaptistis Anogeianakis <nomad@cornercase.gr>
/*
 *	This file is part of Multiple Windows.
 *
 *	Multiple Windows is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	Multiple Windows is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with Multiple Windows.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MOVING_WINDOW_H
#define MOVING_WINDOW_H

#include "common.h"

namespace MovingWindow
{
	extern WNDCLASS commonAttributes;
	LRESULT CALLBACK messageHandler(HWND window,UINT message,WPARAM argW,LPARAM argL);
} // end namespace MovingWindow

#endif // MOVING_WINDOW_H