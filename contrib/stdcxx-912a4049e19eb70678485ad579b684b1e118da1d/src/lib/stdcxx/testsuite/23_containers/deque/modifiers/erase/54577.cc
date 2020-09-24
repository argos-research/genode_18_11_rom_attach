// { dg-options "-std=gnu++11" }
// { dg-do compile }

// Copyright (C) 2013-2016 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING3.  If not see
// <http://www.gnu.org/licenses/>.

#include <deque>

void test01() 
{
  std::deque<int> d1;
  d1.push_back(1);
  d1.erase(d1.cbegin());

  std::deque<int> d2;
  d2.push_back(2);
  d2.push_back(3);
  d2.erase(d2.cbegin(), d2.cend());
}
