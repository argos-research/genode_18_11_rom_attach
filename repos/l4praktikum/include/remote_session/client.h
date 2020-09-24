#ifndef _INCLUDE__REMOTE_SESSION_H__CLIENT_H_
#define _INCLUDE__REMOTE_SESSION_H__CLIENT_H_

#include <remote_session/remote_session.h>
#include <base/rpc_client.h>
#include <base/log.h>

namespace Remote { struct Session_client; }


struct Remote::Session_client : Genode::Rpc_client<Session>
{
	Session_client(Genode::Capability<Session> cap)
	: Genode::Rpc_client<Session>(cap) { }

	Genode::size_t shared_mem_quota()
	{
		return call<Rpc_shared_mem_quota>();
	}

	Genode::Dataspace_capability retrieve_shared_mem()
	{
		return call<Rpc_retrieve_shared_mem>();
	}

	void release_shared_mem()
	{
		call<Rpc_release_shared_mem>();
	}

	bool submit_input()
	{
		return call<Rpc_submit_input>();
	}
};

#endif /* _INCLUDE__REMOTE_SESSION_H__CLIENT_H_ */
