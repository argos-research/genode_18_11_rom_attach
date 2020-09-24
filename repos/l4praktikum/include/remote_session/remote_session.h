#ifndef _INCLUDE__REMOTE_SESSION__REMOTE_SESSION_H_
#define _INCLUDE__REMOTE_SESSION__REMOTE_SESSION_H_

#include <session/session.h>
#include <base/rpc.h>

namespace Remote { struct Session; }


struct Remote::Session : Genode::Session
{
	static const char *service_name() { return "Remote"; }

	enum { CAP_QUOTA = 2 };

	virtual Genode::size_t shared_mem_quota() = 0;
	virtual Genode::Dataspace_capability retrieve_shared_mem() = 0;
	virtual void release_shared_mem() = 0;
	virtual bool submit_input() = 0;

	GENODE_RPC(Rpc_shared_mem_quota, Genode::size_t, shared_mem_quota);
	GENODE_RPC(Rpc_retrieve_shared_mem, Genode::Dataspace_capability,
	               retrieve_shared_mem);
	GENODE_RPC(Rpc_release_shared_mem, void, release_shared_mem);
	GENODE_RPC(Rpc_submit_input, bool, submit_input);

	GENODE_RPC_INTERFACE(Rpc_shared_mem_quota, Rpc_retrieve_shared_mem,
		                    Rpc_release_shared_mem, Rpc_submit_input);
};

#endif /* _INCLUDE__REMOTE_SESSION__REMOTE_SESSION_H_ */
