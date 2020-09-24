/*
 * \brief  Layout target
 * \author Norman Feske
 * \date   2018-09-27
 */

/*
 * Copyright (C) 2018 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _TARGET_H_
#define _TARGET_H_

/* local includes */
#include <types.h>

namespace Window_layouter { class Target; }


class Window_layouter::Target : Noncopyable
{
	public:

		typedef String<64> Name;

	private:

		Name     const _name;
		unsigned const _layer;
		Rect     const _geometry;

	public:

		Target(Xml_node target, Rect geometry)
		:
			_name (target.attribute_value("name", Name())),
			_layer(target.attribute_value("layer", 9999UL)),
			_geometry(geometry)
		{ }

		/* needed to use class as 'Registered<Target>' */
		virtual ~Target() { }

		Name     name()     const { return _name; }
		unsigned layer()    const { return _layer; }
		Rect     geometry() const { return _geometry; }
};

#endif /* _TARGET_H_ */
