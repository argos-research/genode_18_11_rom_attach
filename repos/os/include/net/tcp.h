/*
 * \brief  Transmission Control Protocol
 * \author Martin Stein
 * \date   2016-06-15
 */

/*
 * Copyright (C) 2016-2017 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _TCP_H_
#define _TCP_H_

/* Genode includes */
#include <base/exception.h>
#include <base/stdint.h>
#include <util/endian.h>
#include <net/ethernet.h>
#include <net/ipv4.h>
#include <util/register.h>
#include <net/port.h>

namespace Net
{
	class Tcp_state;
	class Tcp_packet;
}

/**
 * Data layout of this class conforms to an TCP packet (RFC 768)
 */
class Net::Tcp_packet
{
	private:

		using uint8_t      = Genode::uint8_t;
		using uint16_t     = Genode::uint16_t;
		using uint32_t     = Genode::uint32_t;
		using size_t       = Genode::size_t;
		using Exception    = Genode::Exception;

		uint16_t _src_port;
		uint16_t _dst_port;
		uint32_t _seq_nr;
		uint32_t _ack_nr;
		unsigned _data_offset : 4;
		unsigned _reserved    : 3;
		unsigned _flags_msb   : 1;
		uint8_t  _flags_lsb;
		uint16_t _window_size;
		uint16_t _checksum;
		uint16_t _urgent_ptr;
		uint32_t _data[0];

		struct Flags : Genode::Register<16>
		{
			struct Fin : Bitfield<0, 1> { };
			struct Syn : Bitfield<1, 1> { };
			struct Rst : Bitfield<2, 1> { };
			struct Psh : Bitfield<3, 1> { };
			struct Ack : Bitfield<4, 1> { };
			struct Urg : Bitfield<5, 1> { };
			struct Ece : Bitfield<6, 1> { };
			struct Crw : Bitfield<7, 1> { };
			struct Ns  : Bitfield<8, 1> { };
		};

	public:

		void update_checksum(Ipv4_address ip_src,
		                     Ipv4_address ip_dst,
		                     size_t       tcp_size);


		/***************
		 ** Accessors **
		 ***************/

		Port     src_port()    const { return Port(host_to_big_endian(_src_port)); }
		Port     dst_port()    const { return Port(host_to_big_endian(_dst_port)); }
		uint32_t seq_nr()      const { return host_to_big_endian(_seq_nr); }
		uint32_t ack_nr()      const { return host_to_big_endian(_ack_nr); }
		uint8_t  data_offset() const { return _data_offset; }
		uint16_t flags()       const { return _flags_lsb | _flags_msb << 8; }
		uint16_t window_size() const { return host_to_big_endian(_window_size); }
		uint16_t checksum()    const { return host_to_big_endian(_checksum); }
		uint16_t urgent_ptr()  const { return host_to_big_endian(_urgent_ptr); }
		bool     ns()          const { return Flags::Ns::get(flags()); };
		bool     ece()         const { return Flags::Ece::get(flags()); };
		bool     crw()         const { return Flags::Crw::get(flags()); };
		bool     fin()         const { return Flags::Fin::get(flags()); };
		bool     syn()         const { return Flags::Syn::get(flags()); };
		bool     rst()         const { return Flags::Rst::get(flags()); };
		bool     psh()         const { return Flags::Psh::get(flags()); };
		bool     ack()         const { return Flags::Ack::get(flags()); };
		bool     urg()         const { return Flags::Urg::get(flags()); };

		void src_port(Port p) { _src_port = host_to_big_endian(p.value); }
		void dst_port(Port p) { _dst_port = host_to_big_endian(p.value); }


		/*********
		 ** log **
		 *********/

		void print(Genode::Output &output) const;

} __attribute__((packed));

#endif /* _TCP_H_ */