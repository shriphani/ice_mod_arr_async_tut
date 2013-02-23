#include <Ice/Ice.h>
#include <Assign.h>

using namespace std;
using namespace AsyncStatefulDemo;

int ASSIGN_ARR[5];   // this is the array we assign items to

class AssignI : public Assign {
public:
	virtual bool asgn(int item, int position,const Ice::Current&);
};

bool AssignI::asgn(int item, int position, const Ice::Current&) {
	if (position > 4) {
		return false;
	}
	ASSIGN_ARR[position] = item;

	for (int i = 0; i < 5; i++) {
		cout << ASSIGN_ARR[i] << " ";
	}
	cout << endl;
	return true;
}

int main(int argc, char *argv[]) {
	int status = 0;
	Ice::CommunicatorPtr ic;
	try {
		// THIS STUFF IS MOSTLY BOILERPLATE. CHANGE STUFF FOR YOUR CLASS
		ic = Ice::initialize(argc, argv);
		Ice::ObjectAdapterPtr adapter = 
			ic->createObjectAdapterWithEndpoints("AssignAdapter", "default -p 10000"); // we create an adapter w/ endpoint and port
		Ice::ObjectPtr object = new AssignI;
		adapter->add(object, ic->stringToIdentity("SimpleAssign")); // this adapter's unique string identifier
		adapter->activate();
		ic->waitForShutdown();
	} catch (const Ice::Exception& e) {
		cerr << e << endl;
		status = 1;
	} catch (char* msg) {
		cerr << msg << endl;
		status = 1;
	}

	// THIS IS ALL BOILERPLATE, COPY AND PASTE INTO YOUR MASTER
	if (ic) {
		try {
			ic->destroy();
		} catch (const Ice::Exception& e) {
			cerr << e << endl;
			status = 1;
		}
	}
	return status;
}