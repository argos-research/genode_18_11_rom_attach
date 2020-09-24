#ifndef _INCLUDE__CUSTOM__CHILD_H_
#define _INCLUDE__CUSTOM__CHILD_H_

#include <util/xml_node.h>
#include <base/allocator.h>
#include <base/service.h>
#include <base/lock.h>
#include <base/child.h>
#include <timer_session/timer_session.h>
#include <pd_session/client.h>
#include <init/child_policy.h>

#include <libc/component.h>

namespace Remote {
	class Custom_child;
}

class Remote::Custom_child : public Genode::Child_policy
{
private:
	
	Name const _name;

	Genode::Env &_env;

	Genode::Allocator &_alloc;

	Genode::Cap_quota const _cap_quota;
	Genode::Ram_quota const _ram_quota;

	Genode::Child _child;

	

public:
	
	Custom_child(Genode::Env &env,
		                Genode::Allocator &alloc,
		                Genode::Session_label const &label,
		                Genode::Cap_quota cap_quota,
		                Genode::Ram_quota ram_quota)
		:
			_name(label),
			_env(env), _alloc(alloc),
			_cap_quota(Genode::Child::effective_quota(cap_quota)),
			_ram_quota(Genode::Child::effective_quota(ram_quota)),
			_child(_env.rm(), _env.ep().rpc_ep(), *this)
		{ }

	~Target_child();

		/****************************
		 ** Child_policy interface **
		 ****************************/

	Name name() const override { return _name; }

	Genode::Pd_session           &ref_pd()           override { return _env.pd(); }
	Genode::Pd_session_capability ref_pd_cap() const override { return _env.pd_session_cap(); }

	void init(Genode::Pd_session &session,
		          Genode::Pd_session_capability cap) override
	{
		session.ref_account(_env.pd_session_cap());
		_env.pd().transfer_quota(cap, _cap_quota);
		_env.pd().transfer_quota(cap, _ram_quota);
	}
}


#endif /* _INCLUDE__CUSTOM__CHILD_H_ */
