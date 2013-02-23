#include <Ice/Ice.h>
#include <Assign.h>

using namespace std;
using namespace AsyncStatefulDemo;

int main(int argc, char* argv[]) {
	int status = 0;
	Ice::CommunicatorPtr ic;
	try {
		ic = Ice::initialize(argc, argv);
		Ice::ObjectPrx base = ic->stringToProxy("SimpleAssign:default -p 10000");
		AssignPrx assigner = AssignPrx::checkedCast(base);
		if (!assigner) {
			throw "Invalid Proxy";
		}
		Ice::AsyncResultPtr r = assigner->begin_asgn(atoi(argv[1]), atoi(argv[1]));  // begin_<function_name> is the way to initiate an async call.

		while (!r->isCompleted()) {  // this is how you test if that async call has completed
			cout << "Waiting" << endl;
		}
		string res = assigner->end_asgn(r) ? "Success" : "Fail";
		cout << res << endl;   // once the async call is completed, if there is a return value, end_fib will return it. Pass the AssignResultPtr object to it.
	} catch (const Ice::Exception& e) {
		cerr << e << endl;
		status = 1;
	} catch (const char* msg) {
		cerr << msg << endl;
		status = 1;
	}

	if (ic) {
		ic->destroy();
	}
	return status;
}