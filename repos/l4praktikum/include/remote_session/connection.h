#ifndef _INCLUDE__REMOTE_SESSION__CONNECTION_H_
#define _INCLUDE__REMOTE_SESSION__CONNECTION_H_

#include <remote_session/client.h>
#include <base/connection.h>

namespace Remote { struct Connection; }


struct Remote::Connection : Genode::Connection<Session>, Session_client
{
	Connection(Genode::Env &env)
	:
		Genode::Connection<Remote::Session>(env, session(env.parent(),
		                                                "ram_quota=32K, cap_quota=12")),

		Session_client(cap()) { }
};

#endif /* _INCLUDE__REMOTE_SESSION__CONNECTION_H_ */
