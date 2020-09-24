#include <base/component.h>
#include <base/log.h>
#include <remote_session/connection.h>
#include <custom_child/custom_child.h>


void Component::construct(Genode::Env &env)
{
	Remote::Connection decrypt(env);

	Genode::size_t q = decrypt.shared_mem_quota();
	Genode::log("Quota from client perspective: ", q);

	Genode::Dataspace_capability ds = decrypt.retrieve_shared_mem();

	bool result = decrypt.submit_input();

	decrypt.release_shared_mem();

	Genode::log("decrypt test completed");
}
