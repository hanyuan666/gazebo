/*
 *  Gazebo - Outdoor Multi-Robot Simulator
 *  Copyright (C) 2003  
 *     Nate Koenig & Andrew Howard
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */
/* Desc: Base gui
 * Author: Nate Koenig
 * Date: 14 May 2009
 * SVN: $Id:$
 */

#ifndef GUIAPI_HH
#define GUIAPI_HH

#include <string>
#include <iostream>

namespace gazebo
{
  class XMLConfigNode;
  class Gui;

  class GuiAPI
  {
    /// \brief Constructor
    public: GuiAPI(int x, int y, int w, int h, const std::string &t);

    /// \brief Destructor
    public: virtual ~GuiAPI();

    /// \brief Load the gui
    public: void Load(XMLConfigNode *node);

    /// \brief Save the gui params in xml format
    public: void Save(std::string &prefix, std::ostream &stream);

    /// \brief Initalize the gui
    public: void Init();

    /// \brief Update the gui
    public: void Update();

    private: Gui *gui;
  };
}

#endif
