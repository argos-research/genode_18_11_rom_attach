#include <base/component.h>
#include <base/log.h>

// additinal includes for server functionality
#include <base/heap.h>
#include <root/component.h>
#include <remote_session/remote_session.h>
#include <base/rpc_server.h>
#include <base/service.h>

// additional includes for network connection
#include <libc/component.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <util/string.h>

namespace Remote {
	struct Session_component;
	struct Root_component;
	struct Main;
}


class Decrypt::Session_component
:
	public Genode::Rpc_object<Session>
{
	private:

		Libc::Env &_env;
		Genode::size_t _shared_mem_quota;	// size of the allocated shared memory
		Genode::Ram_dataspace_capability _ds;
		Genode::addr_t _addr;

	public:	

		Session_component(Genode::Env &env, Genode::size_t quota) 
		:
			_env(env), _shared_mem_quota(quota), _addr(0) 
		{
			Genode::log("Remote session quota for shared_mem is: ", _shared_mem_quota);
		}

		Genode::size_t shared_mem_quota() {
			return _shared_mem_quota;
		}

		Genode::Dataspace_capability retrieve_shared_mem() {
			_ds = _env.pd().alloc(_shared_mem_quota);
			_addr = _env.rm().attach(_ds);	
			return _ds;
		}

		void release_shared_mem() {
			_env.ram().free(_ds);
		}

		bool submit_input() {
		  Libc::with_libc([&] () {
		    Genode::log("remote test completed");

		    struct sockaddr_in srv_addr;
		    srv_addr.sin_port = htons(8080);
		    srv_addr.sin_family = AF_INET;
		    srv_addr.sin_addr.s_addr = inet_addr("131.159.12.17");

		    int sd = ::socket(AF_INET, SOCK_STREAM, 0);
		    ::connect(sd, (struct sockaddr *)&srv_addr, sizeof(srv_addr));

		    //char buffer[16384];
		    ::recv(sd, (char *)_addr, 16383, 0);
		    Genode::String<16383> s(buffer);
		    Genode::log(s);

		    // ----------------------------------

		  });	
		}

};


class Decrypt::Root_component
:
	public Genode::Root_component<Session_component>
{
	private:

		Libc::Env &_env;

	protected:

		Session_component *_create_session(const char *args)
		{
			Genode::log("creating decrypt session");
			Genode::size_t shared_mem_quota = Genode::Arg_string::find_arg(args, "ram_quota").ulong_value(0);
			//Genode::size_t complete_session_quota = shared_mem_quota + sizeof(Decrypt::Session_component)+ md_alloc()->overhead(sizeof(Decrypt::Session_component));
			//Genode::log("complete_session_quota: ", complete_session_quota);
			Genode::size_t unusable_quota = shared_mem_quota % 4096;
			shared_mem_quota -= unusable_quota;
			return new (md_alloc()) Session_component(_env, shared_mem_quota);
		}

	public:

		Root_component(Genode::Env &env, Genode::Entrypoint &ep,
		               Genode::Allocator &alloc)
		:
			Genode::Root_component<Session_component>(ep, alloc), _env(env)
		{
			Genode::log("creating root component");
		}
};


struct Decrypt::Main
{
	Libc::Env &env;

	Genode::Sliced_heap sliced_heap { env.ram(), env.rm() };

	Genode::Service_registry  parent_services { };

	Decrypt::Root_component root { env, env.ep(), sliced_heap };

	Main(Genode::Env &env) : env(env)
	{
		env.parent().announce(env.ep().manage(root));
	}
};


void Libc::Component::construct(Libc::Env &env)
{
	static Decrypt::Main main(env);
}
